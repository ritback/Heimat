#version 150

uniform vec3            uResolution;           // viewport resolution (in pixels)
uniform float           uGlobalTime;           // shader playback time (in seconds)

uniform sampler2DRect	uSilhouetteTexture;
uniform vec3            uSilhouetteTextureRes;

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



vec2 offset( vec2 p, float phase )
{
	return vec2(simplex3d_fractal(vec3(p.xy * 10, phase)), simplex3d_fractal(vec3(p.yx * 10, phase)));
}



// -----------------------------------------------------------------------------

const float heatAmount = 0.04;

void main()
{
    vec2 p = iFragCoord.xy / uResolution.xy;
	float phase = uGlobalTime * 0.1;

	vec2 pBackground1 = (p + heatAmount * offset(p, phase)) * uSilhouetteTextureRes.xy;
	vec2 pBackground2 = (p + heatAmount * offset(p, phase + 0.5849)) * uSilhouetteTextureRes.xy;
    
	vec4 s1 = texture(uSilhouetteTexture, pBackground2);
	vec4 s2 = texture(uSilhouetteTexture, pBackground2);

	vec4 depth =  mix(s1, s2, abs(2 * (sin(phase*2.0) - 0.5)));

	float alpha = 0.0;
	if (depth.r > 0.5)
	{
		alpha = 0.5;
	}
	
	depth.r = 0.0;
	depth.b = 0.0;
	depth.g = 0.0;
	depth.a = alpha;

    // Out
    //oColor = mix(s1, s2, abs(2 * (sin(phase*2.0) - 0.5)));
    oColor = depth;
}
