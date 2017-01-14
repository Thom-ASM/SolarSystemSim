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
	int textSize;
public:
	interfaceText(sf::Vector2f textPosition, sf::Color textColor,std::string String, int textSize);
	void updateText(std::string string, sf::Vector2f textPosition,  sf::Color textColor, int textSize);
	sf::Vector2f returnTextPosition();
	std::string returnString();
	sf::Text returnRenderObject();
	~interfaceText();
};
extern std::vector<interfaceText>  textArray;
