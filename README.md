jeEngine
========
jeEngine is a platform-independent game engine written in C++.
Using it is meant to be simple, and the engine is meant to be as small and flexible as possible.
Current Version: 0.1
Features
--------
- Worlds
- Entities
- Groups
- Collision

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
	JE::world->update();
	return 0;
}
```

More examples comming soon.

Update log
--------
### Version 0.1 ###
- Initial release
- Added worlds and groups
- Added entities
- Added collision

Todo
--------
- [x] Nested groups
- [x] Documentation
- [ ] Collision grid
- [ ] Filesystem
