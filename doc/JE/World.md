#World
##JE::WORLD
###Description
World is a class that is an abstraction to Group.  
For additional functions, also see Group.md.  
Inherits Group

###Constructors
#####World(int order = JE_ORDER_NONE, int drawmode = JE_WORLD_MODE_ALL, int updatemode = JE_WORLD_MODE_ALL)
Creates a new world.  
order: the order of entities.  
drawmode: the drawing order of entities.
updatemode: the updating order of entities.

###Callbacks
#####void OnBegin()
Called when the world is set via setWorld().
#####void onUpdate()
Called when the world is updated.
#####void OnDraw(){};
Called when the entity is drawn.
#####void onEnd(){};
Called when the world is replaced by a different world via setWorld().

###Methods(class functions)
All methods can be found in Group.md.

###Functions
#####void setWorld(World* world)
Sets the active world.
world: the world to set as the active world.
