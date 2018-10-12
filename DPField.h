#pragma once
#include "DPObject.h"
#include <SDL.h>
#include <utility>
#include <cstdint>
#include <memory>
#include "DPMonster.h"



class DPField :
	public DPObject
{
public:
	friend class DPMap;
	friend class DPCamera;
	DPField() = default;
	DPField(const SDL_Texture* fieldText, std::uint16_t x = 0, std::uint16_t y = 0);
	virtual ~DPField() = default;

	DPField(const DPField&) = default;
	DPField& operator=(const DPField&) = default;
	DPField(DPField&&) = default;
	DPField& operator=(DPField&&) = default;

	void setPlayer() { if (!m_isPlayer)m_isPlayer = true; }
	void draw(SDL_Renderer* renderer);

private:
	const SDL_Texture*  m_fieldTexture;
	bool m_isMonster = false;
	bool m_isPlayer = false;
	std::pair<std::uint16_t, std::uint16_t> m_coords = std::make_pair<std::uint16_t, std::uint16_t>(0, 0);
	SDL_Rect m_srcRect; SDL_Rect m_destRect;

	std::unique_ptr<DPMonster> m_monster = nullptr;

};

