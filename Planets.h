#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<math.h>
//Constants
const float PI = 3.14;
const float G = 6.67*pow(10, -11);



//Planet class
class Planet {
private:
	//Variables
	int planetRadius, orbitRadius;
	float currentAngle, planetMass, angularVelocity, orbitalPeriod, fx,fy,vx, vy,velocity;
	float acc;
	sf::Color planetColor;
	sf::Vector2i planetPos;
	sf::CircleShape planet;
	//Functions
	//float getNetForce();
	std::string planetName;
	bool isCollision(Planet* collidingPlanet);
	void checkCollision();
	float dt = 1 / 60;
	
	
public:
	//Functions
	
	void update();
	bool checkMouse(sf::RenderWindow &window, sf::Vector2f mousePos);
	Planet(std::string name, int raduis, sf::Vector2i Position, sf::Color planetColor, float mass, float initalVelocity, float currentang);

	//Return functions- Is there a better way of doing this? I would rather keep the class attributes private 
	
	float returnAngVel();
	float returnAngle();
	void getNetForce();
	float returnMass();
	int returnRadius();
	sf::Color returnColor();
	std::string returnName();
	sf::CircleShape getRenderObjet();
	sf::Vector2i returnPos();

	~Planet();
	
};

//External Variables
extern std::vector<Planet> planetArray;
extern int timewarp;


