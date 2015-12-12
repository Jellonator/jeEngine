#include "JE/GRAPHIC/jeGraphic.h"
#include "JE/UTIL/jeString.h"
#include "JE/UTIL/jeMath.h"
#include "JE/UTIL/jeTime.h"
#include "JE/jeUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glu.h>
#include <time.h>
namespace JE{

std::string fileOpen(std::string file){
	std::ifstream in(file.c_str());
	std::string text = "";
	std::string temp = "";
	int i = 0;
	if (!in.is_open()) {
		std::cout << "JE: File " << file << " does not exist!" << std::endl;
		text += "JE: File ";
		text += file;
		text += " does not exist!";
		return text;
	}
	while (getline (in,temp))
	{
		i ++;
		//std::cout << i << ":\t" << temp << std::endl;
		text += temp;
		text += '\n';
	}
	//std::cout << text << std::endl;
	return text;
}
namespace STRING{
	int toInt(std::string string){
		int numb;
		std::istringstream(string) >> numb;
		return numb;
	}
	std::vector<std::string> seperateString(std::string string, char seperator){
		std::vector<std::string> strings;
		std::istringstream ss(string);
		while (ss){
			std::string s;
			if (ss.eof()) break;
			if (!getline(ss, s, seperator)) break;
			strings.push_back(s);
		}
		return strings;
	}
}
}
