#version 150

// Passed in by default from OpenFrameworks
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;

// -----------------------------------------------------------------------------

out vec2 iFragCoord;
out vec2 iChannelCoord0;

// -----------------------------------------------------------------------------

void main()
{
    iFragCoord = position.xy;
    iChannelCoord0 = texcoord;
    gl_Position = modelViewProjectionMatrix * position;
}




precision mediump float;
uniform mat4 modelViewProjectionMatrix;
uniform mat4 tCameraMatrix;
in vec4 position;
void main(){
    gl_Position = modelViewProjectionMatrix * position;
