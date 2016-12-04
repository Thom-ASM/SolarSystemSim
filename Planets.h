#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<math.h>
#include<sstream>
//Constants
const float PI = 3.14;
const float G = 6.67*pow(10, -11);



//Planet class
class Planet {
private:
	//Variables
	int planetRadius, orbitRadius;
	float currentAngle, planetMass, angularVelocity, orbitalPeriod, netForce,velocity;
	sf::Color planetColor;
	sf::Vector2i planetPos;
	sf::CircleShape planet;
	//Functions
	//float getNetForce();
	std::string planetName;
	std::string returnPlanetInfo();
	
public:
	//Variables

	//Functions
	Planet(std::string name,int raduis, sf::Vector2i Position, sf::Color planetColor, float mass, float initalVelocity);
	void update();
	float getNetForce();
	float returnMass();
	bool checkMouse(sf::RenderWindow &window, sf::Vector2f mousePos);
	std::string returnName();
	sf::CircleShape getRenderObjet();
	sf::Vector2i returnPos();
};

//External Variables
extern std::vector<Planet> planetArray;
extern int timewarp;

