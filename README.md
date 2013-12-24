jeEngine
========
jeEngine is a cross-platform game engine written in C++, currently supporting whatever SDL supports.
Using it is meant to be simple, and the engine is meant to be as small and flexible as possible.
Libraries/dependancies:
- SDL2
- SDL2_image
Current Version: 0.2
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

Update log
--------
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


