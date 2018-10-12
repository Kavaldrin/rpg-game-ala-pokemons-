#include "DPGame.h"
#include <exception>
#include"DPTextureLoader.h"
#include <utility>

std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> DPGame::renderer;
std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> DPGame::window;



void DPGame::setup(const char *title, const std::uint16_t w, const std::uint16_t h)
{
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		throw std::exception("SDL Initialization failed");
	}

	SDL_Window *newWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
	if (newWindow == nullptr) { throw std::exception("SDL Creating Window failed"); }
	window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(newWindow, [](SDL_Window* win) {SDL_DestroyWindow(win); });

	SDL_Renderer *newRenderer = SDL_CreateRenderer(window.get(), -1, 0);
	if (newRenderer == nullptr) { throw std::exception("SDL Creating Renderer failed"); }
	renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>(newRenderer, [](SDL_Renderer* ren) {SDL_DestroyRenderer(ren); });


	/////////////////////
	std::vector<std::string> texturePaths;
	texturePaths.push_back("assets/grass.png");
	texturePaths.push_back("assets/dirt.png");

	////////////////////


	///////////map creation

	DPMap::loadMapTextures( DPTextureLoader::loadTextures(texturePaths,renderer.get()));
	m_maps.emplace_back(DPMap::loadMap("maps/map1.map"));
	m_maps.back()->debugInfo();
	texturePaths.clear();
	////////////////

	texturePaths.push_back("assets/player1right.png");
	texturePaths.push_back("assets/player1left.png");
	//////////////player creation
	m_player = std::make_unique<DPPlayer>();
	m_player->setPosition(m_maps.back()->findPlayer());
	DPPlayer::loadPlayerTextures(DPTextureLoader::loadTextures(texturePaths, renderer.get()));
	m_player->setActualTexture("player1right");


	///////////////camera creation
	camera = std::make_unique<DPCamera>();

}




void DPGame::handleEvents()
{


	std::unique_ptr<SDL_Event> event = std::make_unique<SDL_Event>();
	while (SDL_PollEvent(event.get())) {
		switch (event->type) {

		///////////////////////////////
		case SDL_QUIT:
			m_isRunning = false;
			break;
		//////////////////////////////
		}


	}

	playerPositionUpdate();


	/////////////////////////
	

}
void DPGame::update()
{
	camera->update(m_player,m_maps.back());

}
void DPGame::draw()
{

	SDL_RenderClear(renderer.get());

	camera->draw(m_maps.back(),renderer.get());
	camera->draw(m_player,renderer.get());

	SDL_RenderPresent(renderer.get());

}

void DPGame::playerPositionUpdate()
{
	//keyboards events
	static auto movingCooldown = 0;
	if (movingCooldown > 10) movingCooldown = 0;

	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	const std::pair<uint16_t, uint16_t> playerPos = m_player->getPosition();
	std::pair<uint16_t, uint16_t> playerPosUpdated = playerPos;

	if (!movingCooldown) {

		if (keyboardState[SDL_SCANCODE_LEFT]) {
			if (m_maps.back()->inMap(playerPos.first - 1, playerPos.second)) {
				m_player->makeMove(std::pair<std::uint16_t, std::uint16_t>(playerPos.first - 1, playerPos.second));
				--playerPosUpdated.first;
			}
		}
		if (keyboardState[SDL_SCANCODE_RIGHT]) {
			if (m_maps.back()->inMap(playerPos.first + 1, playerPos.second)) {
				m_player->makeMove(std::pair<std::uint16_t, std::uint16_t>(playerPos.first + 1, playerPos.second));
				++playerPosUpdated.first;
			}
		}
		if (keyboardState[SDL_SCANCODE_UP]) {
			if (m_maps.back()->inMap(playerPos.first, playerPos.second - 1)) {
				m_player->makeMove(std::pair<std::uint16_t, std::uint16_t>(playerPos.first, playerPos.second - 1));
				--playerPosUpdated.second;
			}
		}
		if (keyboardState[SDL_SCANCODE_DOWN]) {
			if (m_maps.back()->inMap(playerPos.first, playerPos.second + 1)) {
				m_player->makeMove(std::pair<std::uint16_t, std::uint16_t>(playerPos.first, playerPos.second + 1));
				++playerPosUpdated.second;
			}
		}
	}

	m_maps.back()->updatePlayerPos(playerPos, playerPosUpdated);

	if (playerPos.first - playerPosUpdated.first > 0) {
		m_player->setActualTexture("player1left");
	}
	else if (playerPos.first - playerPosUpdated.first < 0) {
		m_player->setActualTexture("player1right");
	}


	++movingCooldown;

	/////////////////////////////
}
