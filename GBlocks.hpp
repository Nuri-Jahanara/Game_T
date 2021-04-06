#pragma once
#ifndef UNTITLED_GBLOCKS_HPP
#define UNTITLED_GBLOCKS_HPP

#include<SFML/Graphics/Sprite.hpp>
#include<SFML/Graphics/Drawable.hpp>
#include<array>
#include "Direction.hpp"


class GBlocks : public sf::Drawable
{
public:
	GBlocks(sf::Texture& texture, int id);
	~GBlocks() = default;
	void rotate();

	void motion(Direction direction);
	void setPosition(const sf::Vector2i& position);
	void revertState();

	std::array<sf::Vector2i, 4>getBlockPositions() const;
	std::array<sf::Vector2i, 4>getNextBlockPositions(Direction direction) const;
	int getID() const;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Vector2i                   tPosition;
	int                            currentRotation;
	int                            tID;
	std::array<sf::Vector2i, 4>    tBlock;
	std::array<sf::Vector2i, 4>    previousBlock;
	mutable sf::Sprite             tSprite;
};
#endif   // UNTILTED_GBLOCKS_HPP



