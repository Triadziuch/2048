#pragma once
#include "VertexArray2.h"

// = = = = = = = = = = Private update functions = = = = = = = = = = 
void VertexArray2::updateCentroid()
{
	m_needCentroidUpdate = false;

	sf::Vector2f centroid_temp{};
	const size_t vertex_count = sf::VertexArray::getVertexCount();

	if (vertex_count == 0) {
		m_centroid = centroid_temp;
		return;
	}

	for (size_t i = 0; i < vertex_count; ++i)
		centroid_temp += sf::VertexArray::operator[](i).position;
	m_centroid = centroid_temp / static_cast<float>(vertex_count);
}

// = = = = = = = = = = Constructors / Destructors = = = = = = = = = =

VertexArray2::VertexArray2() : sf::VertexArray{}, m_centroid{}, m_needCentroidUpdate{false} {}

VertexArray2::VertexArray2(sf::PrimitiveType type, size_t vertexCount) : sf::VertexArray{ type, vertexCount },
							   m_centroid{}, m_needCentroidUpdate{ false } {}

VertexArray2::VertexArray2(const VertexArray2& other) : sf::VertexArray{ other }, m_centroid{ other.m_centroid },
							   m_needCentroidUpdate{ other.m_needCentroidUpdate } {}

VertexArray2::~VertexArray2() { 
};

// = = = = = = = = = = Overriden functions = = = = = = = = = =
void VertexArray2::clear()
{
	m_needCentroidUpdate = true;
	sf::VertexArray::clear();
}

void VertexArray2::resize(std::size_t vertexCount)
{
	m_needCentroidUpdate = true;
	sf::VertexArray::resize(vertexCount);
}

void VertexArray2::append(const sf::Vertex& vertex)
{
	m_needCentroidUpdate = true;
	sf::VertexArray::append(vertex);
}

// = = = = = = = = = = Overriden operators = = = = = = = = = =
sf::Vertex& VertexArray2::operator [](std::size_t index)
{
	m_needCentroidUpdate = true;
	return sf::VertexArray::operator[](index);
}

const sf::Vertex& VertexArray2::operator [](std::size_t index) const
{
	return sf::VertexArray::operator[](index);
}

VertexArray2::operator sf::VertexArray& () {
	m_needCentroidUpdate = true;
	return *this;
}

VertexArray2::operator const sf::VertexArray& () const {
	return *this;
}

const sf::Vector2f& VertexArray2::getCentroid()
{
	if (m_needCentroidUpdate)
		updateCentroid();
	return m_centroid;
}
