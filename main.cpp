#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<string>
#include<iostream>
#include<vector>
#include<time.h>
#include"server.h"
#include"client.h"

using namespace std;

int main()
{
	int temp = 50;
	int licznik = 0;

	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	char connectionType;

	
	cout << "(s) for server, (c) for client:";
	cin >> connectionType;

	if (connectionType == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
	}
	else
		socket.connect(ip, 2000);

	sf::RectangleShape rect1, rect2;

	rect1.setSize(sf::Vector2f(20, 20));
	rect2.setSize(sf::Vector2f(20, 20));

	rect1.setFillColor(sf::Color::Red);
	rect2.setFillColor(sf::Color::Blue);

	sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Packets");
	sf::Vector2f prevPosition, p2Position;

	socket.setBlocking(false);

	bool update = false;

	while (Window.isOpen())
	{
		sf::Event Event;
		while (Window.pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed || Event.key.code == sf::Keyboard::Escape)
				Window.close();
			else if (Event.type == sf::Event::GainedFocus)
				update = true;
			else if (Event.type == sf::Event::LostFocus)
				update = false;

		}

		prevPosition = rect1.getPosition();
		
		
		if (update)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				rect1.move(0.5f, 0.0f);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				rect1.move(-0.5f, 0.0f);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				rect1.move(0.0f, -0.5f);
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				rect1.move(0.0f, 0.5f);
		}
		/*rect1.move(0.2f, 0.0f);
		if (prevPosition.x > 800.f) {
			rect1.setPosition(0, temp);
			temp = temp + 50;
			if (temp > 400)
				temp = 0;
		}//*/
		

		sf::Packet packet;
		if (prevPosition != rect2.getPosition())
		{
			packet << rect1.getPosition().x << rect1.getPosition().y;
			socket.send(packet);
		}


		socket.receive(packet);
		
		
		if ( packet>> p2Position.x >> p2Position.y)//packet
		{
		
				rect2.setPosition(p2Position);
				
		}

		Window.draw(rect1);
		Window.draw(rect2);

		Window.display();
		Window.clear();
	}
		system("pause");

		return 0;


}