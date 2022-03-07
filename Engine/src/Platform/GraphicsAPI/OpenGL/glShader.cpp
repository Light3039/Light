#include "glShader.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/matrix.hpp>


namespace Light {

glShader::glShader(BasicFileHandle vertexFile, BasicFileHandle pixelFile)
    : m_ShaderID(0u)
{
	// create
	m_ShaderID = glCreateProgram();

	std::string vertexSource(vertexFile.GetData(), vertexFile.GetData() + vertexFile.GetSize());
	std::string pixelSource(pixelFile.GetData(), pixelFile.GetData() + pixelFile.GetSize());

	unsigned int vertexShader = CompileShader(vertexSource, Shader::Stage::VERTEX);
	unsigned int pixelShader  = CompileShader(pixelSource, Shader::Stage::PIXEL);

	// attach shaders
	glAttachShader(m_ShaderID, vertexShader);
	glAttachShader(m_ShaderID, pixelShader);

	// link shader program
	glLinkProgram(m_ShaderID);

	// delete shaders (free memory)
	glDeleteShader(vertexShader);
	glDeleteShader(pixelShader);
}

glShader::~glShader()
{
	glDeleteProgram(m_ShaderID);
}

void glShader::Bind()
{
	glUseProgram(m_ShaderID);
}

void glShader::UnBind()
{
	glUseProgram(NULL);
}

shaderc::SpvCompilationResult glShader::CompileGLSL(BasicFileHandle file, Shader::Stage stage)
{
	// compile options
	shaderc::CompileOptions options;
	options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
	options.SetOptimizationLevel(shaderc_optimization_level_performance);

	// compile
	shaderc::Compiler compiler;
	shaderc::SpvCompilationResult result = compiler.CompileGlslToSpv(reinterpret_cast<const char*>(file.GetData()), stage == Shader::Stage::VERTEX ? shaderc_shader_kind::shaderc_vertex_shader : shaderc_shader_kind::shaderc_fragment_shader, file.GetName().c_str(), options);

	// log error
	if (result.GetCompilationStatus() != shaderc_compilation_status_success)
	{
		LT_ENGINE_ERROR("Failed to compile {} shader at {}...", stage == Shader::Stage::VERTEX ? "vertex" : "pixel", file.GetPath());
		LT_ENGINE_ERROR("    {}", result.GetErrorMessage());
	}

	return result;
}

unsigned int glShader::CompileShader(std::string source, Shader::Stage stage)
{
	// &(address of) needs an lvalue
	const char* lvalue_source = source.c_str();
	unsigned int shader       = glCreateShader(stage == Shader::Stage::VERTEX   ? GL_VERTEX_SHADER :
	                                           stage == Shader::Stage::PIXEL    ? GL_FRAGMENT_SHADER :
	                                           stage == Shader::Stage::GEOMETRY ? GL_GEOMETRY_SHADER :
                                                                                  NULL);

	// compile
	glShaderSource(shader, 1, &lvalue_source, NULL);
	glCompileShader(shader);

	// check
	int isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		int logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);

		char* errorLog = (char*)alloca(logLength);
		glGetShaderInfoLog(shader, logLength, &logLength, &errorLog[0]);

		LT_ENGINE_ERROR("glShader::glShader: failed to compile {} shader:\n        {}", stage == Shader::Stage::VERTEX ? "Vertex" : "Pixel", errorLog);

		return NULL;
	}
#define LIGHT_OPENGL_ENABLE_SHADER_INFO_LOG
#ifdef LIGHT_OPENGL_ENABLE_SHADER_INFO_LOG
	// info log
	{
		int logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength)
		{
			char* infoLog = (char*)alloca(logLength);
			glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);

			LT_ENGINE_WARN(infoLog);
		}
	}
#endif

	return shader;
}

} // namespace Light
