#Group
##JE::Group
###Description
A class that manages groups of entities and other groups.  
Do not inherit, instead you should inherit World.  

###Constructors
#####Group(int order = JE_ORDER_NONE, int drawmode = JE_WORLD_MODE_ALL, int updatemode = JE_WORLD_MODE_ALL)
Creates a new group.  
order: the order of entities.  
JE_ORDER NONE means that there is no definite order and the last entity replaces removed entity(fastest at runtime).  
JE_ORDER_HALF means that new entities will fill in holes left by removed entities(fastest when removing).  
JE_ORDER_FULL guarantees that new entities will be placed at the end and removed entities will remove their slot as well(slowest).  

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
#####void Group::move(int from, int to)
#####void Group::clear()
#####void Group::clear(int group)
#####void Group::clearAll()
#####void Group::moveToBack(int from)
#####void Group::moveToFront(int from)
#####void Group::moveUp(int from)
#####void Group::moveDown(int from)
#####int Group::getID(Entity* entity)
#####void Group::changeOrder(int order)
#####void Group::addToGroup(Entity* entity, unsigned int group)
#####void Group::removeFromGroup(Entity* entity, unsigned int group)
#####Group* Group::getGroup(unsigned int index)
#####void Group::addGroup(unsigned int group, int order = -1, int drawmode = -1, int updatemode = -1)
#####void Group::removeGroup(unsigned int group)

###Functions
#####void functionA()
Description
#####bool functionB(Class* class)
Description

###Variables
#####int Class::foo
Description
#####float Class::bar = 0
Description
