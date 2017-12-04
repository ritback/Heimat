//
//  ofxShadertoy.cpp
//  RayWarper
//
//  Created by Tiago Rezende on 6/26/15.
//
//

#include "ofxShadertoy.h"

ofxShadertoy::ofxShadertoy():globalTime(0),advanceTime(true),dimensions(640.f, 480.f) {
    ofAddListener(ofEvents().update, this, &ofxShadertoy::update);
}
ofxShadertoy::~ofxShadertoy() {
    ofRemoveListener(ofEvents().update, this, &ofxShadertoy::update);
}

bool ofxShadertoy::load(string shaderfilename) {
    ofShader currentShader;
    currentShader.setupShaderFromSource(GL_VERTEX_SHADER, string("#version 330\n"
                                                                 "precision mediump float;"
                                                                 "uniform mat4 modelViewProjectionMatrix;"
                                                                 "uniform mat4 tCameraMatrix;"
                                                                 "in vec4 position;"
                                                                 "void main(){"
                                                                 "    gl_Position = modelViewProjectionMatrix * position;"
                                                                 "}\n"));
    ofFile f;
    f.open(shaderfilename);
    ofBuffer b = f.readToBuffer();
    string fragprogram =
    string("#version 330\n"
           "precision mediump float;\n"
           //"vec4 texture2D(sampler2DRect tex, vec2 coords) { return texture(tex, coords*512.0+vec2(512,-512)); }\n"
           "vec4 texture2D(sampler2D tex, vec2 coords) { return texture(tex, coords.xy); }\n"
           "#define texture2DCube texture\n"
           "uniform vec3      iResolution;\n"
           "uniform float     iGlobalTime;\n"
           "uniform float     iTime;\n"
           "uniform int       iFrame;\n"
           "uniform float     iChannelTime[4];\n"
           "uniform vec4      iMouse;\n"
           "uniform vec4      iDate;\n"
           "uniform float     iSampleRate;\n"
           "uniform vec3      iChannelResolution[4];\n"
           "uniform mat4      tCameraMatrix;\n")+
    b.getText()+
    string("\nout vec4 FragColor;"
           "void main( void )"
           "{"
           "vec4 color = vec4(0.0,0.0,0.0,1.0);"
           "mainImage( color, gl_FragCoord.xy );"
           "color.w = 1.0;"
           "FragColor = color;"
           "}");
    if(!currentShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragprogram)) {
        ofLogError("shader") << "error loading shader";
        return false;
    } else {
        if(currentShader.linkProgram()) {
            currentShader.bindDefaults();
            currentShader.setUniform1f("iGlobalTime", ofGetElapsedTimef());
            currentShader.setUniform4f("iMouse", mousepos.x, mousepos.y, ofGetMousePressed()?1:0, 0);
            dimensions.set(ofGetWindowWidth(), ofGetWindowHeight());
            currentShader.setUniform3f("iResolution", dimensions.x, dimensions.y, 4.0f);
            currentShader.setUniform4f("iDate", ofGetYear(), ofGetMonth(), ofGetDay(), ((ofGetHours()*60+ofGetMinutes())*60)+ofGetSeconds());
            currentShader.setUniformMatrix4f("tCameraMatrix", ofMatrix4x4::newIdentityMatrix());
            shader = currentShader;
            return true;
        } else {
            ofLogError("shader") << "did not link";
            return false;
        }
    }
}

void ofxShadertoy::begin() const {
    shader.begin();
    shader.setUniform1f("iGlobalTime", globalTime);
    shader.setUniform1f("iTime", globalTime);
    shader.setUniform4f("iMouse", mousepos.x, mousepos.y, ofGetMousePressed()?1:0, 0);
    shader.setUniform3f("iResolution", dimensions.x, dimensions.y, 4.0f);
    shader.setUniform4f("iDate", ofGetYear(), ofGetMonth(), ofGetDay(), ((ofGetHours()*60+ofGetMinutes())*60)+ofGetSeconds());
    
    shader.setUniformMatrix4f("tCameraMatrix", ofMatrix4x4::newIdentityMatrix());
    

}

void ofxShadertoy::end() const {
    shader.end();
}

void ofxShadertoy::draw(float x, float y, float z, float w, float h) const {
    begin();
    ofDrawRectangle(x, y, z, w, h);
    end();
}

void ofxShadertoy::update(ofEventArgs &event) {
    if(advanceTime) {
        globalTime += ofGetLastFrameTime();
    }
    if(useMouse && ofGetMousePressed()) {
        mousepos.set(ofGetMouseX(), ofGetMouseY());
    }
}

void ofxShadertoy::setAdvanceTime(bool advance) {
    advanceTime = advance;
}

void ofxShadertoy::setUseMouse(bool use) {
    useMouse = use;
}
