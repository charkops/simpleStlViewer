#pragma once

#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace simpleStlViewer {
  struct Shader {
    // Programm ID
    unsigned int ID;

    // Reads and build the shader
    Shader(const char *vertexPath, const char *fragmentPath);

    ~Shader() = default;

    // Activate shader
    void use();

    // Utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
  };

}