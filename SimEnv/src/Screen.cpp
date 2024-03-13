
#include <SFML/Graphics.hpp>
#include <iostream>

unsigned int width = 1700;
unsigned int height = 900;

const float zoomAmount = 1.02f;

sf::RenderWindow window(sf::VideoMode(width, height), "Simulation Environment");

sf::View view(sf::Vector2f(0, 0), sf::Vector2f((float)width, (float)height));