jeEngine
========
jeEngine is a platform-independent game engine written in C++.
Using it is meant to be simple, and the engine is meant to be as small and flexible as possible.

Downloads
--------
Although you can install it by compiling the source code, I will provide downloads anyways.
- Linux: https://dl.dropboxusercontent.com/u/55433941/downloads/JelloEngine/JelloEngine-Linux_1_0_0.tar.gz
- Windows and Mac: coming soon!(For now you need to compile it)

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
	MyEntity() : jeEntity(){}
	void OnUpdate(){jePrint("Hello World!");}
};
int main(){
	jeWorld::set(new jeWorld());
	jeWorld::add(new MyEntity());
	jeWorld::update();
}
```

More examples comming soon.

Todo
--------
- [ ] Collision grid
- [ ] Nested groups
- [ ] Documentation
- [ ] Filesystem
