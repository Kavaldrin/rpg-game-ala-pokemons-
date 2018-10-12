#include "DPTextureLoader.h"
#include <iostream>



const SDL_Texture * DPTextureLoader::loadTexture(const char * path, SDL_Renderer* renderer)
{
	SDL_Surface *surface = IMG_Load(path);

	////////////////////////////debug
	if (surface == nullptr) {
		std::cout << IMG_GetError() << std::endl;
		system("pause");
	}
	/////////////////////////

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

std::unordered_map<std::string, const SDL_Texture*> DPTextureLoader::loadTextures(const std::vector<std::string>& paths, SDL_Renderer * renderer)
{
	std::unordered_map<std::string, const SDL_Texture*> temp;
	for (const auto &str : paths) {

		///////////////////////////debug
		std::cout << str.c_str() << " " << DPTextureLoader::prettyName(str).c_str() << std::endl;
		///////////////////////////////

		temp[DPTextureLoader::prettyName(str)] = DPTextureLoader::loadTexture(str.c_str(), renderer);
	}
	return std::move(temp);
}

const SDL_Texture* DPTextureLoader::getTexture(std::string name,const std::unordered_map<std::string, const SDL_Texture*>& loadedTextures)
{
	auto iterator = loadedTextures.find(name);
	if (iterator == loadedTextures.end()) { 
		return nullptr; 
	}

	return iterator->second;
}

std::string DPTextureLoader::prettyName(std::string fullName)
{
	auto i = 0;
	int begIndex = 0; int endIndex = 0;
	const char* data = fullName.data();

	while (*data) {
		if (*data == '/') begIndex = data - fullName.data();
		if (*data == '.') endIndex = data - fullName.data();
		++data;
	}

	return std::string(fullName.data() + begIndex + 1, endIndex - begIndex - 1);
}

