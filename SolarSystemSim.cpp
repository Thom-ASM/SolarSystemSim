#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<math.h>
#include<sstream>
#include"Planets.h"

//Global variables
const int height = 1080;
const int width = 1920;

int timewarp=1;
std::vector<Planet> planetArray;

int main() {
	// All of the planets + Pluto
	sf::RenderWindow window(sf::VideoMode(width, height), "Solar System sim");
	Planet Sun("Sun",50, sf::Vector2i(0,0), sf::Color::Yellow, 5,50);
	Planet Mercury("Mercury",2, sf::Vector2i(100,100), sf::Color(100, 100, 100),10, 2);
	Planet Venus("Venus",4,sf::Vector2i(150, 150), sf::Color(139, 69, 19),4, 4);
	Planet Earth("Earth",5, sf::Vector2i(200, 200), sf::Color(77, 77, 255), 5,5);
	Planet Mars("Mars", 3, sf::Vector2i(250, 250), sf::Color(255, 55, 55),3, 3);
	Planet Jupiter("Jupiter", 9, sf::Vector2i(300, 300), sf::Color(201, 144, 57),9, 9);
	Planet Saturn("Saturn", 8, sf::Vector2i(300, 350), sf::Color(206, 184, 184),8, 8);
	Planet Uranus("Uranus", 7, sf::Vector2i(300, 400), sf::Color(40, 114, 144), 6,6);
	Planet Neptune("Neptune", 6, sf::Vector2i(300, 450), sf::Color(39, 70, 135), 7,7);
	//I know you are not a planet but I still love you
	Planet Pluto("Pluto",1, sf::Vector2i(300, 500), sf::Color(180, 133, 112),1, 1);

	sf::View view;
	//Makes the camera center be at the coordinates (0,0) 
	view.reset(sf::FloatRect(-width/2, -height/2, width, height));
	window.setView(view);

	sf::Font font;
	font.loadFromFile("AvenirNextLTPro-Cn.otf");
	while (window.isOpen())
	{
		std::ostringstream oss;
		oss << timewarp;
		std::string timeWarpStr = ("Time Warp: " + oss.str());

		sf::Text warpValueText(timeWarpStr, font);
		warpValueText.setPosition(-width/2, -height/2);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
				// If mouse pressed
			case sf::Event::MouseButtonPressed: {
				//Create a new earth like planet
				//Planet newShape("CustomPlanet",5, sf::Mouse::getPosition(window), sf::Color::Green,5, 5);
				planetArray[0].getNetForce();
				break;
			}
			case sf::Event::KeyPressed:
				//Decrease timewarp value
				if (event.key.code == sf::Keyboard::Comma) {
					if (timewarp > 1) {
						timewarp = timewarp / 10;
					}
				}
				//Increase time warp value
				else if (event.key.code == sf::Keyboard::Period) {
					if (timewarp < pow(10, 9)) {
						timewarp = timewarp * 10;
					}
				}
				//Exit program
				else if (event.key.code == sf::Keyboard::Escape) {
					window.close();
				}
				break;
			}
		}
		window.clear();
		//Loop through all of the planets and update and draw them
		for (int itr = 0; itr<planetArray.size(); itr++) {
			planetArray[itr].update();
			window.draw(planetArray[itr].getRenderObjet());
		}
		window.draw(warpValueText);
		window.display();
	}
	return 0;
}
