#pragma once

#include <map>
#include <string>
#include <memory>
#include "util/Logger.h"
#include "util/Uncopyable.h"

/**
* Template resource management class.
*
*/
template <class Type>
class ResourceManager : private Uncopyable {

	private:
		typedef std::shared_ptr<Type> typePtr;
		typedef std::map<std::string, typePtr> typeMap;

	public:
		/**
		* The destructor.
		* @note Warns about resources being deleted with references still pointing to them.
		*/
		virtual ~ResourceManager();

		/**
		* Retrieves the resource from the resources.
		* @return The pointer to the wanted resource. Creates it, if not already in resources.
		* @param path_ : Path to the desired resource.
		*/
		Type* get(const std::string& path_);

	protected:
		/**
		* Constructs the desired resource.
		* @param path_ : Path to the desired resource.
		*/
		virtual typePtr load(const std::string& path_) = 0;

		/**
		* Registers the resource on the resources map.
		* @param path_ : Path to the resource. Will be the key value.
		* @param resource_ : The shared pointer for the resource.
		*/
		void registerResource(const std::string& path_, typePtr resource_);

		/**
		* Unregisters the resource on the resources map.
		* @param path_ : The key (path to resource) on the map.
		*/
		void unregisterResource(const std::string& path_);

		typeMap resources; /**< The map that contains all the Type resources. */

};

template <class Type>
ResourceManager<Type>::~ResourceManager() {
	typename typeMap::const_iterator it;

	for(it = resources.begin(); it != resources.end(); it++) {
		if(it->second.use_count() != 1) {
			log_warn() << "Resource deleted with use count different than 1 (" << it->first
				<< ").";
		}
	}
}

template <class Type>
Type* ResourceManager<Type>::get(const std::string& path_) {
	typename typeMap::const_iterator it;
	it = resources.find(path_);

	Type* tPtr = nullptr;

	if (it != resources.end()) {
		tPtr = it->second.get();
	}
	else {
		tPtr = load(path_).get();
	}

	return tPtr;
}

template <class Type>
void ResourceManager<Type>::registerResource(const std::string& path_, typePtr resource_) {
	resources.insert(std::make_pair(path_, resource_));
}

template <class Type>
void ResourceManager<Type>::unregisterResource(const std::string& path_) {
	typename typeMap::const_iterator it;
	it = resources.find(path_);

	if (it != resources.end()) {
		resources.erase(it);
	}
}

