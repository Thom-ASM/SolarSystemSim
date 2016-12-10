#include "interfaceText.h"

interfaceText::interfaceText(sf::Vector2f textPosition, sf::Color textColor,std::string String):position(textPosition),color(textColor),string(String){
	font.loadFromFile("AvenirNextLTPro-Cn.otf");
	text.setString(string);
	text.setPosition(position);
	text.setFont(font);
	text.setColor(color);
	textArray.push_back(*this);
}

void interfaceText::updateText(std::string String, sf::Vector2f textPosition, sf::Color textColor) {
	srand(time(NULL));
	string = String;
	position = textPosition;
	text.setString(string);
	text.setPosition(position);
	text.setColor(textColor);
}

sf::Text interfaceText::returnRenderObject() {
	return text;
}
sf::Vector2f interfaceText::returnTextPosition() {
	return position;
}
std::string  interfaceText::returnString() {
	return string;
}

