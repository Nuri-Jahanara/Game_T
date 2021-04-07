#pragma once
#include "Grid.hpp"
#include "Game.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>

FieldInfo::FieldInfo(sf::Texture& texture, int id) {
	sf::IntRect rect{ (id % 7) * 18, 0, 18, 18 };
	tSprite.setTexture(texture);
	tSprite.setTextureRect(rect);

}
Field& Field::operator=(const Field& field) {
	this->tOccupied = field.tOccupied;
	this->tVisible = field.tVisible;
	this->tInfo = field.tInfo;
	return *this;
}

Grid::Grid(sf::Vector2i size, Game& Game) :
	tGame(Game), tField(), tFieldInfo(), tSize(size), tCleaned(), tElapsedTime(0.f), tToRemoveBlocks(false) {
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			tField[convert2D_to_1D(x, y)] = std::make_unique<Field>();
		}
	}
	for (int id = 0; id < 7; ++id) {
		tFieldInfo[id] = std::make_unique<FieldInfo>(tGame.texture, id);
	}
}

void Grid::addBlock(int id, std::array<sf::Vector2i, 4>block) {
	for (int i = 0; i < 4; ++i) {
		auto field = getField(block[i].x, block[i].y);
		field->tOccupied = true;
		field->tInfo = tFieldInfo[i].get();
	}
}


int Grid::convert2D_to_1D(int x, int y) {
	return y * tSize.x + x;
}

void Grid::draw(sf::RenderWindow& window) {
	for (int x = 0; x < tSize.x; ++x) {
		for (int y = 0; y < tSize.y; ++y) {
			auto field = getField(x, y);
			//if field is not occupied already,tInfo would be assigned nUllptr
			if (field->tOccupied && field->tVisible) {
				field->tInfo->tSprite.setPosition(x * 18.f, y * 18.f);
				window.draw(field->tInfo->tSprite);
			}
		}
	}
}

// Implement these methods
void Grid::update(const sf::Time& date)
{

}

void Grid::clean()
{

}

bool Grid::isOccupied(std::array<sf::Vector2i, 4>block)
{
	for (sf::Vector2i currentBlock : block) {
		auto field = getField(currentBlock.x, currentBlock.y);
		if (field->tOccupied)
			return true;
	}
	return false;
}

void Grid::printGrid()
{

}

Field* Grid::getField(int x, int y)
{
	return tField[convert2D_to_1D(x, y)].get();
}
