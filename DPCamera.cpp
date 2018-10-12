#include "DPCamera.h"
#include "DPMap.h"
#include "DPPlayer.h"

void DPCamera::update(std::unique_ptr<DPPlayer>& player, std::unique_ptr<DPMap>& map)
{
	m_playerPos = player->getPosition();

	std::cout << m_playerPos.first << " " << m_playerPos.second << std::endl;

	if (m_playerPos.second < 5) player->m_destRect.y = m_playerPos.second * 60;
	else if (m_playerPos.second > map->m_fields.size() - 5) player->m_destRect.y = 600 - ((map->m_fields.size() - m_playerPos.second) * 60);
	else player->m_destRect.y = 300;
	
	if (m_playerPos.first < 5) player->m_destRect.x = m_playerPos.first * 80;
	else if (m_playerPos.first > map->m_fields[m_playerPos.second].size() - 5) player->m_destRect.x = 800 - ((map->m_fields[m_playerPos.second].size() - m_playerPos.first) * 80);
	else player->m_destRect.x = 400;
	
	///////////////////////////////////////////////
	
	m_displayRactangle.y_start = m_playerPos.second - 5;
	if (m_displayRactangle.y_start < 0) m_displayRactangle.y_start = 0;
	m_displayRactangle.y_stop = m_playerPos.second + 5;
	if (m_displayRactangle.y_stop > map->m_fields.size()) m_displayRactangle.y_stop = map->m_fields.size();


	m_displayRactangle.x_start = m_playerPos.first - 5;
	if (m_displayRactangle.x_start < 0) m_displayRactangle.x_start = 0;
	m_displayRactangle.x_stop = m_playerPos.first + 5;
	if (m_displayRactangle.x_stop > map->m_fields[0].size()) m_displayRactangle.x_stop = map->m_fields[0].size();



	if (m_displayRactangle.x_stop - m_displayRactangle.x_start < 10) {
		auto toAdd = 10 - (m_displayRactangle.x_stop - m_displayRactangle.x_start);

		while (toAdd) {
			if (m_displayRactangle.x_start > 0) {
				--m_displayRactangle.x_start;
				--toAdd;
			}
			else if (m_displayRactangle.x_stop < map->m_fields[0].size()) {
				++m_displayRactangle.x_stop;
				--toAdd;
			}
		}
	}


	if (m_displayRactangle.y_stop - m_displayRactangle.y_start < 10) {
		auto toAdd = 10 - (m_displayRactangle.y_stop - m_displayRactangle.y_start);

		while (toAdd) {
			if (m_displayRactangle.y_start > 0) {
				--m_displayRactangle.y_start;
				--toAdd;
			}
			else if (m_displayRactangle.y_stop < map->m_fields.size()) {
				++m_displayRactangle.y_stop;
				--toAdd;
			}
		}
	}





	for (int y = m_displayRactangle.y_start; y < m_displayRactangle.y_stop; ++y) {
		for (int x = m_displayRactangle.x_start; x < m_displayRactangle.x_stop; ++x) {
			map->m_fields[y][x].m_destRect.x = 80 * (x - m_displayRactangle.x_start);
			map->m_fields[y][x].m_destRect.y = 60 * (y - m_displayRactangle.y_start);
		}
	}



}

void DPCamera::draw(std::unique_ptr<DPMap>& map, SDL_Renderer* ren)
{
	for (int y = m_displayRactangle.y_start; y < m_displayRactangle.y_stop; ++y) {
		for (int x = m_displayRactangle.x_start; x < m_displayRactangle.x_stop; ++x) {
			map->m_fields[y][x].draw(ren);
		}
	}


}
void DPCamera::draw(std::unique_ptr<DPPlayer>& player, SDL_Renderer* ren)
{
	player->draw(ren);
}