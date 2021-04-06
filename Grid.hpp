#pragma once
#ifndef UNTITLLED_GRID_HPP
#define UNTITLED_GRID_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <array>
#include <vector>
#include <unordered_map>

class Game;
struct FieldInfo {
	FieldInfo(sf::Texture& texture, int id);
	sf::Sprite  tSprite;
};
struct Field {
	Field& operator=(const Field& field);
	bool tOccupied = false;
	bool tVisible = true;
	FieldInfo* tInfo = nullptr;
};

class Grid
{
public:
	Grid(sf::Vector2i size, Game& game);
	Grid(const Grid& other) = delete;
	Grid& operator=(const Grid& other) = delete;

	void update(const sf::Time& date);
	void clean();
	void addBlock(int id, std::array<sf::Vector2i, 4>block);
	bool isOccupied(std::array<sf::Vector2i, 4>block);
	void draw(sf::RenderWindow& window);
	void printGrid();
	inline bool isToRemoveBlocks() const { return tToRemoveBlocks; }
	Field* getField(int x, int y);

private:
	int convert2D_to_1D(int x, int y);
	void cleanLines();
	void linesToRemove();
	void blink();

	Game& tGame;
	std::unordered_map<unsigned int, std::unique_ptr<Field>>               tField;
	std::unordered_map<unsigned int, std::unique_ptr<FieldInfo>>           tFieldInfo;
	sf::Vector2i                                                           tSize;
	std::vector<int>                                                       tCleaned;
	float                                                                  tElapsedTime;
	bool                                                                   tToRemoveBlocks;

};
#endif //UNTITLLED_GRID_HPP