#pragma once

#include <SDL_image.h>
#include <vector>
#include <unordered_map>

class DPTextureLoader
{
public:

	DPTextureLoader() = delete;
	~DPTextureLoader() = delete;

	static const SDL_Texture* loadTexture(const char *path, SDL_Renderer* renderer);
	static std::unordered_map<std::string, const SDL_Texture*> loadTextures(const std::vector<std::string>& paths,SDL_Renderer* renderer);
	static const SDL_Texture* getTexture(std::string name,const std::unordered_map<std::string, const SDL_Texture*>& loadedTextures);

private:

	static std::string prettyName(std::string fullName);

};

