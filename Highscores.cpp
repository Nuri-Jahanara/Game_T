#include <SFML/System/TIme.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Highscores.hpp"
#include "Direction.hpp"
#include "infoBlock.hpp"
#include "GBlocks.hpp"
#include "Grid.hpp"


Highscores::Highscores()
	:font(), levelText(), scoreText(), linesClearedText(), gameScore(), loadSoftScore(),
	linesCleared(0) {
	font.loadFromFile("Arial.ttf");
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);

	levelText.setFont(font);
	levelText.setCharacterSize(20);
	scoreText.setPosition(sf::Vector2f{ 10 * 18 + 3, 50.f });
	levelText.setPosition(sf::Vector2f{ 10 * 18 + 3, 100.f });

	linesClearedText.setFont(font);
	linesClearedText.setCharacterSize(20);
	linesClearedText.setPosition(10 * 18 + 3, 150.f);

}

void Highscores::update(const sf::Time& date) {
	levelText.setString(std::string{ "LEVEL:\n" + std::to_string(linesCleared / 10) });
	scoreText.setString(std::string{ "SCORE:\n" + std::to_string(gameScore) });
	linesClearedText.setString(std::string{ "LINES:\n" + std::to_string(linesCleared) });
}
void Highscores::reset() {
	linesCleared = 0;
	gameScore = 0;
}

void Highscores::addSoftScore(int gameScore) {
	loadSoftScore += gameScore;
}

void Highscores::sumSoftScore() {
	gameScore += loadSoftScore;
	loadSoftScore = 0;
}

void Highscores::draw(sf::RenderWindow& window) {
	window.draw(levelText);
	window.draw(scoreText);
	window.draw(linesClearedText);
}

void Highscores::addLinesCleared(int num) {
	linesCleared += num;
	int level = linesCleared / 10;
	switch (num) {
	case(1): {
		gameScore += 40 * (level + 1);
		break;
	}
	case (2): {
		gameScore += 100 * (level + 1);
		break;
	}
	case (3): {
		gameScore += 300 * (level + 1);
		break;
	}
	case (4): {
		gameScore += 1200 * (level + 1);
		break;
	}
	}
}

int Highscores::getLevel() const {
	return linesCleared / 10;
}