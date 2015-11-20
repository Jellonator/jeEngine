jeEngine
========
jeEngine, or Jello's Engine, is a cross-platform game engine written in C++, currently supporting whatever SDL supports.
Note that this engine is mostly just a wrapper for SDL2 and OpenGL. Currently uses the heavily outdated OpenGL 1.2 standard.
There are plans to impliment OpenGL 3.2 in the future.

######Libraries/dependancies:######
- SDL2
- SDL2_image

Current Version: 0.9.0

Features
--------
- Entities
- Groups
- Collision
- Graphics

Examples
--------
```C++
//Hello world
#include "JE/JE.h"
#include <iostream>

class MyEntity : public JE::Entity{
	public:
	MyEntity();
	void OnUpdate(JE::Group& group, float dt);
};
MyEntity::MyEntity() : JE::Entity(){

}
void MyEntity::OnUpdate(JE::Group& group, float dt){
	std::cout << "Hello World!" << std::endl;
}
int main(){
	JE::init();
	
	JE::Group world;
	world.add<MyEntity>();
	JE::update();
	world.update(0);
	
	return 0;
}
```
More examples coming soon.

Todo
--------
- Impliment OpenGL 3.2
- Make JE::GRAPHICS::Camera less weird and awkward.
- Actual documentation.

Update log
--------
### Version 0.9.0 ###
- Revised a lot of things to be more modern and flexible and a few other buzzwords.
- Added components to the entity system.
- Reimplimented a new collision system, this time using integer positions.
- Current types of Mask are PointMask(single point), Hitbox(AABB rectangle), Multimask(Combination of masks), and Grid(optimized Multimask).
- Particle systems are a lot more optimized, including an option to have a custom Particle system renderer.
- A lot of systems now use string IDs instead of integer IDs.
- Entity system is a lot different now. No more groups embedded in groups, there is no World class or global world object anymore.
- Added and revised a couple math functions

### Version 0.8 ###
- Added JE::MATH::toInt(string) and JE::MATH::toString(int)
- Added JE::TIME::setDeltaTimeLimit to make things not jittery when doing intensive processes
- A ton of new functions in JE::MATH
- Added JE::fileOpen
- Added clear() and resize(width, height) functions to JE::GRAPHICS::Canvas
- Added the beginnings of a GUI system(Frame, Divider)
- Added layering for entities
- Added Grid sides, which allow for entities to only collide with one side of a grid tile(currently only top-only collision is implimented)
- Added custom collision functions for JE::Mask
- Added a deleteAll function to Group
- Masks now all have a debug draw function
- Added setColor and getSize to Image
- Added more JE::MASK::Line functions
- Added JE::MASK::push and JE::MASK::pushGroup, which pushes entities outside of other entities, so that they don't collide.
- Spritemaps can now be initialized with files, and now have functions to draw specific frames.

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


