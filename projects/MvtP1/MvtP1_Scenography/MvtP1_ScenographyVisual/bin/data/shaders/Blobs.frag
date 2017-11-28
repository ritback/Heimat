




#version 150

uniform vec3            uResolution;           // viewport resolution (in pixels)
uniform float           uGlobalTime;           // shader playback time (in seconds)
// blobs parameters
uniform float           uBpm;
uniform float           uBpmAmplitude;
uniform float           uDistortionAmount;
uniform float           uDistortionSpeed;
uniform float           uMvtSpeed;
uniform float           uMvtRange;


in vec2 iFragCoord; // coordinate in pixel.
in vec2 iChannelCoord0;

out vec4 oColor;



// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// discontinuous pseudorandom uniformly distributed in [-0.5, +0.5]^3
vec3 random3(vec3 c) {
    float j = 4096.0*sin(dot(c,vec3(17.0, 59.4, 15.0)));
    vec3 r;
    r.z = fract(512.0*j);
    j *= .125;
    r.x = fract(512.0*j);
    j *= .125;
    r.y = fract(512.0*j);
    return r-0.5;
}


// -----------------------------------------------------------------------------
// skew constants for 3d simplex functions
const float F3 =  0.3333333;
const float G3 =  0.1666667;

// 3d simplex noise
float simplex3d(vec3 p)
{
    // 1. find current tetrahedron T and it's four vertices
    // s, s+i1, s+i2, s+1.0 - absolute skewed (integer) coordinates of T vertices
    // x, x1, x2, x3 - unskewed coordinates of p relative to each of T vertices
    
    // calculate s and x
    vec3 s = floor(p + dot(p, vec3(F3)));
    vec3 x = p - s + dot(s, vec3(G3));
    
    // calculate i1 and i2
    vec3 e = step(vec3(0.0), x - x.yzx);
    vec3 i1 = e*(1.0 - e.zxy);
    vec3 i2 = 1.0 - e.zxy*(1.0 - e);
    
    // x1, x2, x3
    vec3 x1 = x - i1 + G3;
    vec3 x2 = x - i2 + 2.0*G3;
    vec3 x3 = x - 1.0 + 3.0*G3;
    
    // 2. find four surflets and store them in d
    vec4 w, d;
    
    // calculate surflet weights
    w.x = dot(x, x);
    w.y = dot(x1, x1);
    w.z = dot(x2, x2);
    w.w = dot(x3, x3);
    
    // w fades from 0.6 at the center of the surflet to 0.0 at the margin
    w = max(0.6 - w, 0.0);
    
    // calculate surflet components
    d.x = dot(random3(s), x);
    d.y = dot(random3(s + i1), x1);
    d.z = dot(random3(s + i2), x2);
    d.w = dot(random3(s + 1.0), x3);
    
    // multiply d by w^4
    w *= w;
    w *= w;
    d *= w;
    
    // 3. return the sum of the four surflets
    return dot(d, vec4(52.0));
}


// -----------------------------------------------------------------------------
// const matrices for 3d rotation
const mat3 rot1 = mat3(-0.37, 0.36, 0.85,-0.14,-0.93, 0.34,0.92, 0.01,0.4);
const mat3 rot2 = mat3(-0.55,-0.39, 0.74, 0.33,-0.91,-0.24,0.77, 0.12,0.63);
const mat3 rot3 = mat3(-0.71, 0.52,-0.47,-0.08,-0.72,-0.68,-0.7,-0.45,0.56);

// directional artifacts can be reduced by rotating each octave
// results seems to be between [-0.5, +0.5]
float simplex3d_fractal(vec3 m)
{
    float ret = 0.5333333*simplex3d(m*rot1)
    + 0.2666667*simplex3d(2.0*m*rot2)
    + 0.1333333*simplex3d(4.0*m*rot3)
    + 0.0666667*simplex3d(8.0*m);
    return ret;
}








