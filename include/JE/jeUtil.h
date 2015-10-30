#pragma once
#include <vector>
#include <string>
#include <map>
#include "GRAPHIC/jeGraphic.h"
namespace JE{
extern bool should_resize;
extern bool fix_resize;
/** \brief Prints string to console output.
 * \param string s, string to print.
 */
std::string fileOpen(std::string file);

namespace STRING{
	int toInt(std::string string);
	std::vector<std::string> seperateString(std::string string, char seperator);
};
template<typename Type>
void clearPointerVector(std::vector<Type*>* vector){
	while (!vector->empty()){
		Type* t = vector->back();
		vector->pop_back();
		delete t;
	}
	vector->clear();
}
template<typename KType, class VType>
void clearPointerMap(std::map<KType, VType*>* vector){

	typename std::map<KType, VType*>::iterator iter;
	for (iter = vector->begin(); iter != vector->end(); ++iter) {
		delete iter->second;
	}
	vector->clear();
}
}
