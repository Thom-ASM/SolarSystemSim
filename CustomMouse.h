#include<SFML/Graphics.hpp>
#include<sstream>
#include<iostream>
//This is a warpper (... I think...) for the sf::Mouse class
class MouseC: public sf::Mouse
{
public:
	MouseC(sf::RenderWindow& windowRef);
	//Get position in pixles, 
	sf::Vector2i getPositionP();
	//Get the poition of the mouse in world view
	sf::Vector2f getPositionW();
	int checkEvent(sf::Event &event);

private:
	sf::RenderWindow &windowReference;
	
};

