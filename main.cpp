#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <string>


class Paddle{
	private:
		sf::RectangleShape body;
		int pos[2] = {0, 350};
		short direction = 2;
		sf::RenderWindow* window;



	public:
		Paddle(sf::RenderWindow* w){
			body.setFillColor(sf::Color::Blue);
			body.setSize(sf::Vector2f(120, 20));
			window = w;

		}
		void setDirection(short d){
			direction = d;
		}
		int *getPosition() {
			int paddle_pos[4] = { pos[0], pos[0] + 120, pos[1], pos[1] - 20 };
			return paddle_pos;
		}
		void move(){
			if(pos[0] >= 0 && pos[0] + 120 <= window->getSize().x){
				pos[0] += direction;
			}
			else{
				if(pos[0] < 0){
					pos[0] = 0;
				}
				else if(pos[0] + 120 > window->getSize().x){
					pos[0] = window->getSize().x - 120;
				}
			}
			body.setPosition(pos[0], pos[1]);
			window->draw(body);
		}
};

class Ball {
private:
	sf::CircleShape body;
	int pos[2] = { 100, 50 };
	int direction[2] = { 1, 2 };
	int randX;
	sf::RenderWindow* window;
	Paddle* paddle;
	int count = 0;

	void changeDirection() {
		if (isHitPaddle()) {
			direction[1] = -(2 + count/10);
			direction[0] = direction[0] / abs(direction[0]) * (abs(randX) + count / 10);
			pos[1] = *(paddle->getPosition() + 3);

		}
		if (isHitWalls() == 1) {
			direction[0] = -direction[0];
		}
		if (isHitWalls() == 2) {
			direction[1] = -direction[1];
		}
		if (isHitWalls() == 3) {
			direction[0] = -direction[0];
		}
	}

	bool isHitPaddle() {
		int* paddle_pos = paddle->getPosition();
		if (pos[0] >= *paddle_pos && pos[0] <= *(paddle_pos + 1)) {
			if (pos[1] >= *(paddle_pos + 3) && pos[1] <= *(paddle_pos + 2)) {
				count += 1;
				return true;
			};
			return false;
		}
		return false;
	}
	short isHitWalls() {
		if (pos[1] < 0) {
			return 2;
		}
		if (pos[0] <= 0) {
			return 1;
		}
		if (pos[0] + 14 >= window->getSize().x) {
			return 3;
		}
		if (pos[1] + 14 >= window->getSize().y) {
			return 0;
		}
	}


public:
	Ball(sf::RenderWindow* w, Paddle* p) {
		srand(time(0));
		paddle = p;
		window = w;
		body.setFillColor(sf::Color::Red);
		body.setRadius(9);
		randX = rand() % 6 - 3;
		if (randX == 0) randX = 1;
		direction[0] = randX;
	}

	bool isGameOver() {
		if (isHitWalls() == 0) {
			return true;
		}
		return false;
	}

	std::string getCount() {
		return std::to_string(count);
	}

	void move() {
		changeDirection();
		pos[0] += direction[0];
		pos[1] += direction[1];
		body.setPosition(pos[0], pos[1]);
		window->draw(body);
	}

};

int main(){
	sf::RenderWindow window(sf::VideoMode(500, 400), "It works"), *window_ptr;
	window_ptr = &window;
	window.setPosition(sf::Vector2i(-10,0));
	Paddle paddle(window_ptr), *paddle_ptr;
	paddle_ptr = &paddle;
	Ball ball(window_ptr, paddle_ptr);
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
				paddle.setDirection(-2);
			}
			if((e.type == sf::Event::KeyPressed)&&(e.key.code == sf::Keyboard::Right)){
				paddle.setDirection(2);
			}
		}
		
		if (!ball.isGameOver()) {
			window.clear();
			paddle.move();
			ball.move();
			window.display();
		}
		else {
			sf::Font font;
			font.loadFromFile("arial.ttf");
			sf::Text gameOver("Game Over", font), count(ball.getCount(), font);
			gameOver.setCharacterSize(30);
			gameOver.setStyle(sf::Text::Regular);
			gameOver.setFillColor(sf::Color::White);
			gameOver.setPosition(170, 160);
			count.setPosition(170, 190);
			window.draw(gameOver);
			window.draw(count);
			window.display();

		}
		
	}
	return 0;
}



