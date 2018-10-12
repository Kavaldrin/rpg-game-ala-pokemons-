#include "DPMap.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "DPTextureLoader.h"

DPMap::DPMap()
{
}


DPMap::~DPMap()
{
}

std::unordered_map<std::string, const SDL_Texture*> DPMap::m_loadedMapTextures;

std::unique_ptr<DPMap> DPMap::loadMap(const char* path)
{
	std::fstream mapfile(path);
	if (!mapfile.good()) return nullptr;

	std::string line;
	std::vector<DPField> lineField;
	std::unique_ptr<DPMap> newMap = std::make_unique<DPMap>();
	auto y_counter = 0;

	while (std::getline(mapfile, line)) {

		std::stringstream str(line);
		char temp;
		auto x_counter = 0;
		while (str) {
			str >> temp;
			if (!str) break; //wtf?

			switch (temp) {
			case 'g':
				lineField.emplace_back(
					std::move(DPField(DPTextureLoader::getTexture("grass",m_loadedMapTextures), x_counter, y_counter)));
				++x_counter;
				break;
			case 'd':
				lineField.emplace_back(
					std::move(DPField(DPTextureLoader::getTexture("dirt", m_loadedMapTextures), x_counter, y_counter)));
				++x_counter;
				break;
			case 'p':
				lineField.back().setPlayer();
				break;
			}
		}
		std::cout << std::endl;
		newMap->m_fields.emplace_back(std::move(lineField));
		lineField.clear();
		++y_counter;
		
	}
	mapfile.close();
	return newMap;

}


void DPMap::draw(SDL_Renderer* renderer)
{
	/*
	for (const auto &fieldLine : m_fields) {
		for (const auto &field : fieldLine) {
			field.draw(renderer);
		}
	}
	*/
}

std::pair<std::uint16_t, std::uint16_t> DPMap::findPlayer()
{
	for (auto i = m_fields.cbegin(); i != m_fields.cend(); ++i) {
		for (auto j = i->cbegin(); j != i->cend(); ++j) {
			if (j->m_isPlayer)
				return std::make_pair<std::uint16_t, std::uint16_t>(j - i->cbegin(), i - m_fields.cbegin());
		}
	}

	throw std::exception("Player not found on the map");
	return std::make_pair<std::uint16_t, std::uint16_t>(0,0);

}

bool DPMap::inMap(std::uint16_t x, std::uint16_t y)
{



	if (m_fields.size() > y && y >= 0) {
		if (m_fields[y].size() > x && x >= 0) {
			return true;
		}
	}
	return false;
}

void DPMap::updatePlayerPos(const std::pair<uint16_t, uint16_t>& oldPos, const std::pair<uint16_t, uint16_t>& newPos)
{
	m_fields[oldPos.second][oldPos.first].m_isPlayer = false;
	m_fields[newPos.second][newPos.first].m_isPlayer = true;
}