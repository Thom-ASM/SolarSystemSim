#include "interfaceText.h"

interfaceText::interfaceText(sf::Vector2f textPosition, sf::Color textColor):position(textPosition),color(textColor)
{

	font.loadFromFile("AvenirNextLTPro-Cn.otf");
	text.setString(createString());
	text.setPosition(position);
	text.setFont(font);
	text.setColor(color);
}

std::string interfaceText::createString() {
	std::string TESTSTRING="DEBUG";
	return TESTSTRING;
}

void interfaceText::updateText(float currentAngle){//std::string string, sf::Vector2f textPosition, sf::Color textColor) {
	text.setString(createString());
	position.x = (cos(currentAngle*3.14 / 180)* position.x/2);
	position.y = (sin(currentAngle*3.14 / 180)* position.y/ 2);
	text.setPosition(position);
	text.setColor(generateRandomColors());
	//std::cout << text.getPosition().x<<" " << text.getPosition().y <<'\n';
	currentAngle+=1;
}

sf::Text interfaceText::returnRenderObject() {
	return text;
}
sf::Color interfaceText::generateRandomColors() {
	srand(time(NULL));
	sf::Color newColor (rand()%255, rand() % 255, rand() % 255,255);
	return newColor;
}
interfaceText::~interfaceText()
{
}