// -----------------------------------------------------------------------------
// points is result of 2D function f(x,y) = 1/sqrt(sinfunc(x), sinfunc(y))
// arguments are:
// x, y,
// frequency in x, frequency in y,
// amplitude in x, amplitude in y
float makeBlob(float x, float y, float fx, float fy, float sx, float sy, float t)
{
    float sizeReduction = 40.0;
    
    // animating blobs.
    //float xx = x - uMouse.x / uResolution.x;//sin(t * fx) * sx;
    //float yy = y - uMouse.y / uResolution.y;//cos(t * fy) * sy;
    
    float xx = x - sin(t * uMvtSpeed * fx) * sx * uMvtRange;
    float yy = y - cos(t * uMvtSpeed * fy) * sy * uMvtRange;
    
    
    // temporal and spatial deformation
    vec2 pDeformation = vec2(x, y) * uDistortionAmount * sizeReduction * 0.01; // amount of deformation among x and y axis.
    float deformationSpeed = uDistortionSpeed * 0.25;
    float edgeDeformation = simplex3d_fractal(vec3(pDeformation, deformationSpeed * t)); // adding time as 3rd dimension
    edgeDeformation = 0.5 + 0.5*edgeDeformation; // deformation between 0.25 and 0.75
    edgeDeformation *= edgeDeformation;
    
    // music deformation
    float musicTempoFrequency = uBpm / 60.0; // 120bpm = 120 / 60 = 2 Htz
    float musicTempoDeformation = sin(2 * 3.14159265359 * t * musicTempoFrequency);
    float musicTempoDeformationAmplitude = uBpmAmplitude * 0.01;
    musicTempoDeformation = 1 + musicTempoDeformationAmplitude * musicTempoDeformation;
    /*
     // limit deformation of tempo into a more heart beat like function
     musicTempoDeformation -= 0.8;
     if (musicTempoDeformation <= 0.0) musicTempoDeformation = 0.0;
     // make deformation be a bigger thing.
     musicTempoDeformation += 1.0;
     */
    
    
    return 1.0 / (sizeReduction * musicTempoDeformation * edgeDeformation * (xx * xx +  yy * yy));
}


// -----------------------------------------------------------------------------
float blobsShape(vec2 p, float blobVal, float blobReductionFactor)
{
    blobVal /= blobReductionFactor; // reduce size of (1/x2)
    blobVal = smoothstep(0.3, 1.0, blobVal); // threesold
    
    if (blobVal < 0.8)
    {
        blobVal = 0.0;
    }
    return blobVal;
}

// -----------------------------------------------------------------------------
vec3 colorizeBlobs(vec2 p, float blobVal, vec3 blobMainColor,
                   float innerNoiseSpeed, float innerNoiseScale, float innerNoiseDepth,
                   float colorShadingRange)
{
    // Solid clor
    vec3 ret = blobMainColor * blobVal ;// + coloredNoise;
    
    // making global inner noise.
    vec3 p3 = vec3(p, uGlobalTime * innerNoiseSpeed);
    float noiseValue = 2.0 * simplex3d_fractal(p3 * innerNoiseScale); // noise value is between -1 and 1
    float noiseSubstracted = 0.15;
    noiseValue *= innerNoiseDepth;  // noise value is between -0.25 and 0.25
    noiseValue += 1.0 - innerNoiseDepth;
    
    ret *= noiseValue;
    
    
    // making collored shade noise.
    /*
    vec3 coloredNoiseRange = blobMainColor * colorShadingRange;
    coloredNoiseRange.r = coloredNoiseRange.r * (2.0 * simplex3d_fractal(p3 + 3.55));
    coloredNoiseRange.g = coloredNoiseRange.g * (2.0 * simplex3d_fractal(p3 + 1.35));
    coloredNoiseRange.b = coloredNoiseRange.b * (2.0 * simplex3d_fractal(p3 + 6.87));
    
    ret += coloredNoiseRange * blobVal;
    */
    
    return ret;
}

// -----------------------------------------------------------------------------

