/*#pragma once
#include "jeMain.h"
#include "jeUtil.h"
#include "jeShader.h"
#include <memory>
namespace JE{namespace GRAPHICS{
class Shader;
class Program
{
	public:
    std::vector<std::shared_ptr<Shader>> shaders;
    GLuint program;
		Program();
		virtual ~Program();
		void addShader(std::shared_ptr<Shader> shader);
		void addShader(std::string file, GLint type);
		void addFragmentShader(std::string file);
		void addVertexShader(std::string file);
		void link();
		void use();
	protected:
	private:
};
};};*/
