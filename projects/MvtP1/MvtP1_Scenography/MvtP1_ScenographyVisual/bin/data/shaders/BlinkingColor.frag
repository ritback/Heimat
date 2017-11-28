#version 150

uniform vec3            uResolution;           // viewport resolution (in pixels)
uniform float           uGlobalTime;           // shader playback time (in seconds)
uniform float           uColorChangeSpeed;
uniform float           uBrightness;
uniform float           uColorAmount;
uniform float           uAlpha;

in vec2 iFragCoord; // coordinate in pixel.
in vec2 iChannelCoord0;

out vec4 oColor;


// -----------------------------------------------------------------------------
#define HASHSCALE1 443.8975

float hash11(float p)
{
    vec3 p3  = fract(vec3(p) * HASHSCALE1);
    p3 += dot(p3, p3.yzx + 19.19);
    return fract((p3.x + p3.y) * p3.z);
}

float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float noise(float p)
{
    float i = floor(p);
    float f = fract(p);
    
    float t = f * f * (3.0 - 2.0 * f);
    
    return lerp(f * hash11(i), (f - 1.0) * hash11(i + 1.0), t);
}

float fbm(float x, float persistence, int octaves)
{
    float total = 0.0;
    float maxValue = 0.0;
    float amplitude = 1.0;
    float frequency = 1.0;
    
    for(int i=0; i<octaves;++i)
    {
        total += noise(x * frequency) * amplitude;
        maxValue += amplitude;
        amplitude *= persistence;
        frequency *= 2.0;
    }
    
    return (total/maxValue);
}

// -----------------------------------------------------------------------------
float scalingMap(float inValue, float baseMin, float baseMax, float limitMin, float limitMax)
{
    return ((limitMax - limitMin) * (inValue - baseMin) / (baseMax - baseMin)) + limitMin;
}


// -----------------------------------------------------------------------------
void main()
{
    vec3 color = vec3(0);
    
    color.r = uBrightness * (fbm(uGlobalTime * uColorChangeSpeed + 0.235, 0.5, 4) + 0.5);
    color.g = uBrightness * (fbm(uGlobalTime * uColorChangeSpeed + 4.675, 0.5, 4) + 0.5);
    color.b = uBrightness * (fbm(uGlobalTime * uColorChangeSpeed + 15.64, 0.5, 4) + 0.5);
    
    
    float strechingValue = -uColorAmount;
    color.r = scalingMap(color.r, 0.0, 1.0, strechingValue, 1.0 - strechingValue);
    color.g = scalingMap(color.g, 0.0, 1.0, strechingValue, 1.0 - strechingValue);
    color.b = scalingMap(color.b, 0.0, 1.0, strechingValue, 1.0 - strechingValue);
    
    color = clamp(color, vec3(0.0), vec3(1.0));
    float alpha = clamp(uAlpha, 0, 1);
    oColor = vec4(color, alpha);
}



