#include "HEHelpers_Shader.h"

HEShaderHelper::HEShaderHelper(const std::string &inShadersFileName)
    : mVertShaderFileName("shaders/" + inShadersFileName + ".vert")
    , mFragShaderFileName("shaders/" + inShadersFileName + ".frag")
{
    load("shaders/" + inShadersFileName);
}

HEShaderHelper::HEShaderHelper(const std::string &inVertShaderFileName,
                   const std::string &inFragShaderFileName)
    : mVertShaderFileName("shaders/" + inVertShaderFileName)
    , mFragShaderFileName("shaders/" + inFragShaderFileName)
{
    load(mVertShaderFileName, mFragShaderFileName);
}

HEShaderHelper::~HEShaderHelper()
{
    
}
