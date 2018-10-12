#pragma once
#include "DPObject.h"
#include <memory>
#include <SDL.h>

class DPPlayer; class DPMap;

class DPCamera :
	public DPObject
{
public:
	DPCamera() = default;
	~DPCamera() {}

	void update(std::unique_ptr<DPPlayer>& player,std::unique_ptr<DPMap>& map);
	
	void draw(std::unique_ptr<DPMap>& map, SDL_Renderer* ren);
	void draw(std::unique_ptr<DPPlayer>& player, SDL_Renderer* ren);

private:
	struct DisplayRactangle {
		std::int16_t x_start;
		std::int16_t x_stop;
		std::int16_t y_start;
		std::int16_t y_stop;
	};

	DisplayRactangle m_displayRactangle;
	std::pair<std::uint16_t, std::uint16_t> m_playerPos = std::make_pair<std::uint16_t, std::uint16_t>(0, 0);

};

