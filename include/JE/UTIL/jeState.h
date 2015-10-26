#pragma once
#include <algorithm>
#include <map>
#include <vector>
//This is a very small, and very simple state machine.
//Situational state overrides aren't currently possible, but it would be a good feature at some point in the future.
namespace JE{
namespace STATE{

template <typename Value>
class StateType{
public:
	int priority;
	Value value;

	StateType(){}
};

template <typename Key, typename Value>
class StateMachine{
private:
	std::map<Key, StateType<Value>> state_types;
	std::vector<Key> state_vector;
	bool needs_sort;
	void sort(){
		this->needs_sort = false;
		//sort by state priority.
		std::sort(this->state_vector.begin(), this->state_vector.end(),
		[&](const Key& a_string, const Key& b_string){
			//const StateType<Key>& a = state_types[a_string];
			//const StateType<Key>& b = state_types[b_string];
			return this->state_types[a_string].priority < this->state_types[b_string].priority;
		});
	}
public:
	StateMachine(){
		this->needs_sort = false;
	}
	virtual ~StateMachine(){}
	bool push(Key name){
		if (this->state_types.count(name) == 0){
			return false;
		}
		if (!this->contains(name)){
			this->state_vector.push_back(name);
			this->needs_sort = true;
			return true;
		}
		return false;
	}
	bool popTop(){
		if (this->state_vector.size() > 0){
			this->state_vector.pop_back();
			return true;
		}
		return false;
	}
	bool pop(const Key& name){
		bool ret = false;
		unsigned int i = 0;
		while (i < this->state_vector.size()){
			if (this->state_vector[i] == name){
				ret = true;
				this->state_vector.erase(this->state_vector.begin() + i);
			} else ++i;
		}
		return ret;
	}
	bool addType(const Key& name, int priority, Value value){
		if (this->state_types.count(name) >= 1){
			return false;
		}
		//this->state_types.insert(name, StateType<Value>());
		this->state_types[name] = StateType<Value>();
		this->state_types[name].priority = priority;
		this->state_types[name].value = value;
		return true;
	}
	bool removeType(const Key& name){
		if (this->state_types.count(name) >= 1){
			this->state_types.erase(name);
			this->pop(name);
		}
		return false;
	}
	Value getTop(){
		if (this->state_vector.size() == 0){
			throw "StateMachine Error: No states enabled in state machine.";
			//only way I can find to exit a function, and I think it should work with exception handlers.
		}
		if (this->needs_sort) this->sort();
		//std::cout << "Size of state vector: " << this->state_vector.size() << std::endl;
		Key k = this->state_vector.back();
		return this->state_types[k].value;
	}
	bool contains(Key key){
		bool does_contain = false;
		for (Key other : this->state_vector){
			if (other == key){
				does_contain = true;
			}
		}
		return does_contain;
	}
	int count(){
		return this->state_vector.size();
		//hopefully people will use this before trying to getTop();
	}
	bool empty(){
		return (this->count() == 0);
		//Although this function is probably better for the above-mentioned situation.
	}
};

}
}
