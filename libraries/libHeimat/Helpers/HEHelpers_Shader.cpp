#include "HEHelpers_Shader.h"

HEShaderHelper::HEShaderHelper(const std::string &inShadersFileName)
    : mVertShaderFileName("shaders/" + inShadersFileName + ".vert")
    , mFragShaderFileName("shaders/" + inShadersFileName + ".frag")
{
    load("shaders/" + inShadersFileName);
}

HEShaderHelper::HEShaderHelper(const std::string &inShadersFileName,
                               const std::string &inFolderDir)
    : mVertShaderFileName(inFolderDir + "/" + inShadersFileName + ".vert")
    , mFragShaderFileName(inFolderDir + "/" + inShadersFileName + ".frag")
{
    load(inFolderDir + "/" + inShadersFileName);
}

HEShaderHelper::~HEShaderHelper()
{
    
}
