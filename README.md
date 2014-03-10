jeEngine
========
jeEngine is a cross-platform game engine written in C++, currently supporting whatever SDL supports.
Using it is meant to be simple, and the engine is meant to be as small and flexible as possible.

######Libraries/dependancies:######
- SDL2
- SDL2_image

Current Version: 0.4

Features
--------
- Worlds
- Entities
- Groups
- Collision
- Graphics

Examples
--------
```C++
//Hello world
#include "JE.h"
class MyEntity : public jeEntity{
	public:
	MyEntity();
	void OnUpdate();
};
MyEntity::MyEntity() : jeEntity(){

}
void MyEntity::OnUpdate(){
	std::cout << "Hello World!" << std::endl;
}
int main(){
	jeWorld::set(new jeWorld());
	JE::world->add(new MyEntity());
	jeUpdate();
	return 0;
}
```

More examples comming soon.

Todo
--------
- [ ] Particle system

Update log
--------
### Version 0.5 ###
- Added jeEvent*, a class for comparing against SDL_Event and other such things.
- Added jeLine*, experimental, not reccomended for use.
- Reminder that jePoint* and jeCamera* are also experimental and not reccomended for use.
- Added jeEventContainer*, a class for containing jeEvent*s and polling inputs and stuff.
- bugfixes

### Version 0.4 ###
- Added jeData, a class for storing data.
- Added jeSpritemapData, an implimentation of jeData for jeSpritemap.
- Added jeTexture, an implimentation of jeData for jeImage.
- Fixed memory leak in jeImage::load()
- Added jeCopyImage, copies an image.
- Clipping rectangle is no longer automatically generated, and instead will use the texture's size if clip is NULL(jeImage)
- Added jeSetColor and jeSetBackgroundColor, which sets SDL drawing color and background color, respectively.

### Version 0.3 ###
- Added jeGrid, a grid collision system.  Supports oddly sized rectangles.
- Added jeCanvas, a graphic you can draw to and from.
- Added jeTilemap, a graphic that you can use to draw with tilesets.
- Added collision with groups, supports collision sweeping.

### Version 0.2 ###
- Added jeImage, to load and display images.
- Added jeSpritemap, to load and display animated images/spritemaps.
- Added jeCamera, to change the way images are displayed.
- Several bugfixes.

### Version 0.1 ###
- Initial release
- Added worlds and groups
- Added entities
- Added collision


