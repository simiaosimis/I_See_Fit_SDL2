#pragma once

#include "Uncopyable.h"
#include <map>
#include <string>
#include <memory>

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

#include "ResourceManager.tpp"
