#pragma once
#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include <memory>
#include "DPMap.h"
#include "DPPlayer.h"
#include "DPCamera.h"
#include <functional>

class DPMap;





class DPGame
{
public:
	DPGame() = default;
	~DPGame() = default;
	static std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer;
	static std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window;


	bool isRunning() { return m_isRunning; }
	void setup(const char *title, const std::uint16_t x, const std::uint16_t y);

	void handleEvents();
	void update();
	void draw();


private:
	bool m_isRunning = true;

	std::unique_ptr<DPPlayer> m_player;
	std::vector<std::unique_ptr<DPMap>> m_maps;
	std::unique_ptr<DPCamera> camera;

	void playerPositionUpdate();

};

