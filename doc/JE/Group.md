#Group
##JE::Group
###Description
A class that manages groups of entities and other groups.  
Do not inherit, instead you should inherit World.  

###Constructors
#####Group(int order = JE_ORDER_NONE, int drawmode = JE_WORLD_MODE_ALL, int updatemode = JE_WORLD_MODE_ALL)
Creates a new group.  
order: the order of entities.  
drawmode: the drawing order of entities.
updatemode: the updating order of entities.

###Callbacks
#####void Group::begin()
Called when the group is initiated.
#####void Group::update(int group = -1)
Called when the group is updated.  
group: the group to update. Defaults to updating all entities.
#####void Group::draw(int group = -1)
Called when the group is drawn. 
group: the group to draw. Defaults to drawing all entities.
#####void Group::end()
Called when the group is ended.  

###Methods
#####void Group::add(Entity* entity)
Adds an entity to the group.  
entity: the entity to add to the group.  
#####void Group::remove(Entity* entity)
Removes an entity from the group.  
entity: the entity to remove from the group.
####Movement methods
#####void Group::move(int from, int to)
Moves an entity from one position to another using IDs.
from: the ID of entity to move(use Group::getID)  
to: the ID to move the entity to(use Group::getID)  
#####void Group::moveToBack(int from)
Moves an entity to the back  
from: the ID of entity to move(use Group::getID)  
#####void Group::moveToFront(int from)
Moves an entity to the front  
from: the ID of entity to move(use Group::getID)  
#####void Group::moveUp(int from)
Moves an entity up one ID  
from: the ID of entity to move(use Group::getID)  
#####void Group::moveDown(int from)
Moves an entity down one ID  
from: the ID of entity to move(use Group::getID)  
#####void Group::swap(int a, int b)
Swaps the position of two entities(A and B)
a: the ID of entity A(use Group::getID)  
b: the ID of entity B(use Group::getID)  
#####int Group::getID(Entity* entity)
Gets the ID of an entity for moving. Returns -1 if invalid.
entity: the ID of the entity to get the ID of.
####Clearing methods
#####void Group::clear()
Removes all entities from the group.
#####void Group::clear(int group)
Removes all entities from a sub-group.  
group: the group to remove.
#####void Group::clearAll()
Removes all entities and groups from group.
#####void Group::changeOrder(int order)
Change the order of the group.  
order: the order to change to.
####Group management methods
#####void Group::addToGroup(Entity* entity, unsigned int group)
Adds an entity to a group.  
entity: the entity to add.  
group: the group ID to add to.
#####void Group::removeFromGroup(Entity* entity, unsigned int group)
Removes an entity from a group.  
entity: the entity to remove.  
group: the group ID to remove from.
#####Group* Group::getGroup(unsigned int index)
Returns a group pointer with a group ID.  
index: the group ID to use.
#####void Group::addGroup(unsigned int group, int order = -1, int drawmode = -1, int updatemode = -1)
Creates a new group within the group.  
order: the order of entities.  
drawmode: the drawing order of entities.
updatemode: the updating order of entities.
#####void Group::removeGroup(unsigned int group)
Removes a group from the group.  
group: the group ID to remove.

###Variables
#####std::vector<Group*> groups
A list of groups withing the group.
#####std::vector<Entity*> entities
A list of entities within the group.
#####int order
The order of entities.
#####int drawMode
The drawmode of the group.
#####int updateMode
The updatemode of the group.
