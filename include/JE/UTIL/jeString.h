#pragma once
#include <sstream>
#include <string>
namespace JE{
	namespace STRING{
		template <class Type>
		std::string toString(Type value){
			std::stringstream ss;
			ss << value;
			std::string ret = ss.str();
			
			// Code that adds comma seperators
			std::string::size_type i = ret.find('.');
			if (i == ret.npos) i = ret.size()-1;
			i -= 2;
			
			while (i > 0 && i < ret.size()){
				ret.insert(i, ",");
				i -= 3;
			}
			
			return ret;
		}
	}
}