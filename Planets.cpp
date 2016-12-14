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
float Planet::getNetForce() {
	float currentForce;
	for (auto& planetItr: planetArray) {
		float distance = sqrt(pow(planetItr.returnPos().x- planetPos.x, 2)+ pow(planetItr.returnPos().y- planetPos.y,2));
		currentForce += (G*planetItr.returnMass()*planetMass) / pow(distance, 2);
	}
	return currentForce;
}
bool::Planet::checkMouse(sf::RenderWindow &window,sf::Vector2f mousePos) {
	if (planet.getGlobalBounds().contains(mousePos)) {
		return true;
	}
return false;
}

//Need to remove both of the objects in the collision;
void Planet::checkCollision() {
	for (int itr = 0; itr < planetArray.size(); itr++) {
		//Is there a collision and can both objects collide?
		if (isCollision(itr)) {
			std::string ColString = "Collision between " + planetName + " and: " + planetArray[itr].returnName();
			std::cout << ColString << '\n';
			//Release the colliding object from the vector and call its destructor
			planetArray.erase(planetArray.begin()+itr);
			break;
		}
	}
}
bool Planet::isCollision(int itr) {
	return (planet.getGlobalBounds().contains((sf::Vector2f)planetArray[itr].returnPos()) && &planetArray[itr] != this);
}
sf::CircleShape Planet::getRenderObjet() {
	return  planet;
}
float Planet::returnMass() {
	return planetMass;
}
std::string Planet::returnName() {
	return planetName;
}
sf::Vector2i Planet::returnPos() {
	return planetPos;
}
float Planet::returnAngle() {
	return currentAngle;
}
float  Planet::returnAngVel() {
	return angularVelocity;
}
sf::Color Planet::returnColor() {
	return planetColor;
}
int Planet::returnRadius() {
	return planetRadius;
}

Planet::~Planet()
{
	//Have to zero out the block of memory so that class data cannont be accsessed when removed 
	memset(this, NULL, sizeof(*this));
}