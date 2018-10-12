#pragma once
#include "DPMob.h"
#include "DPSkills.h"
#include "DPInventory.h"
#include <memory>
#include <SDL.h>

#include <unordered_map>
#include <vector>
class DPPlayer :
	public DPMob
{
public:

	friend class DPCamera;

	DPPlayer();
	virtual ~DPPlayer();

	//
	void CreateNewPlayer();
	void setPosition(const std::pair<uint16_t, uint16_t> &pair);
	void makeMove(const std::pair<uint16_t, uint16_t> &pair);
	const std::pair<uint16_t, uint16_t> getPosition() { return m_position; }
	void setActualTexture(std::string name) { m_actualTexture = m_loadedPlayerTextures[name]; }
	static void loadPlayerTextures(std::unordered_map<std::string, const SDL_Texture*>&& textures) { m_loadedPlayerTextures = std::move(textures); }

	void draw(SDL_Renderer* renderer);
	

private:


	std::vector<std::shared_ptr<DPSkills>> m_skills;
	std::unique_ptr<DPInventory> m_inventory;
	std::pair<std::uint16_t, std::uint16_t> m_position;
	std::pair<std::uint16_t, std::uint16_t> m_prevPostion;
	const SDL_Texture* m_actualTexture;
	SDL_Rect m_destRect;

	static std::unordered_map<std::string, const SDL_Texture*> m_loadedPlayerTextures;

};

