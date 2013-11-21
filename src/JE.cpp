#include "JE.h"
void jePrint(std::string s){std::cout << s << std::endl;}

namespace JE
{
	jeWorld* world;/**< \brief jeWorld* world, the active world. */
	std::vector<jeGroup*> groups;
	std::vector<bool> __GREMOVED__;
	std::vector<unsigned int> __IREMOVED__;
};

void jeAddGroup(jeGroup* group){
	if (JE::__IREMOVED__.size() > 0){
	//If there is free space
		//Set the entity's index
		group->__INDEX__ = JE::__IREMOVED__.back();
		//Add it to the empty spot
		JE::groups[JE::__IREMOVED__.back()] = group;
		//Clean up the removal vectors
		JE::__GREMOVED__[JE::__IREMOVED__.back()] = false;
		JE::__IREMOVED__.pop_back();
	}else{
	//Otherwise push it to the back
		//set the entity's index to the back
		group->__INDEX__ = JE::groups.size();
		//And push it to the back
		JE::groups.push_back(group);
		JE::__GREMOVED__.push_back(false);
	}
}

void jeRemoveGroup(jeGroup* group){
	//remove all of it's entities
	for (unsigned int i = 0; i < group->entities.size(); i ++){
		group->remove(group->entities[i]);
	}
	//assign the group to NULL and make sure the engine knows it's gone
	JE::groups[group->__INDEX__] = NULL;
	JE::__GREMOVED__[group->__INDEX__] = true;
	JE::__IREMOVED__.push_back(group->__INDEX__);
	//remove all of the NULL groups starting from the back, until it runs into a group
	for (int i = JE::groups.size() - 1; i >= 0; i --){
		if (JE::groups[i] == NULL) {
			JE::groups.pop_back();
			JE::__GREMOVED__.pop_back();
			} else { i = -1; }
	}
	bool done = false;
	int i = 0;
	//Now make sure to update IREMOVED
	while (done == false){
		if (JE::__IREMOVED__[i] >= JE::groups.size()){
			JE::__IREMOVED__.erase(JE::__IREMOVED__.begin() + i);
			i --;
		}
		i ++;
		if (i >= JE::__IREMOVED__.size()) done = true;
	}
	//Cleanup
	delete group;
	group = NULL;
}

