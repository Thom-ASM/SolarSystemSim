/*What I plan to do overall 
	*Fix custom Planets 
		-Something to do with the angle but I do not know what it is.
		-Partially works on one half of a circle
	*N-Body physics
	*/
#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<math.h>
#include "Planets.h"
#include"CustomMouse.h"
#include"interfaceText.h"
#include"FIleIO.h"



//Global variables
const int height = 1080;
const int width = 1920;
int planetCounter = 0;
int timewarp=1;
std::vector<Planet> planetArray;
std::vector<interfaceText> textArray;

int main() {
	//Removed some of the planets so its easy to test
	std::string inputString;
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
	Planet Pluto("Pluto",1, sf::Vector2i(300, 500), sf::Color(180, 133, 112),1, 1, 0);
	//Pointer to the activePlanet object
	Planet* activePlanet=&Sun;
	//All of the default text
	interfaceText planetNameTxt(sf::Vector2f(width*.3, -height*.5), sf::Color(255, 255, 255, 255), "", 30);
	interfaceText planetPosTxt(sf::Vector2f(width*.3, -height*.475), sf::Color(255, 255, 255, 255), "", 30);
	interfaceText planetMassTxt(sf::Vector2f(width*.3, -height*.45), sf::Color(255, 255, 255, 255), "", 30);
	interfaceText planetAngVelTxt(sf::Vector2f(width*.3, -height*.425), sf::Color(255, 255, 255, 255), "", 30);
	interfaceText planetRadiusTxt(sf::Vector2f(width*.3, -height*.4), sf::Color(255, 255, 255, 255), "", 30);
	interfaceText timeWarpText(sf::Vector2f(-width / 2, -height / 2), sf::Color(255, 255, 255, 255), "TimeWarp: 1", 30);
	interfaceText planetInfoText(sf::Vector2f(width*.3, -height*.375), sf::Color(255, 255, 255, 255), "", 30);

	sf::View view;
	//Makes the camera center be at (0,0) 
	view.reset(sf::FloatRect(-width/2, -height/2, width, height));
	window.setView(view);

	while (window.isOpen())
	{
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
					sf::Vector2f mousePos = mouse.getPositionW();
					float orbitRadius = sqrt(pow((int)mousePos.x, 2) + pow((int)mousePos.y, 2));
					Planet newShape("Custom planet "+std::to_string(planetCounter), 5, (sf::Vector2i)mousePos , sf::Color::Green, 5, 5, acos(mousePos.x / orbitRadius) * 180 / 3.14);
					planetCounter++;
				}
				else {
					for (int itr2 = 0; itr2 < planetArray.size(); itr2++) {
						if (planetArray[itr2].checkMouse(window, mousePos)) {
							activePlanet = &planetArray[itr2];
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
					break;
				}
				else if (event.key.code == sf::Keyboard::I) {
				}
				textArray[5].updateText("Timewarp: " + std::to_string(timewarp), textArray[5].returnTextPosition(), sf::Color::White, 30);
				break;
			}
		}
		window.clear();
		for (auto& planetItr : planetArray) {
			planetItr.update();
			window.draw(planetItr.getRenderObjet());
		}
		for (auto& textItr : textArray) {
			sf::Color planetColor = activePlanet->returnColor();
			textArray[0].updateText("Planet name: " + activePlanet->returnName(), textArray[0].returnTextPosition(), planetColor, 30);
			textArray[1].updateText("Planet pos: " + (std::to_string(activePlanet->returnPos().x) + " , " + std::to_string(activePlanet->returnPos().y)), textArray[1].returnTextPosition(), planetColor, 30);
			textArray[2].updateText("Planet mass: " + std::to_string(activePlanet->returnMass()), textArray[2].returnTextPosition(), planetColor, 30);
			textArray[3].updateText("Planet angle: " + std::to_string(activePlanet->returnAngle()), textArray[3].returnTextPosition(), planetColor, 30);
			textArray[4].updateText("Planet radius: " + std::to_string(activePlanet->returnRadius()), textArray[4].returnTextPosition(), planetColor,30);
			textArray[6].updateText(ReturnTextItem(activePlanet->returnName(), "planetTextFileA.txt"), textArray[6].returnTextPosition(), planetColor,20);
			window.draw(textItr.returnRenderObject());
		}

		window.display();
	}
	return 0;
}



