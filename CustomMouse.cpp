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
MouseC::~MouseC() {

}

