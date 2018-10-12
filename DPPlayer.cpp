#include "DPPlayer.h"
#include "DPTextureLoader.h"

std::unordered_map<std::string, const SDL_Texture*> DPPlayer::m_loadedPlayerTextures;

DPPlayer::DPPlayer()
{
}


DPPlayer::~DPPlayer()
{
}

void DPPlayer::setPosition(const std::pair<uint16_t, uint16_t> &pair)
{
	m_prevPostion = pair;
	m_position = pair;
	m_destRect.h = 60 ; m_destRect.w = 80;
	m_destRect.x = 80 * pair.first; m_destRect.y = 60 * pair.second;

}
void DPPlayer::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, const_cast<SDL_Texture*>(m_actualTexture), nullptr, &m_destRect);
}
void DPPlayer::makeMove(const std::pair<uint16_t, uint16_t> &pair)
{
	m_prevPostion = m_position;
	m_position = pair;
	m_destRect.x = 80 * pair.first; m_destRect.y = 60 * pair.second;
}