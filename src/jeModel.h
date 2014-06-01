#pragma once
#include "JE.h"
namespace JE{namespace GRAPHICS{
class Program;
class Model
{
	public:
		Program* program;
		float layer;
		void setPoint(int ID, float x, float y);
		void setPoint(int ID, float x, float y, float z);
		void load(std::string file);
		Model();
		virtual ~Model();
	protected:
	private:
};
};};
