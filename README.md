jeEngine
========
jeEngine is a platform-independent game engine written in C++.
Using it is meant to be simple, and the engine is meant to be as small and flexible as possible.

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

Todo
--------
- [ ] Collision grid
- [ ] Nested groups
- [ ] Documentation
- [ ] Filesystem
