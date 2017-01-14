#include<SFML/Graphics.hpp>
//This is a warpper (... I think...) for the sf::Mouse class
class MouseC: public sf::Mouse
{
public:
	MouseC(sf::RenderWindow& windowRef);
	//Get position in pixles, 
	sf::Vector2i getPositionP();
	//Get the poition of the mouse in world view
	sf::Vector2f getPositionW();
	~MouseC();
private:
	sf::RenderWindow &windowReference;
	
};

