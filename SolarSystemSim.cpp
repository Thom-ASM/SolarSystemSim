#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<math.h>
#include<sstream>
//Constants
const int PI = 3.14;
const float G = 6.67*pow(10, -11);
const int height = 1080;
const int width = 1920;

//Planet class
class Planet {
private:

	int planetRadius, xPos, yPos, xOrigin, yOrigin, orbitRadius;
	float currentAngle, planetMass, angularVelocity, orbitalPeriod;
	sf::Color planetColor;
public:
	Planet(int raduis, int x, int y, sf::Color planetColor, float angularVel);
	void update();
	void getOrbitInfo();
	sf::CircleShape planet;
};

//Global variables
int timeWarp = 1;
std::vector<Planet> planetArray;

//Planet constructor
Planet::Planet(int planetRadius, int x, int y, sf::Color color, float mass) {
	planetRadius = planetRadius;
	planetMass = mass;
	xOrigin = width / 2;
	yOrigin = height / 2;
	xPos = x;
	yPos = y;
	orbitRadius = sqrt(pow(xPos, 2) + pow(yPos, 2));
	currentAngle = 0;
	planetColor = color;
	planet.setOrigin(planetRadius, planetRadius);
	//The radius of the orbit of the sun is 0 and we can't / by 0
	if (orbitRadius != 0) {
		currentAngle = acos(yPos / orbitRadius) * 180 / PI;
	}
	planet.setPointCount(255);
	planet.setRadius(planetRadius);
	planet.setPosition((xPos + xOrigin), (yPos + yOrigin));
	planet.setFillColor(planetColor);
	planetArray.push_back(*this);
}
//Update the planets angle and position
void Planet::update() {
	getOrbitInfo();
	currentAngle += angularVelocity;
	if (currentAngle>360) {
		currentAngle = 0;
	}
	xPos = (xOrigin + (cos(-currentAngle*PI / 180)*orbitRadius));
	yPos = (yOrigin + (sin(-currentAngle*PI / 180)*orbitRadius));
	planet.setPosition(xPos, yPos);
}

//Find the angular velocity and time period of the orbit
void Planet::getOrbitInfo() {
	//Kepler's third law
	orbitalPeriod = sqrt(4 * pow(PI, 2) / (G*planetArray[0].planetMass)*pow(orbitRadius, 3)) / timeWarp;
	angularVelocity = (2 * PI) / orbitalPeriod;

}
int main() {
	// All of the planets + Pluto
	sf::RenderWindow window(sf::VideoMode(width, height), "Solar System sim");
	Planet Sun(50, 0, 0, sf::Color::Yellow, 5);
	Planet Mercury(2, 100, 100, sf::Color(100, 100, 100), 2);
	Planet Venus(4, 150, 150, sf::Color(139, 69, 19), 4);
	Planet Earth(5, 200, 200, sf::Color(77, 77, 255), 5);
	Planet Mars(3, 250, 250, sf::Color(255, 55, 55), 3);
	Planet Jupiter(9, 300, 300, sf::Color(201, 144, 57), 9);
	Planet Saturn(8, 300, 350, sf::Color(206, 184, 184), 8);
	Planet Uranus(7, 300, 400, sf::Color(40, 114, 144), 6);
	Planet Neptune(6, 300, 450, sf::Color(39, 70, 135), 7);
	Planet Pluto(1, 300, 500, sf::Color(180, 133, 112), 1);

	sf::Font font;
	font.loadFromFile("AvenirLTStd-Book.otf");
	while (window.isOpen())
	{
		std::ostringstream oss;
		oss << timeWarp;
		std::string timeWarpStr = ("Time Warp: " + oss.str());

		sf::Text warpValueText(timeWarpStr, font);
		warpValueText.setPosition(0, 0);

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
				// If mouse pressed
			case sf::Event::MouseButtonPressed: {
				//Get mouse position
				int posy = event.mouseButton.y;
				int posx = event.mouseButton.x;
				//Create a new earth like planet
				Planet newShape(5, posx - width / 2, posy - height / 2, sf::Color::Green, 5);
				break;
			}
			case sf::Event::KeyPressed:
				//Decrease timewarp value
				if (event.key.code == sf::Keyboard::Comma) {
					if (timeWarp > 1) {
						timeWarp = timeWarp / 10;
					}
				}
				//Increase time warp value
				else if (event.key.code == sf::Keyboard::Period) {
					if (timeWarp < pow(10, 9)) {
						timeWarp = timeWarp * 10;
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
			window.draw(planetArray[itr].planet);
		}
		window.draw(warpValueText);
		window.display();
	}
	return 0;
}
