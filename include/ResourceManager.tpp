#include "Logger.h"

template <class Type>
ResourceManager<Type>::~ResourceManager(){
	typename TypeMap::const_iterator it;
	
	for(it = resources.begin(); it != resources.end(); it++){
		if(it->second.use_count() != 1){
			Log(WARN) << "Resource deleted with use count different than 1 (" << it->first << ").";
		}
	}
}

template <class Type>
Type* ResourceManager<Type>::get(const std::string& path_){
	typename TypeMap::const_iterator it;
	it = resources.find(path_);

	Type* tPtr = nullptr;

	if (it != resources.end()){
		tPtr = it->second.get();
	}
	else{
		tPtr = load(path_).get();
	}
	
	return tPtr;
}

template <class Type>
void ResourceManager<Type>::registerResource(const std::string& path_, TypePtr resource_){
	resources.insert(std::make_pair(path_, resource_));
}

template <class Type>
void ResourceManager<Type>::unregisterResource(const std::string& path_){
	typename TypeMap::const_iterator it;
	it = resources.find(path_);

	if (it != resources.end()){
		resources.erase(it);
	}
}
