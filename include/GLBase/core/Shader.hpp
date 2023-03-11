#pragma once

#include <string_view>
#include <unordered_map>
#include <string>
#include <GLBase/math/Matrix.hpp>

namespace GLBase
{
    // Represents an OpenGL GLSL shader
    class Shader
    {
    private:
        unsigned _vsId=0, _fsId=0;
        unsigned _prog=0;
        bool _valid = false;
        std::unordered_map<std::string, int> _uniformCache;

    public:
        // Initializes the shader without setting any code
        Shader();
        /* Constructs the shader with the provided source code
        @param vertexShaderCode: The source code for the vertex shader
        @param fragShaderCode: The source code for the fragment shader
        */
        Shader(std::string_view vertexShaderCode, std::string_view fragShaderCode);
        // Indicates the object represents a valid shader
        bool isValid() const;
        // Returns the same as isValid
        operator bool() const;
        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other);
        Shader& operator=(Shader&& other);

        /* Recompiles the shader with a new source code
        @param vertexSource: The source code for the vertex shader
        @param fragmentSource: The source code for the fragment shader
         */
        void setSource(std::string_view vertexSource, std::string_view fragmentSource);
        // Binds the shader
        void bind() const;
        // Unbinds the shader
        void unbind() const;

        /* Gets the location of a uniform, if it exists 
        @param name: The name of uniform to look for
        @return The location of the uniform, or -1 if it wasn't found or if the shader is invalid
        */ 
        int getUniformID(std::string_view name);

        void setUniform(std::string_view name, float v0);
        void setUniform(std::string_view name, float v0, float v1);
        void setUniform(std::string_view name, float v0, float v1, float v2);
        void setUniform(std::string_view name, float v0, float v1, float v2, float v3);

        void setUniform(std::string_view name, int v0);
        void setUniform(std::string_view name, int v0, int v1);
        void setUniform(std::string_view name, int v0, int v1, int v2);
        void setUniform(std::string_view name, int v0, int v1, int v2, int v3);

        void setUniform(std::string_view name, unsigned v0);
        void setUniform(std::string_view name, unsigned v0, unsigned v1);
        void setUniform(std::string_view name, unsigned v0, unsigned v1, unsigned v2);
        void setUniform(std::string_view name, unsigned v0, unsigned v1, unsigned v2, unsigned v3);
        void setUniform(std::string_view name, const GLBase::Matrix44& M);

        /* Sets a callback function that will get called whenever a GLSL related error occurs
        @param cbk: A pointer to the function. This function must take the error message as the first argument, and takes a user defined pointer as a second argument
        @param context: User defined pointer that will be passed to the callback
         */
        static void setGLSLErrorCallback(void (*cbk)(const char* msg, void *context), void *context);
        ~Shader();
    };
    
} // namespace GLBase
