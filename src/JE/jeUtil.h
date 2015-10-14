#pragma once
#include <vector>
#include <string>
#include <map>
#include "GRAPHIC/jeGraphic.h"
namespace JE{
extern bool should_resize;
extern bool fix_resize;
/** \brief Initiates the global window and renderer.
 * \param name std::string, The name of the window.
 * \param SDL_WINDOWPOS_CENTERED int x, The X position of the window.
 * \param SDL_WINDOWPOS_CENTERED int y, The Y position of the window.
 * \param 640 int w, the width of the window.
 * \param 480 int h, the height of the window.
 * \param 0 int wflags, the SDL window flags.
 * \param 0 int rflags, the SDL renderer flags.
 */
void initWindow(std::string name, int w, int h, int wflags = 0, int rflags = 0);
/** \brief Prints string to console output.
 * \param string s, string to print.
 */
std::string fileOpen(std::string file);
void init();/**< \brief Initiates jelloEngine. */
void quit();
void update(bool update_world = true);/**< \brief Updates the engine and the active world. */
void setFramerate(int framerate);
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
