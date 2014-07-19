jeEngine
========
jeEngine is a cross-platform game engine written in C++, currently supporting whatever SDL supports.

######Libraries/dependancies:######
- SDL2
- SDL2_image

Current Version: 0.7.1

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
class MyEntity : public JE::Entity{
	public:
	MyEntity();
	void OnUpdate();
};
MyEntity::MyEntity() : JE::Entity(){

}
void MyEntity::OnUpdate(){
	JE::print("Hello World!");
}
int main(){
	JE::init();
	JE::world->add(new MyEntity());
	JE::update();
	return 0;
}
```
More examples coming soon.

Todo
--------

Update log
--------
### Version 0.7 ###
- Added a few functions to JE::MATH
- Added particle system
- Fixed major bugs in World/Group class.

#### Version 0.7.1 ####
- Added JE::MATH::random(a, b) which returns a random float between a and b.
- Added JE::MATH::chance(x) which has an X percent chance of return true.
- Added JE::MATH::chance(a, b) which is the same as chance(x), but as a fraction (e.g. 1/4 chance would be chance(1, 4)).
- Fixed Hitbox collision inaccuracies.
- Changed JE::Data a bit.
- Fixed particles crashing on Windows.
- Fixed canvases clearing when resizing on Windows.
- Updated JE::Spritemap and JE::Tilemap to be easier to manage, they now use JE::Data.
- Probably a few other things.

### Version 0.6 ###
- Now uses namespaces, everything is now under JE::
- Added JE::EVENT:: namespace
- Added JE::GRAPHICS:: namespace
- Added JE::MATH:: namespace
- Added JE::MASK:: namespace
- Added JE::TIME:: namespace

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


