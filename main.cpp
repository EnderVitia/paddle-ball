#include <SFML/Graphics.hpp>
#include <iostream>

class Ball{
	private:
		sf::CircleShape body;
		int pos[2] = {100, 100};
		sf::RenderWindow *window;
	
	public:
		Ball(sf::RenderWindow *w){
			window = w;
			body.setFillColor(sf::Color::Red);
			body.setRadius(7);
		}

		void move(){
			body.setPosition(pos[0], pos[1]);
			window->draw(body);
		}

};

class Paddle{
	private:
		sf::RectangleShape body;
		int pos[2] = {0, 150};
		short direction = 1;
		sf::RenderWindow* window;


	public:
		Paddle(sf::RenderWindow* w){
			body.setFillColor(sf::Color::Blue);
			body.setSize(sf::Vector2f(50, 15));
			window = w;

		}
		void setDirection(short direction){
			this->direction = direction;
		}
		void move(){
			std::cout << window->getSize().x << " "<< pos[0] << std::endl;
			if(pos[0] >= 0 && pos[0] + 50 <= window->getSize().x){
				pos[0] += direction;
			}
			else{
				if(pos[0] < 0){
					pos[0] = 0;
				}
				else if(pos[0] + 50 > window->getSize().x){
					pos[0] = window->getSize().x - 50;
				}
			}
			body.setPosition(pos[0], pos[1]);
			window->draw(body);
		}
};

int main(){
	sf::RenderWindow window(sf::VideoMode(200, 200), "It works"), *window_ptr;
	window_ptr = &window;
	Paddle paddle(window_ptr);
	Ball ball(window_ptr);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);


	while(window.isOpen()){
		sf::Event e;
		while (window.pollEvent(e))
		{
			if(e.type == sf::Event::Closed){
				window.close();
			}
			if((e.type == sf::Event::KeyPressed)&&(e.key.code == sf::Keyboard::Left)){
				paddle.setDirection(-1);
			}
			if((e.type == sf::Event::KeyPressed)&&(e.key.code == sf::Keyboard::Right)){
				paddle.setDirection(1);
			}
		}
		window.clear();
		paddle.move();
		ball.move();
		window.display();
		
	}
	return 0;
}



