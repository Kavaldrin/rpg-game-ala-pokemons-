#pragma once
#include "DPObject.h"
#include "DPField.h"
#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <utility>

class DPMap :
	public DPObject
{
public:

	friend class DPCamera;

	DPMap();
	virtual ~DPMap();
	static std::unique_ptr<DPMap> loadMap(const char* path);
	static void loadMapTextures(std::unordered_map<std::string, const SDL_Texture*>&& textures) { m_loadedMapTextures = std::move(textures); }
	void draw(SDL_Renderer* renderer);
	void updatePlayerPos(const std::pair<uint16_t, uint16_t>& oldPos, const std::pair<uint16_t, uint16_t>& newPos);

	void debugInfo() {
		std::cout << m_fields.size() << std::endl;
		std::cout << m_fields[0].size() << std::endl;
	}

	std::pair<std::uint16_t, std::uint16_t> findPlayer();
	bool inMap(std::uint16_t x, std::uint16_t y);

	
private:
	std::vector<std::vector<DPField>> m_fields;
	static std::unordered_map<std::string, const SDL_Texture*> m_loadedMapTextures;


};

