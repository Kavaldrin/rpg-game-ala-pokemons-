#include "DPField.h"





DPField::DPField(const SDL_Texture* fieldText, std::uint16_t x, std::uint16_t y)
	:m_fieldTexture(fieldText)
{
	
	m_coords = std::pair<std::uint16_t, std::uint16_t>(x, y);

	m_destRect.h = 60;
	m_destRect.w = 80;

}

void DPField::draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, const_cast<SDL_Texture*>(m_fieldTexture), nullptr, &m_destRect);
}