#pragma once

#include "ofMain.h"

class HEShaderHelper : public ofShader
{
public:
    HEShaderHelper(const std::string &inShadersFileName);
    HEShaderHelper(const std::string &inShaderFileName,
                   const std::string &inFolderDir);
    virtual ~HEShaderHelper();
    
private:
    const std::string mVertShaderFileName;
    const std::string mFragShaderFileName;
};

