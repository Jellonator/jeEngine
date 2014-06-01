#pragma once
#include "JE.h"
namespace JE{namespace GRAPHICS{
class Shader;
class Program
{
	public:
		std::vector<Shader*> shaders;
		GLuint program;
		void addShader(Shader* shader);
		void begin();
		void end();
		Program();
		virtual ~Program();
	protected:
	private:
};
};};
