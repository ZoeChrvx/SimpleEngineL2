#include "Assets.h"
#include "Log.h"
#include <sstream>

std::map<std::string, Texture> Assets::textures;
static std::map<std::string, Shader> shaders;

Texture Assets::loadTexture(IRenderer& renderer, const string& filename, const string& name)
{
    textures[name] = loadTextureFromFile(renderer, filename.c_str());
    return textures[name];
}

Texture& Assets::getTexture(const string& name) 
{
    if (textures.find(name) == end(textures))
    {
        std::ostringstream loadError;
        loadError << "Texture " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return textures[name];
}

void Assets::clear() 
{
    // (Properly) delete all textures
    for (auto iter : textures)
        iter.second.unload();
    textures.clear();

    // (Properly) delete all shaders
    for (auto iter : shaders)
        iter.second.unload();
    shaders.clear();
}

Shader Assets::loadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& tcShaderFile, const std::string& teShaderFile, const std::string& gShaderFile, const std::string& name)
{
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, tcShaderFile, teShaderFile, gShaderFile);
    return shaders[name];
}

Shader& Assets::getShader(const std::string& name)
{
    if (shaders.find(name) == end(shaders)) {
        std::ostringstream loadError;
        loadError << "Shader " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return shaders[name];
}

Texture Assets::loadTextureFromFile(IRenderer& renderer, const string& filename)
{
    Texture texture;
    texture.load(renderer, filename);
    return texture;
}

Shader Assets::loadShaderFromFile(const std::string& vShaderFile, const std::string& fShaderFile, const std::string& tcShaderFile, const std::string& teShaderFile, const std::string& gShaderFile)
{
    //1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string tcCode;
    std::string teCode;
    std::string geometryCode;
    try {
        //Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        //Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        //Close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        //Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        //If tess control shader path is present, also load a tess control shader
        if (teShaderFile != "") {
            std::ifstream tessControlShaderFile(tcShaderFile);
            std::stringstream tcShaderStream;
            tcShaderStream << tessControlShaderFile.rdbuf();
            tessControlShaderFile.close();
            tcCode = tcShaderStream.str();
        }

        //if tess evaluation shader path is present, also load a tess evaluation shader
        if (teShaderFile != "") {
            std::ifstream tessEvalShaderFile(teShaderFile);
            std::stringstream teShaderStream;
            teShaderStream << tessEvalShaderFile.rdbuf();
            tessEvalShaderFile.close();
            teCode = teShaderStream.str();
        }

        //if geometry shader path is present, also load a geometry shader
        if (gShaderFile != "") {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }

    catch (std::exception e) {
        std::ostringstream loadError;
        std::string geomShaderFile = "";
        if (gShaderFile != "")
            geomShaderFile = gShaderFile;

        loadError << "ERROR::SHADER: Failed to read shader files" << vShaderFile << " " << fShaderFile << " "
            << geomShaderFile << "\n"
            << "\n ---------------------------- "
            << std::endl;
        Log::error(LogCategory::Render, loadError.str());
    }

    const GLchar* vShaderCode = vertexCode.c_str();
    const GLchar* fShaderCode = fragmentCode.c_str();
    const GLchar* tcShaderCode = tcCode.c_str();
    const GLchar* teShaderCode = teCode.c_str();
    const GLchar* gShaderCode = geometryCode.c_str();

    //2. Now create shader object from source code
    Shader shader;
    shader.compile(vShaderCode, fShaderCode,
        tcShaderFile != "" ? tcShaderCode : nullptr,
        teShaderFile != "" ? teShaderCode : nullptr,
        gShaderFile != "" ? gShaderCode : nullptr);
    return shader;
}
