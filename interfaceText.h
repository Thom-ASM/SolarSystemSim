#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<math.h>
#include<sstream>
#include<ctime>
#include<cstdlib>
class interfaceText
{
private:
	std::string createString();
	std::ostringstream stringStream;
	sf::Text text;
	sf::Vector2f position;
	sf::Font font;
	sf::Color color;
	//DEBUG
	int currentAngle = 1;
	sf::Color generateRandomColors();
	
public:
	sf::Text returnRenderObject();
	interfaceText(sf::Vector2f textPosition, sf::Color textColor);
	void updateText(float currentangle);//std::string string, sf::Vector2f textPosition,  sf::Color textColor);
	~interfaceText();
};

