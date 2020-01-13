#include "assetManager.hpp"

void AssetManager::loadObjects(const std::string & assetFileName){
	std::ifstream input(assetFileName);
	if(!input){
		throw fileNotFound(assetFileName);
	}
}