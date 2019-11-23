#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <ctime>

struct Sign
{
	std::string name;
	sf::Text text;
	sf::Font font;
};

void LEVEL();