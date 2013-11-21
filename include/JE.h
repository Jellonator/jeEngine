#ifndef JE_H
#define JE_H

#include <vector>
#include <cstddef>
#include <string>
#include <iostream>
#include <cmath>
#include <cstring>

void jePrint(std::string s);

enum JE_ORDER{JE_ORDER_NONE, JE_ORDER_HALF, JE_ORDER_FULL};
enum JE_WORLD_MODE{JE_WORLD_MODE_NONE, JE_WORLD_MODE_ALL, JE_WORLD_MODE_GROUP};
enum JE_MASK_TYPE{JE_MASK_NONE, JE_MASK_BOX, JE_MASK_GRID, JE_MASK_LIST};

class jeWorld;
class jeEntity;
class jeGraphic;
class jePoint;
class jeMask;
class jeHitBox;
#include "jeGroup.h"

namespace JE
{
	extern jeWorld* world;/**< \brief jeWorld* world, the active world. */
	extern std::vector<jeGroup*> groups;
	extern std::vector<bool> __GREMOVED__;
	extern std::vector<unsigned int> __IREMOVED__;
};
void jeAddGroup(jeGroup* group);
void jeRemoveGroup(jeGroup* group);

#include "jeEntity.h"
#include "jeWorld.h"
#include "jeGraphic.h"
#include "jePoint.h"
#include "jeMask.h"

#endif // JE_H
