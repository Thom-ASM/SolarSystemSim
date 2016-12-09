/*What I plan to do overall 
	*Collisions with planets
		-Check if get local bounds constains another planet
		-Remove both of the planets involved
		-Perhaps a small particle system
	*Fix custom Planets 
		-Something to do with the angle but I do not know what it is.
		-Partially works on one quadrant of a circle
	*Text interface to show planet information
		-Replace the command line with sf::text
		-Have to work out an elegant(ish) solution
	*N-Body physics
	*/
#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<math.h>
#include<sstream>
#include "Planets.h"
#include"CustomMouse.h"
#include"interfaceText.h"

//Global variables
const int height = 1080;
const int width = 1920;
int customPlanetCounter = 0;


int timewarp=1;
std::vector<Planet> planetArray;

int main() {
	// All of the planets + Pluto
	sf::RenderWindow window(sf::VideoMode(width, height), "Solar System sim");
	MouseC mouse(window);
	Planet Sun("Sun",50, sf::Vector2i(0,0), sf::Color::Yellow, 5,50,0);
	Planet Mercury("Mercury",2, sf::Vector2i(100,100), sf::Color(100, 100, 100),10, 2, 0);
	Planet Venus("Venus",4,sf::Vector2i(150, 150), sf::Color(139, 69, 19),4, 4, 0);
	Planet Earth("Earth",5, sf::Vector2i(200, 200), sf::Color(77, 77, 255), 5,5, 0);
	Planet Mars("Mars", 3, sf::Vector2i(250, 250), sf::Color(255, 55, 55),3, 3, 0);
	Planet Jupiter("Jupiter", 9, sf::Vector2i(300, 300), sf::Color(201, 144, 57),9, 9, 0);
	Planet Saturn("Saturn", 8, sf::Vector2i(300, 350), sf::Color(206, 184, 184),8, 8, 0);
	Planet Uranus("Uranus", 7, sf::Vector2i(300, 400), sf::Color(40, 114, 144), 6,6, 0);
	Planet Neptune("Neptune", 6, sf::Vector2i(300, 450), sf::Color(39, 70, 135), 7,7, 0);
	//I know you are not a planet but I still love you
	Planet Pluto("Pluto",1, sf::Vector2i(300, 500), sf::Color(180, 133, 112),1, 1, 0);

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
		interfaceText newText(sf::Vector2f(100, 100), sf::Color(255, 255, 255, 255));
		interfaceText newText2(sf::Vector2f(500, 500), sf::Color(255, 255, 255, 255));
		interfaceText newText3(sf::Vector2f(320, 200), sf::Color(255, 255, 255, 255));
		interfaceText newText4(sf::Vector2f(921, 532), sf::Color(255, 255, 255, 255));

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed: {
				sf::Vector2f mousePos = mouse.getPositionW();
				if (event.mouseButton.button == sf::Mouse::Right) {
					std::ostringstream planetNameStream;
					planetNameStream << "Custom Planet " << customPlanetCounter;
					std::string planetName = planetNameStream.str();
					sf::Vector2f mousePos = mouse.getPositionW();
					float orbitRadius = sqrt(pow((int)mousePos.x, 2) + pow((int)mousePos.y, 2));
					Planet newShape(planetName, 5, (sf::Vector2i)mousePos , sf::Color::Green, 5, 5, acos(mousePos.x / orbitRadius) * 180 / 3.14);
					customPlanetCounter++;
				}
				else {
					for (int itr2 = 0; itr2 < planetArray.size(); itr2++) {
						if (planetArray[itr2].checkMouse(window, mousePos)) {
							break;
						}
					}
				}
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
			//planetArray[itr].collision();
			window.draw(planetArray[itr].getRenderObjet());
		}
		window.draw(warpValueText);
		newText.updateText(planetArray[2].returnAngle());
		window.draw(newText.returnRenderObject());
		newText2.updateText(planetArray[2].returnAngle());
		window.draw(newText2.returnRenderObject());
		newText3.updateText(planetArray[2].returnAngle());
		window.draw(newText3.returnRenderObject());
		newText4.updateText(planetArray[2].returnAngle());
		window.draw(newText4.returnRenderObject());
		window.display();
	}
	return 0;
}