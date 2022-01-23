#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

template <class T>
class Object
{
	sf::Vector2f _speed;
public:
	T shape;
	sf::Text name;

	Object(sf::Text text, T shape, sf::Vector2f speed)
		:name(text),
		shape(shape),
		_speed(speed)
	{
    }
	sf::Vector2f getSpeed() const
	{
		return _speed;
	}
	void setSpeed(sf::Vector2f newSpeed)
	{
		_speed = newSpeed;
	}
};


int main(int argc, char * argv[])
{
	// window W H
	// Font F S R G B
	// Rectangle N X Y SX SY R G B W H
	// Circle N X Y SX SY R G B R
	std::vector<Object<sf::CircleShape>> circles;
	std::vector<Object<sf::RectangleShape>> rectangles;

	std::string name, type;
	int Wwidth, Wheight, R, G, B, S;
	float X, Y, SX, SY, W, H, Rad;
	sf::Color fillColor;
	size_t characterSize;
	std::fstream fin("config.txt");	

	sf::Font myFont;

	while(fin >> type)
	{
		if(type == "window")
		{
		
			fin >> Wwidth >> Wheight;
		} else if (type == "Font")
		{

			fin >> name >> S >> R >> G >> B;
			if(!myFont.loadFromFile("fonts/Arialn.ttf"))
			{
				std::cerr << "Could not load font!";
				exit(-1);
			}
			fillColor = sf::Color(R,G,B);
			characterSize = S;
		} else if (type == "Circle")
		{
			fin >> name >> X >> Y >> SX >> SY >> R >> G >> B >> Rad;
            sf::CircleShape temp;
			temp.setRadius(Rad);
			temp.setFillColor(sf::Color(R,G,B));
			temp.setPosition(X,Y);

            sf::Text Ttemp(name,myFont,characterSize);
            Ttemp.setFillColor(fillColor);
            Ttemp.setPosition(
                    ((2 * X) + Rad * 2)/2 - (Ttemp.getGlobalBounds().width)/2,
                    ((2 * Y) + Rad * 2)/2 - characterSize/2
            );
            circles.push_back(Object<sf::CircleShape> (Ttemp, temp, sf::Vector2f(SX, SY)));
		} else if (type == "Rectangle")
		{
			fin >> name >> X >> Y >> SX >> SY >> R >> G >> B >> W >> H;
            sf::RectangleShape temp({W,H});
            temp.setPosition(X,Y);
            temp.setFillColor(sf::Color(R,G,B));

            sf::Text Ttemp(name,myFont,characterSize);
            Ttemp.setFillColor(fillColor);
            Ttemp.setPosition(
                    ((2 * X) + W)/2 - (Ttemp.getGlobalBounds().width)/2,
                    ((2 * Y) + H)/2 - characterSize/2
                    );
            rectangles.push_back(Object<sf::RectangleShape> (Ttemp, temp, sf::Vector2f(SX,SY)));
			//make object, add to vector
		} else 
		{
			std::cerr << "invalid file!\n\n";
			exit(-1);
		}
	}

	sf::RenderWindow window(sf::VideoMode(Wwidth, Wheight), "SFML works!");
	
	while (window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
			if(event.type == sf::Event::KeyPressed)
			{
				std::cout << "Key pressed with code = " << event.key.code << "/n";
			}
		}



		for(Object<sf::CircleShape> & obj: circles)
		{

			//logic for reversing direction goes here
            if(obj.shape.getGlobalBounds().left <= 0.0)
            {
                obj.setSpeed({obj.getSpeed().x * (-2.0f),obj.getSpeed().y});
            }
            if(obj.shape.getGlobalBounds().top <= 0.0)
            {
                obj.setSpeed({obj.getSpeed().x,obj.getSpeed().y * (-2.0f)});
            }
            if(obj.shape.getGlobalBounds().left + obj.shape.getGlobalBounds().width >= window.getSize().x)
            {
                obj.setSpeed({obj.getSpeed().x * (-2.0f),obj.getSpeed().y});
            }
            if(obj.shape.getGlobalBounds().top + obj.shape.getGlobalBounds().height >= window.getSize().y)
            {
                obj.setSpeed({obj.getSpeed().x,obj.getSpeed().y * (-2.0f)});
            }
			obj.shape.setPosition(obj.shape.getPosition() + obj.getSpeed());
			obj.name.setPosition(obj.name.getPosition() + obj.getSpeed());
		}
        for(Object<sf::RectangleShape> & obj: rectangles)
        {

            //logic for reversing direction goes here
            if(obj.shape.getGlobalBounds().left <= 0.0)
            {
                obj.setSpeed({obj.getSpeed().x * (-1.0f),obj.getSpeed().y});
            }
            if(obj.shape.getGlobalBounds().top <= 0.0)
            {
                obj.setSpeed({obj.getSpeed().x,obj.getSpeed().y * (-1.0f)});
            }
            if(obj.shape.getGlobalBounds().left + obj.shape.getGlobalBounds().width >= window.getSize().x)
            {
                obj.setSpeed({obj.getSpeed().x * (-1.0f),obj.getSpeed().y});
            }
            if(obj.shape.getGlobalBounds().top + obj.shape.getGlobalBounds().height >= window.getSize().y)
            {
                obj.setSpeed({obj.getSpeed().x,obj.getSpeed().y * (-1.0f)});
            }
            obj.shape.setPosition(obj.shape.getPosition() + obj.getSpeed());
			obj.name.setPosition(obj.name.getPosition() + obj.getSpeed());
        }
        window.clear();
        for (Object<sf::CircleShape> & obj: circles) {
            window.draw(obj.shape);
            window.draw(obj.name);
        }
        for (Object<sf::RectangleShape> & obj: rectangles) {
            window.draw(obj.shape);
            window.draw(obj.name);
        }
		window.display();
	}

	return 0;
}

