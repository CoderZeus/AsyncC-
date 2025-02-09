#include <core/include/SharedLibraryManager.h>

namespace Core
{
	SharedLibraryManager::SharedLibraryManager():ISubsystem(SHAREDLIBRARY_MANAGER)
	{
	}
	SharedLibraryManager::~SharedLibraryManager()
	{
	}
	void SharedLibraryManager::init()
	{
		LOG_VERBOSE((LOGGER),("SharedLibraryManager::init>>>"));
		LOG_VERBOSE((LOGGER),("SharedLibraryManager::init<<<"))
	}

	void SharedLibraryManager::shutdown()
	{
		LOG_VERBOSE((LOGGER),("SharedLibraryManager::shutdown>>>"));
		this->mLoaders.clear();
		LOG_VERBOSE((LOGGER),("SharedLibraryManager::shutdown<<<"))
	}

	SharedLibraryLoader* SharedLibraryManager::loadLibrary(string libraryname)
	{
		LOG_VERBOSE((LOGGER),("SharedLibraryManager::loadLibrary>>>"));
		shared_ptr<SharedLibraryLoader> loader;
		if(unlikely(!this->mLoaders.find(libraryname,loader)))
		{
			loader = make_shared<SharedLibraryLoader>(libraryname);
			if(unlikely(loader->loadLibrary() == false))
			{
				return nullptr;
			}
			this->mLoaders.insert(libraryname,loader);
		}
		LOG_VERBOSE((LOGGER),("SharedLibraryManager::loadLibrary<<<"));
		return loader.get();
	}
}
