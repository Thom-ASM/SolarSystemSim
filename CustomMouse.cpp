#include "CustomMouse.h"
#include "Planets.h"

MouseC::MouseC(sf::RenderWindow& windowRef) : windowReference(windowRef) {
}
sf::Vector2i MouseC::getPositionP() {
	return getPosition(windowReference);

}

sf::Vector2f MouseC::getPositionW() {
	return windowReference.mapPixelToCoords(getPosition(windowReference));
}
int MouseC::checkEvent(sf::Event&event) {
	switch (event.mouseButton.button)
	{
	Left:
		std::ostringstream planetNameStream;
		planetNameStream << "Custom Planet " << 1;
		std::string planetName = planetNameStream.str();
		sf::Vector2f mousePos = getPositionW();
		Planet newShape(planetName, 5, (sf::Vector2i)mousePos, sf::Color::Green, 5, 5,5);
		//customPlanetCounter++;
		break;
	Right:
		for (int planetArrayitr = 0; planetArrayitr < planetArray.size(); planetArrayitr++) {
			if (planetArray[planetArrayitr].checkMouse(windowReference, getPositionW())) {
				break;
			}
		}
		
		break;
	Middle:
		break;
	}
	if (event.mouseButton.button==Left){} {
	}
}
//	windowRef = windowRef;

