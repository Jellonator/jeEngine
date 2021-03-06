#include "JE/jeGroup.h"
#include "JE/jeEntity.h"
#include <algorithm>
#include <iostream>
namespace JE{

Group::Group(){
	this->needUpdateEntityLayering = false;
	this->do_sort = true;
	this->correct_remove = true;
}

Group::~Group(){
	//this->deleteAll();
}

void Group::update(float dt){
	this->updateEntities();
	for (auto& entity : this->entities){
		entity->OnUpdate(*this, dt);
	}
	this->updateEntities();
}

void Group::draw(){
	this->updateEntities();
	for (auto& entity : this->entities){
		entity->OnDraw();
	}
	this->updateEntities();
}

void Group::remove(Entity& entity){
	/*entity_vec_iter iter = this->entities.begin();
	while (iter != this->entities.end()){
		//dereference iterator -> dereference unique_ptr -> pointer
		if (iter->get() == &entity) this->remove(iter);
		++iter;
	}*/
	this->entities_remove.push_back(&entity);
}

struct sort_entity_by_layer
{
    inline bool operator() (const Entity& entity_a, const Entity& entity_b)
    {
        return (entity_a.getLayer() < entity_b.getLayer());
    }
};

void Group::updateEntities(){
	//Remove entities that are marked as removed
	if (this->entities_remove.size() > 0) std::cout << "Removing " << this->entities_remove.size() << " entities" << std::endl;
	for (std::vector<Entity*>::iterator rm_iter = this->entities_remove.begin(); rm_iter != this->entities_remove.end(); ++rm_iter){
		Entity* entity = *rm_iter;
		//Remove entity from groups
		while (entity->_groups_v.size() > 0){
			this->removeFromGroup(*entity->_groups_v.begin(), *entity);
		}
		
		//Actually remove entity
		entity_vec_iter entity_iter = this->entities.begin();
		while (entity_iter != this->entities.end()){
			if (entity_iter->get() == entity){
				entity_iter = this->entities.erase(entity_iter);
			} else {
				++entity_iter;
			}
		}
		
	}
	this->entities_remove.clear();
	
	//Add entities to entity list
	for (entity_vec_iter iter = this->entities_add.begin(); iter != this->entities_add.end(); ++iter){
		this->entities.push_back(std::move(*iter));
	}
	this->entities_add.clear();
	
	//Sort entities if need sorting
	if (this->needUpdateEntityLayering && this->do_sort){
		std::sort(this->entities.begin(), this->entities.end(),  [ ]( const std::unique_ptr<Entity>& lhs, const std::unique_ptr<Entity>& rhs )
		{
		   return lhs->getLayer() < rhs->getLayer();
		});
		this->needUpdateEntityLayering = false;
	}
}

void Group::clear(){
	this->entities.clear();
	this->entities_add.clear();
	this->entities_remove.clear();
}

void Group::setSort(bool sort){
	this->do_sort = sort;
}

void Group::setCorrectRemove(bool do_correct_remove){
	this->correct_remove = do_correct_remove;
}

entity_vec::size_type Group::getSize() const{
	return this->entities.size();
}

entity_vec::iterator Group::getBegin(){
	return this->entities.begin();
}

entity_vec::iterator Group::getEnd(){
	return this->entities.end();
}

bool Group::getSort() const{
	return this->do_sort;
}

bool Group::getCorrectRemove() const{
	return this->correct_remove;
}

Entity& Group::getEntity(entity_vec_size value){
	return *this->entities.at(value);
}

Entity& Group::operator[](entity_vec_size value){
	return *this->entities.at(value);
}

const Entity& Group::getEntity(entity_vec_size value) const{
	return *this->entities.at(value);
}

const Entity& Group::operator[](entity_vec_size value) const{
	return *this->entities.at(value);
}

void Group::addToGroup(const std::string& group, Entity& entity){
	this->entity_groups[group].push_back(&entity);
	entity._groups_v.push_back(group);
}

void Group::removeFromGroup(const std::string& group, Entity& entity){
	std::vector<Entity*>::iterator entity_iter = this->entity_groups[group].begin();
	while (entity_iter != this->entity_groups[group].end()){
		if (*entity_iter == &entity){
			entity_iter = this->entity_groups[group].erase(entity_iter);
		} else {
			++entity_iter;
		}
	}
	
	std::vector<std::string>::iterator group_iter = entity._groups_v.begin();
	while (group_iter != entity._groups_v.end()){
		if (*group_iter == group){
			group_iter = entity._groups_v.erase(group_iter);
		} else {
			++group_iter;
		}
	}
}

std::vector<Entity*>::iterator Group::getGroupBegin(const std::string& group){
	return this->entity_groups[group].begin();
}

std::vector<Entity*>::iterator Group::getGroupEnd(const std::string& group){
	return this->entity_groups[group].end();
}

entity_vec::size_type Group::getGroupSize(const std::string& group){
	return this->entity_groups[group].size();
}

bool Group::getCollideEntity(JE::Entity& entity, int move_x, int move_y, int* get_x, int* get_y){
	JE::MASK::Mask* mask = entity.getMask();
	if (mask == nullptr) return false;
	return this->getCollideMask(*mask, move_x, move_y, get_x, get_y);
}

bool Group::getCollideMask(JE::MASK::Mask& mask, int move_x, int move_y, int* get_x, int* get_y){
	std::vector<JE::MASK::Mask*> mask_vec;
	
	for (auto& entity : this->entities){
		JE::MASK::Mask* other_mask = entity->getMask();
		if (other_mask == nullptr || other_mask == &mask) continue;
		
		mask_vec.push_back(other_mask);
	}
	
	return mask.callCollideGroup(mask_vec, move_x, move_y, get_x, get_y);
}

bool Group::getCollideEntityGroup(JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y, const std::string& group){
	JE::MASK::Mask* mask = entity.getMask();
	if (mask == nullptr) return false;
	return this->getCollideMaskGroup(*mask, move_x, move_y, get_x, get_y, group);
}

bool Group::getCollideMaskGroup(JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y, const std::string& group){
	std::vector<JE::MASK::Mask*> mask_vec;
	
	for (JE::Entity* entity : this->entity_groups[group]){
		JE::MASK::Mask* other_mask = entity->getMask();
		if (other_mask == nullptr || other_mask == &mask) continue;
		
		mask_vec.push_back(other_mask);
	}
	
	return mask.callCollideGroup(mask_vec, move_x, move_y, get_x, get_y);
}

bool Group::getCollideEntityGroups(JE::Entity& entity,  int move_x, int move_y, int* get_x, int* get_y, const std::vector<std::string>& groups){
	JE::MASK::Mask* mask = entity.getMask();
	if (mask == nullptr) return false;
	return this->getCollideMaskGroups(*mask, move_x, move_y, get_x, get_y, groups);
}

bool Group::getCollideMaskGroups(JE::MASK::Mask& mask,int move_x, int move_y, int* get_x, int* get_y, const std::vector<std::string>& groups){
	std::vector<JE::MASK::Mask*> mask_vec;
	
	for (auto& entity : this->entities){
		JE::MASK::Mask* other_mask = entity->getMask();
		if (other_mask == nullptr || other_mask == &mask) continue;
		
		bool do_add = false;
		for (const std::string& entity_group_name : entity->_groups_v){
			for (const std::string& group_name : groups){
				if (entity_group_name == group_name){
					do_add = true;
				}
			}
		}
		
		if (!do_add) continue;
		
		mask_vec.push_back(other_mask);
	}
	
	return mask.callCollideGroup(mask_vec, move_x, move_y, get_x, get_y);
}

void Group::callComponents(const std::string& name){
	for (auto& entity : this->entities){
		entity->callComponent(name);
	}
}

void Group::callComponentsGroup(const std::string& group, const std::string& component){
	for (auto entity : this->entity_groups[group]){
		entity->callComponent(component);
	}
}

}