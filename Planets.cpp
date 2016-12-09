#include"Planets.h"



Planet::Planet(std::string name,int radius, sf::Vector2i position, sf::Color color, float mass,float initalVelocity,float currentang):planetName(name),planetRadius(radius), planetPos(position),planetColor(color),planetMass(mass),currentAngle(currentang){
	orbitRadius= sqrt(pow((int)planetPos.x, 2) + pow((int)planetPos.y, 2));//Will need to change this when I use eliptical orbits
	planet.setOrigin(planetRadius, planetRadius);
	//The radius of the orbit of the sun is 0 and we can't / by 0
	planet.setPointCount(255);
	planet.setRadius(planetRadius);
	planet.setPosition((sf::Vector2f)planetPos);
	planet.setFillColor( planetColor);
	planetArray.push_back(*this);
}

void Planet::update() {
	 getNetForce();
	 orbitalPeriod = sqrt(4 * pow(PI, 2) / (G*planetArray[0].planetMass)*pow( orbitRadius, 3))/timewarp;
	 angularVelocity = (2 * PI) /  orbitalPeriod;
	 currentAngle +=  angularVelocity;

	if ( currentAngle>360) {
		 currentAngle = 0;
	}
	//netForce = getNetForce();
	//Update Position
	 planetPos.x = (cos(currentAngle*PI / 180)* orbitRadius);
	 planetPos.y = (sin(currentAngle*PI / 180)* orbitRadius);
	 planet.setPosition((sf::Vector2f) planetPos);
	 checkCollision();
}

sf::CircleShape Planet::getRenderObjet() {
	return  planet;
}
float Planet::returnMass() {
	return planetMass;
}
float Planet::getNetForce() {
	float currentForce;
	for (int planetItr = 0; planetItr < planetArray.size(); planetItr++) {
		sf::Vector2i currentPlanetPos = planetArray[planetItr].returnPos();
		float distance = sqrt(pow(currentPlanetPos.x - planetPos.x, 2)+ pow(currentPlanetPos.y- planetPos.y,2));
		//std::cout <<"Distance from "<<planetName<<" to "<<planetArray[planetItr].returnName()<<" : "<< distance << '\n';
		currentForce += (G*planetArray[planetItr].returnMass()*planetMass)/pow(distance,2);
		
	}
	return currentForce;
}
std::string Planet::returnName() {
	return planetName;
}
sf::Vector2i Planet::returnPos() {
	return (planetPos);
}
bool::Planet::checkMouse(sf::RenderWindow &window,sf::Vector2f mousePos) {
		if (planet.getGlobalBounds().contains(mousePos)) {
			std::cout <<returnPlanetInfo()<<'\n';
			return true;
		}else {
			return false;
		}
}
std::string Planet::returnPlanetInfo() {
	std::ostringstream stringStream;
	stringStream << "Planet Name: " << planetName << "\n \t Position: " << planetPos.x <<" , "<< planetPos.y << "\n \t Mass: " << planetMass << "\n \t Radius: " << planetRadius << "\n \t Angular Velocity: " << angularVelocity;
	std::string infoString = stringStream.str();
	return infoString;
}
//Need to remove both of the objects in the collision;
void Planet::checkCollision() {
	for (int itr = 0; itr < planetArray.size(); itr++) {
		if (isCollision(itr)) {
			std::ostringstream stringStream;
			stringStream << "Collision between " << planetName << " and: " << planetArray[itr].returnName();
			std::string ColString = stringStream.str();
			std::cout << ColString << '\n';
		}
	}
}

bool Planet::isCollision(int itr) {
	return (planet.getGlobalBounds().contains((sf::Vector2f)planetArray[itr].returnPos()) && &planetArray[itr] != this);
}

//DEBUG


float Planet::returnAngle() {
	return currentAngle;
}
