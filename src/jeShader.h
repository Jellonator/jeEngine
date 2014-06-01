#pragma once
#include "JE.h"
namespace JE{namespace GRAPHICS{
class Shader
{
	public:
		std::map<std::string, GLint> attributes;
		GLuint shader;
		void addAttribute(std::string name);
		void addAttribute(std::string name, std::string key);
		void removeAttribute(std::string name);
		void load(std::string data);
		void enableAttributes();
		void disableAttributes();
		Shader();
		virtual ~Shader();
	protected:
	private:
};
namespace SHADERS{

};
};};
