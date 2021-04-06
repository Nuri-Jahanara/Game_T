#include <SFML/System/TIme.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Highscores.hpp"
#include "Direction.hpp"
#include "infoBlock.hpp"
#include "GBlocks.hpp"
#include "Grid.hpp"
#include "Utilities.hpp"
#include<chrono>

std::default_random_engine engine{
	static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()) };

int getRandomNumb(int max) {
	std::uniform_int_distribution<int>int_distribution(max);
	return int_distribution(engine);
}


int getRandomNumb(int min, int max) {
	std::uniform_int_distribution<int>int_distribution(min, max);
	return int_distribution(engine);
}