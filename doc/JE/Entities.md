#Entities
##JE::Entity
###Description
A class used to represent an object occupying a world, group, or neither.
Inherits JE::Point

###Constructors
#####Entity();
Creates a new entity.
Do not use ```delete entity```, instead use ```entity->destroy()``` instead.

###Callbacks
#####void Entity::OnCreate()
Called when the entity is created.
#####void Entity::OnAdd(Group* group)
Called when the entity is added to a group.
#####void Entity::OnUpdate()
Called when the entity is updated via JE::update, group->update(), or entity->OnUpdate();
#####void Entity::OnDraw()
Called when the entity is drawn via JE::draw, group->draw(), or entity->OnDraw();
#####void Entity::OnRemove(Group* group)
Called when the entity is removed from a group.

###Methods(class functions)
#####void Entity::setMask(Mask* mask)
Sets the entity's collision mask.
#####void Entity::destroy()
Removes the entity from all groups, then deletes it.

###Variables
#####Mask* mask = NULL
The entity's current collision mask.
