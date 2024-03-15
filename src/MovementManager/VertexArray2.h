#pragma once
#include <SFML/Graphics.hpp>

class VertexArray2 : public sf::VertexArray, public sf::Transformable {
private:
	sf::Vector2f	m_centroid;
	bool			m_needCentroidUpdate;

private:

	// Private update functions
	void updateCentroid();

public:
	// Constructors / Destructors
	VertexArray2();
	VertexArray2(sf::PrimitiveType type, size_t vertexCount = 0);
	VertexArray2(const VertexArray2& other);
	~VertexArray2();

	// Overriden functions
	void clear();
	void resize(std::size_t vertexCount);
	void append(const sf::Vertex& vertex);

	// Overriden operators
	sf::Vertex& operator [](std::size_t index);
	const sf::Vertex& operator [](std::size_t index) const;

	operator sf::VertexArray& ();
	operator const sf::VertexArray& () const;

	// Accessors
	const sf::Vector2f& getCentroid();
};