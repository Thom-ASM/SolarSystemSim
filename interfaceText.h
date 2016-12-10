#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<math.h>
#include<sstream>
#include<ctime>
#include<cstdlib>
class interfaceText{
private:
	sf::Text text;
	sf::Vector2f position;
	sf::Font font;
	sf::Color color;
	std::string string;
public:
	interfaceText(sf::Vector2f textPosition, sf::Color textColor,std::string String);
	void updateText(std::string string, sf::Vector2f textPosition,  sf::Color textColor);
	sf::Vector2f returnTextPosition();
	std::string returnString();
	sf::Text returnRenderObject();
};
extern std::vector<interfaceText>  textArray;
extern interfaceText planetInfoTextArray[5];
