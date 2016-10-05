#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<math.h>
const int PI =3.14;
const float G=6.67*pow(10,-11);
int timeWarp=1;

class Circle{
    private :
        int getOrbitInfo();
        int radius,xPos,yPos,xOrigin,yOrigin;
        int semiMajorAxis;
        int orbitRadius;
        float currentAngle,mass,angularVelocity,orbitalPeriod;
        sf::Color planetColor;
    public:
        Circle(int raduis,int x,int y,int orbitRadius,sf::Color planetColor,float angularVel);
        void update();        
        sf::CircleShape planet;
};
Circle::Circle(int radius,int x,int y,int OrbitRadius,sf::Color color,float mass){
      this->radius=radius;
      this->orbitRadius=OrbitRadius;
      this->mass=mass;
      this->xOrigin=500;
      this->yOrigin=360;
      this->xPos=x+this->xOrigin;
      this->yPos=y+this->yOrigin;
      this->currentAngle=0;       
      this->planetColor=color;
      this->planet.setOrigin(this->radius,this->radius);
      this->planet.setPointCount(255);
      this->planet.setRadius(this->radius);  
      this->planet.setPosition(this->xPos,this->yPos);
      this->planet.setFillColor(this->planetColor);
}

void Circle::update(){   
    getOrbitInfo();   
this->currentAngle+=this->angularVelocity;
    if (this->currentAngle>360){
       this->currentAngle=0;}
    this->xPos=(this->xOrigin+(cos(-currentAngle*3.14/180)*this->orbitRadius));
    this->yPos=(this->yOrigin+(sin(-currentAngle*3.14/180)*this->orbitRadius));
    this->planet.setPosition(this->xPos,this->yPos);
    }
std::vector<Circle> planetArray;
    
int Circle::getOrbitInfo(){
//Kepler's third law
this->orbitalPeriod=sqrt(4*pow(PI,2)/(G*planetArray[0].mass)*pow(this->orbitRadius,3))/timeWarp;
this->angularVelocity=(2*PI)/this->orbitalPeriod;
} 
int main(){
int height=720;
int width=1000;
    sf::RenderWindow window(sf::VideoMode(width, height), "Solar System sim");  
Circle Sun(50,width/2,height/2,0,sf::Color::Yellow,5);
planetArray.push_back(Sun);
Circle Mercury(7,400,360,150,sf::Color(100,100,100),5);
planetArray.push_back(Mercury);
Circle Venus(7,400,360,200,sf::Color(139,69,19),4);
planetArray.push_back(Venus);
Circle Earth(7,400,360,250,sf::Color(77,77,255),3);
planetArray.push_back(Earth);
Circle Mars(7,400,360,300,sf::Color(255,55,55),2);
planetArray.push_back(Mars);
Circle Jupiter(7,400,360,350,sf::Color(201,144,57),1);
planetArray.push_back(Jupiter);
 while (window.isOpen())
    {
        sf::Event event;
         while (window.pollEvent(event))
        {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:{
                    int posy=event.mouseButton.y;
                    int posx=event.mouseButton.x;
                    Circle newShape(50,posx,posy,125,sf::Color::Green,5);
                    planetArray.push_back( newShape);
                    break;
}
                case sf::Event::KeyPressed:
                     if(event.key.code== sf::Keyboard::Comma){
                            if (timeWarp>10){
                                timeWarp=timeWarp/10;}
                     }else if(event.key.code==sf::Keyboard::Period){
                            if(timeWarp<pow(10,9)){
                                timeWarp=timeWarp*10;}
                    }break;
              }
        }
                     
                                   
        

        window.clear();
 	for (int itr=0;itr<planetArray.size();itr++){
            planetArray[itr].update();
            window.draw(planetArray[itr].planet);       
}
        window.display();
    }
    return 0;
}
