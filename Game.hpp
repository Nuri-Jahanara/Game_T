#pragma once
#ifndef UNTITLED_GAME_HPP
#define UNTITLED_GAME_HPP

#include "GBlocks.hpp"
#include "Grid.hpp"
#include "Highscores.hpp"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class Game
{
	friend class Grid;

public:
	Game();
	void run();

private:
	void proceed(Direction direction);
	void update(const sf::Time& date);
	void rotate();
	void createGameBlocks();
	bool isValidMotion(std::array<sf::Vector2i, 4>block);
	bool isOccupied(int x, int y);
	void processEvents();
	void render();



	sf::RenderWindow           tRenderWindow;
	sf::Texture                texture;
	sf::RectangleShape         tSeparationLine;
	std::unique_ptr<GBlocks>   tBlock;
	std::unique_ptr<GBlocks>   tPreview;
	std::unique_ptr<Grid>      tGrid;
	Highscores                 tHighscore;
	sf::Time                   tElapsedTime;
	int                        tID;
};

#endif  //UNTILED_GAME_HPP