void main()
{
    vec2 p = (2.0 * iFragCoord - uResolution.xy) / uResolution.y;
    
    //vec2 p = iFragCoord.xy / uResolution.xy;
    
    float x = p.x;
    float y = p.y;
    
    float blobsGroup1 = 0;
    float blobsGroup2 = 0;
    float blobsGroup3 = 0;
    float blobsGroup4 = 0;
    
    // blobs group 1
    blobsGroup1  = makeBlob(x, y, 0.25, 0.45, 0.7, 0.6, uGlobalTime);
    blobsGroup1 += makeBlob(x, y, 0.06, 0.4, 0.6, 0.7, uGlobalTime);
    
    blobsGroup1 = blobsShape(p, blobsGroup1, 1.0);
    
    
    // blobs group 2
    blobsGroup2  = makeBlob(x, y, 0.16, 0.61, 0.6, 0.5, uGlobalTime);
    //blobsGroup2 += makeBlob(x, y, 0.36, 0.55, 0.6, 0.8, uGlobalTime);
    
    blobsGroup2 = blobsShape(p, blobsGroup2, 0.5);
    
    // blobs group 3
    blobsGroup3  = makeBlob(x, y, 0.15, 0.25, 0.9, 0.8, uGlobalTime);
    blobsGroup3 += makeBlob(x, y, 0.45, 0.15, 0.8, 0.7, uGlobalTime);
    
    blobsGroup3 = blobsShape(p, blobsGroup3, 1.0);
    
    // blobs group 4
    blobsGroup4 = makeBlob(x, y, 0.10, 0.05, 0.9, 0.9, uGlobalTime);
    
    blobsGroup4 = blobsShape(p, blobsGroup4, 2.5);
    
     
    // final blob coloring
    // blue
    vec3 coloredBlobs1 = vec3(73.4, 104.5, 143.3) / 255.0;
    coloredBlobs1 = colorizeBlobs(p, blobsGroup1, coloredBlobs1, 0.25, 3.0, 0.15, 0.2);
    
    //red
    vec3 coloredBlobs2 = vec3(135.6, 18.9, 8.11) / 255.0;
    coloredBlobs2 = colorizeBlobs(p, blobsGroup2, coloredBlobs2, 0.25, 3.0, 0.08, 0.2);
    
    // yellow
    vec3 coloredBlobs3 = vec3(142.2, 97.2, 38.7) / 255.0;
    coloredBlobs3 = colorizeBlobs(p, blobsGroup3, coloredBlobs3, 0.25, 3.0, 0.15, 0.2);
    
    // green
    vec3 coloredBlobs4 = vec3(14.5, 104.2, 75.7) / 255.0;
    coloredBlobs4 = colorizeBlobs(p, blobsGroup4, coloredBlobs4, 0.25, 3.0, 0.15, 0.2);
    
    
    
    // Color blending
    vec3 d;
    
    if (blobsGroup1 != 0 && blobsGroup2 != 0 && blobsGroup3 != 0)
    {
        d = max(coloredBlobs1, coloredBlobs2);
        d = max(d, coloredBlobs3);
        
    }
    else if (blobsGroup2 != 0 && blobsGroup3 != 0)
    {
        d = vec3(0.8) - max(coloredBlobs2, coloredBlobs3);
        
    }
    else if (blobsGroup1 != 0 && blobsGroup2 != 0)
    {
        d = 0.05 + min(coloredBlobs1, coloredBlobs2);
    }
    else if (blobsGroup1 == 0 && blobsGroup2 == 0 && blobsGroup3 == 0)
    {
        d = coloredBlobs4;
    }
    else
    {
        d = coloredBlobs1 + coloredBlobs2 + coloredBlobs3;
    }
    
    
    // alpha
    //alpha = max(coloredBlobs1.r, coloredBlobs1.g); most interesting technique
    //alpha = max(alpha, coloredBlobs1.b);
    
    //alpha = coloredBlobs1.b
    
    float alpha = blobsGroup1 + blobsGroup2 + blobsGroup3 + blobsGroup4; // allow to be transparent when no blob
    alpha /= blobsGroup1 + blobsGroup2 + blobsGroup3 + blobsGroup4;
    
    //alpha *= 0.8;
    
    // Out
    oColor = vec4(d, alpha);
}
