#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>

int main(int argc, char * argv[])
{
	// window W H
	// Font F S R G B
	// Rectangle N X Y SX SY R G B W H
	// Circle N X Y SX SY R G B R
    float Wwidth = 600.0, Wheight = 600.0;

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

        window.clear();

		window.display();
	}

	return 0;
}

