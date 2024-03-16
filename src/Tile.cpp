#include "Tile.h"

inline void Tile::center_origin()
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().left + m_sprite.getGlobalBounds().width  / 2.f,
                       m_sprite.getGlobalBounds().top  + m_sprite.getGlobalBounds().height / 2.f);
}

Tile::Tile(int type, sf::Texture* texture, float* scale)
{
	m_type = type;
	m_scale = scale;
	m_sprite.setTexture(*texture);
	center_origin();
	m_sprite.setScale(*m_scale, *m_scale);
}

bool Tile::updateOpacity(const float& dt)
{
	if (m_isSpawning){
		m_spawningTime += dt;
		if (m_spawningTime >= m_spawningTimeMax){
			m_isSpawning = false;
			m_spawningTime = m_spawningTimeMax;
			m_sprite.setColor(sf::Color(255, 255, 255, 255));
			return false;
		}
		else
			m_sprite.setColor(sf::Color(255, 255, 255, 255 * m_spawningTime / m_spawningTimeMax));
	}
	return true;
}

void Tile::gameOver()
{
	m_sprite.setColor(sf::Color(250, 248, 239, 160));
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(m_sprite);
}
