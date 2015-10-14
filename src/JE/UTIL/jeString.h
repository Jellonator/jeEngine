#pragma once
#include <sstream>
#include <string>
namespace JE{
	namespace STRING{
		template <class Type>
		std::string toString(Type value){
			std::stringstream ss;
			ss << value;
			return ss.str();
		}
	}
}