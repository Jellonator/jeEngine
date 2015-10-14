#pragma once
//due to the use of templates, all of jeManager's code is in a header.
//Manager is a class that manages file-loaded resources
//It uses smart pointers to make sure that data isn't deleted until it is no longer needed by anything
//The best way to utilize a manager is to register everything at initialization of code, then load files whenever
//Also note that Value must have a constructor as such: Value(Reference ref)
//look into jeState.cpp for a 330 byte version
#include <map>
#include <memory>

namespace JE{

template <typename Key, typename Value, typename Reference = std::string>
class Manager{
public:
	Manager();
	virtual ~Manager();
	void newResource(Key key, Reference ref);
	void removeResource(Key key);
	std::shared_ptr<Value> getResource(Key key);
	bool hasResource(Key key);
	bool isResourceLoaded(Key key);
	Reference getReference(Key key);
private:
	std::map<Key, Reference> file_names;
	std::map<Key, std::weak_ptr<Value>> pointers;
};
template <typename Key, typename Value, typename Reference>
Manager<Key,Value,Reference>::Manager(){}
template <typename Key, typename Value, typename Reference>
Manager<Key,Value,Reference>::~Manager(){}
template <typename Key, typename Value, typename Reference>
void Manager<Key,Value,Reference>::newResource(Key key, Reference ref){
	this->file_names[key] = ref;
	//std::cout << "Adding resource '" << key << ",'" << " which links to " << ref << std::endl;
}
template <typename Key, typename Value, typename Reference>
void Manager<Key,Value,Reference>::removeResource(Key key){
	this->file_names.erase(key);
	this->pointers.erase(key);
}
template <typename Key, typename Value, typename Reference>
Reference Manager<Key,Value,Reference>::getReference(Key key){
	return this->file_names[key];
}
template <typename Key, typename Value, typename Reference>
bool Manager<Key,Value,Reference>::hasResource(Key key){
	return (this->file_names.count(key) >= 1);
}
template <typename Key, typename Value, typename Reference>
bool Manager<Key,Value,Reference>::isResourceLoaded(Key key){
	return (!this->pointers[key].expired());
}
template <typename Key, typename Value, typename Reference>
std::shared_ptr<Value> Manager<Key,Value,Reference>::getResource(Key key){
	//return a null pointer if there is no such resource
	if (!this->hasResource(key)) return nullptr;
	//make sure to initialize the weak pointer(pretty sure it does this automatically, but you can never be too careful).
	if (this->pointers.count(key) == 0){
		this->pointers[key] = std::weak_ptr<Value>();
	}
	if (this->pointers[key].expired()){
		std::shared_ptr<Value> ptr = std::make_shared<Value>(this->file_names[key]);
		this->pointers[key] = ptr;
		return ptr;
	}else{
		auto ptr = this->pointers[key].lock();
		return ptr;
	}
}
}
