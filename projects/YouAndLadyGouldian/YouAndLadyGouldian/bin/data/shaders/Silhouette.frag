#version 150

uniform vec3            uResolution;           // viewport resolution (in pixels)
uniform float           uGlobalTime;           // shader playback time (in seconds)
// blobs parameters
//uniform float           uBpm;

in vec2 iFragCoord; // coordinate in pixel.
in vec2 iChannelCoord0;

out vec4 oColor;



// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

void main()
{
    vec2 p = (2.0 * iFragCoord - uResolution.xy) / uResolution.y;
    
    //vec2 p = iFragCoord.xy / uResolution.xy;
    
    // Out
    oColor = vec4(0.0);
}
