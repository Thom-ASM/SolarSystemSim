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
	Planet(int raduis, int x, int y,  sf::Color planetColor, float angularVel);
	void update();
	void getOrbitInfo();
	sf::CircleShape planet;
};

//Global variables
int timeWarp = 1;
std::vector<Planet> planetArray;

//Planet constructor
Planet::Planet(int planetRadius, int x, int y,  sf::Color color, float mass) {
    this->planetRadius = planetRadius;
	this->planetMass = mass;
	this->xOrigin = width/2;
	this->yOrigin = height/2;
	this->xPos = x;
	this->yPos = y;
	this->orbitRadius = sqrt(pow(this->xPos,2)+pow(this->yPos,2));
	this->currentAngle = 0;
	this->planetColor = color;
	this->planet.setOrigin(this->planetRadius, this->planetRadius);
	//The radius of the orbit of the sun is 0 and we can't / by 0
	if (this->orbitRadius != 0) {
		this->currentAngle = acos(this->yPos / this->orbitRadius) * 180 / PI;
	}
	this->planet.setPointCount(255);
	this->planet.setRadius(this->planetRadius);
	this->planet.setPosition((this->xPos+this->xOrigin), (this->yPos+this->yOrigin));
	this->planet.setFillColor(this->planetColor);
}
//Update the planets angle and position
void Planet::update() {
	getOrbitInfo();
	this->currentAngle += this->angularVelocity;
	if (this->currentAngle>360) {
		this->currentAngle = 0;
	}
	this->xPos = (this->xOrigin + (cos(-currentAngle*3.14 / 180)*this->orbitRadius));
	this->yPos = (this->yOrigin + (sin(-currentAngle*3.14 / 180)*this->orbitRadius));
	this->planet.setPosition(this->xPos, this->yPos);
}

//Find the angular velocity and time period of the orbit
void Planet::getOrbitInfo() {
	//Kepler's third law
	this->orbitalPeriod = sqrt(4 * pow(PI, 2) / (G*planetArray[0].planetMass)*pow(this->orbitRadius, 3)) / timeWarp;
	this->angularVelocity = (2 * PI) / this->orbitalPeriod;
	
}
int main() {
	// All of the planets + Pluto
	sf::RenderWindow window(sf::VideoMode(width, height), "Solar System sim");
	Planet Sun(50, 0, 0,  sf::Color::Yellow, 5);
	planetArray.push_back(Sun);
	Planet Mercury(2, 100, 100, sf::Color(100, 100, 100), 2);
	planetArray.push_back(Mercury);
	Planet Venus(4, 150, 150,  sf::Color(139, 69, 19), 4);
	planetArray.push_back(Venus);
	Planet Earth(5, 200, 200, sf::Color(77, 77, 255), 5);
	planetArray.push_back(Earth);
	Planet Mars(3, 250, 250, sf::Color(255, 55, 55), 3);
	planetArray.push_back(Mars);
	Planet Jupiter(9, 300, 300, sf::Color(201, 144, 57), 9);
	planetArray.push_back(Jupiter);
	Planet Saturn(8, 300, 350, sf::Color(206,184,184), 8);
	planetArray.push_back(Saturn);
	Planet Uranus(7, 300, 400, sf::Color(40,114,144), 6);
	planetArray.push_back(Uranus);
	Planet Neptune(6, 300, 450, sf::Color(39,70,135), 7);
	planetArray.push_back(Neptune);
	//I know you are not a planet but I still love you
	Planet Pluto(1, 300, 500, sf::Color(180, 133, 112), 1);
	planetArray.push_back(Pluto);

	sf::Font font;
	font.loadFromFile("AvenirNextLTPro-Cn.otf");
	while (window.isOpen())
	{
		std::ostringstream oss;
		oss << timeWarp;
		std::string timeWarpStr =("Time Warp: "+oss.str());
		
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
				Planet newShape(5, posx-width/2, posy-height/2,  sf::Color::Green, 5);
				planetArray.push_back(newShape);
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
