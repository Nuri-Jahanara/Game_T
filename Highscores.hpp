#pragma once
#ifndef UNTITLED_HIGHSCORES_HPP
#define UNTITLED_HIGHSCORES_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>


class Highscores {
public:
	Highscores();
	Highscores(const Highscores& other) = delete;

	void draw(sf::RenderWindow& window);
	void reset();
	void addSoftScore(int score);
	void sumSoftScore();
	void addLinesCleared(int num);
	void update(const sf::Time& date);
	int getLevel() const;

private:
	sf::Font font;
	sf::Text levelText;
	sf::Text scoreText;
	sf::Text linesClearedText;
	int gameScore;
	int loadSoftScore;
	int linesCleared;
};

#endif //UNTITLED_HIGHSCORES_HPP
