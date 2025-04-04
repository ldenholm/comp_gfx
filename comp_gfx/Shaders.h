#pragma once
#include <glad/glad.h>
#include <vector>

namespace Shaders {
	class Shaders {
	public:
		static GLuint compile_and_create_shader(GLenum shaderType, const char* shaderSrcPath);
		static GLuint create_and_link_shader_program(std::vector<GLuint>& shaders);
	};
}

namespace Shaders::Vertex {
	//#define vertexShaderSource = \
	//	"#version 330 core\n" \
	//	"layout (location = 0) in vec3 aPos;\n" \
	//	"void main()\n" \
	//	"{\n" \
	//	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n" \
	//	"}\0";

	//const char* vertexIOSrc = 
	//	"#version 330 core\n"
	//	"layout (location = 0) in vec3 aPos;\n"
	//	"out vec4 vertexColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"gl_Position = vec4(aPos, 1.0);\n"
	//	"vertexColor = vec4(0.5, 0.0, 0.0, 1.0);"
	//	"}\n\0";
}

namespace Shaders::Fragment {
	//const char* fragmentShaderSource =
	//	"#version 330 core\n"
	//	"out vec4 FragColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"FragColor = vec4(0.02, 0.01, 0.91, 1.0);\n"
	//	"}\n\0";

	//const char* secondFragShaderSrc =
	//	"#version 330 core\n"
	//	"out vec4 FragColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"FragColor = vec4(0.91, 0.01, 0.01, 1.0);\n"
	//	"}\n\0";

	//const char* FragIOSrc = 
	//	"#version 330 core\n"
	//	"uniform vec4 dynamicColor;"
	//	"out vec4 FragColor;\n"
	//	"void main()\n"
	//	"{\n"
	//	"FragColor = dynamicColor;\n"
	//	"}\n\0";
}