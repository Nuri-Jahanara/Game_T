#pragma once
#include "Game.hpp"
#include "Grid.hpp"
#include "Highscores.hpp"
#include "Utilities.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <SFML/Window/Event.hpp>


Game::Game() : tRenderWindow
{ sf::VideoMode{10 * 18 + 100, 18 * 18},"Tetris Game", sf::Style::Default },
texture(), tSeparationLine(), tBlock(nullptr), tGrid(), tHighscore(), tElapsedTime(sf::Time::Zero), tID(getRandomNumb(7))
{
	tSeparationLine.setSize(sf::Vector2f{ 1.f, 18.f * 18.f });
	tSeparationLine.setPosition(sf::Vector2f{ 10.f * 18.f, 0 });
	tSeparationLine.setFillColor(sf::Color::Cyan);

	if (!texture.loadFromFile("Tetrominos.png")) {
		std::cout << "Game:Game()-could not loadtTexture\n";
	};
	tGrid == std::make_unique<Grid>(sf::Vector2i{ 10,18 }, *this);

	createGameBlocks();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time deltaTime{ sf::Time::Zero };
	while (tRenderWindow.isOpen()) {
		sf::Time trigger{ sf::seconds(85.f + (tHighscore.getLevel() * (tHighscore.getLevel() * 5.f))) };
		deltaTime = clock.restart();
		tElapsedTime += deltaTime;
		processEvents();
		update(deltaTime);
		if (tElapsedTime > trigger) {
			tElapsedTime = sf::Time::Zero;
			proceed(Direction::Down);
		}
		render();
	}
}

void Game::update(const sf::Time& dt) {
	tGrid->update(dt);
	tHighscore.update(dt);
	if (!tBlock) {
		if (tGrid->isToRemoveBlocks()) {
			return;
		}
		createGameBlocks();
	}

}

void Game::rotate()
{
	if (!tBlock) return;
	tBlock->rotate();
	if (!isValidMotion(tBlock->getBlockPositions())) {
		tBlock->revertState();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (tRenderWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) tRenderWindow.close();
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::D) {
				proceed(Direction::SoftDown);
			}
			else if (event.key.code == sf::Keyboard::R) {
				proceed(Direction::Right);
			}
			else if (event.key.code == sf::Keyboard::L) {
				proceed(Direction::Left);
			}
			else if (event.key.code == sf::Keyboard::Space) {
				rotate();
			}
			else if (event.key.code == sf::Keyboard::P) {
				tGrid->printGrid();
			}
			else if (event.key.code == sf::Keyboard::C) {
				tHighscore.addLinesCleared(10);
			}
		}
	}
}
void Game::render() {
	tRenderWindow.clear(sf::Color::White);
	tHighscore.draw(tRenderWindow);
	tGrid->draw(tRenderWindow);
	if (tBlock)tRenderWindow.draw(*tBlock);

	tRenderWindow.draw(*tPreview);
	tRenderWindow.draw(tSeparationLine);
	tRenderWindow.display();
}
void Game::proceed(Direction direction) {
	if (!tBlock) return;
	if (isValidMotion(tBlock->getBlockPositions())) {
		tBlock->motion(direction);
		if (direction == Direction::SoftDown)tHighscore.addSoftScore(1);
	}
	else {
		if (direction == Direction::Down || direction == Direction::SoftDown) {
			int id = tBlock->getID();
			tGrid->addBlock(id, tBlock->getBlockPositions());
			tBlock.reset(nullptr);
			tHighscore.sumSoftScore();

		}
	}
}
bool Game::isValidMotion(std::array<sf::Vector2i, 4>block) {
	for (int i = 0; i < 4; ++i) {
		if (block[i].x < 0 || block[i].x>9 || block[i].y > 17) {
			return false;
		}
	}
	return true;
}

bool Game::isOccupied(int x, int y) {
	return tGrid->getField(x, y)->tOccupied;
}
void Game::createGameBlocks() {
	tBlock.reset(new GBlocks{ texture,tID });
	//create New Game
	if (tGrid->isOccupied(tBlock->getBlockPositions())) {
		tGrid->clean();
		tHighscore.reset();
	}
	tID = getRandomNumb(7);
	tPreview.reset(new GBlocks{ texture, tID });  //tBlock must be defined
	tPreview->setPosition(sf::Vector2i{ 11,12 });
}