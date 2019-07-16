#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Interpritator.h"
#include <vector>

//stoi(string_type) - из string в int
//to_string(int_type) - из int в string

using namespace sf;
int displayWidth = 320, diaplayHeight = 474, cellSize = 77;//320
std::string str;
const char* StrForIntr;
double otvet;
sf::String Calc[6] = {
	"    ",
	"C<()",
	"789-",
	"456+",
	"123*",
	",0=/",
};

std::vector<char> operators = { '+', '*', '-', '/', '(', ',', ')' };

void calculator(const char* input) {
	try {
		Parser p(input);
		auto result = eval(p.parse());
		otvet = result;
		std::cout << "Result is: " << result << "\n";

	}
	catch (std::exception& e) {
		std::cout << input << ": exeption: " << e.what() << "\n";
		str = "Syntax Error";
	}
	
	
};

int main() {
	setlocale(LC_ALL, "ru");
	RenderWindow window(sf::VideoMode(displayWidth, diaplayHeight), "Calculator in SFML");

	////////////////Textures//////////////////
	Texture t_background;
			
	//////////////Loading///////////////////
	t_background.loadFromFile("images/TileMap.jpg");

	/////////////Sprites///////////////////
	Sprite background(t_background);

	Font font;
	font.loadFromFile("fonts/Verdana.ttf");
	Text text("", font, 36);
	text.setFillColor(Color(77, 73, 70));
	text.setPosition(0, 19.5);
	

	while (window.isOpen()) {
	
		///////////////////////Mouse//////////////////
		Vector2i positionMouse = Mouse::getPosition(window);
		int mouseX = positionMouse.x / cellSize;
		int mouseY = positionMouse.y / cellSize;
		
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::TextEntered)
				if(event.key.code >= 48 && event.key.code <= 57)
						str += event.key.code;

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::BackSpace)
					str = str.substr(0, str.length() - 1);

				if (event.key.code == Keyboard::Add)
					str+='+';

				if (event.key.code == Keyboard::Multiply)
					str += '*';

				if (event.key.code == Keyboard::Subtract)
					str += '-';

				if (event.key.code == Keyboard::Divide)
					str += '/';

				if (event.key.code == Keyboard::Comma)
					str += ',';

				if (event.key.code == Keyboard::Enter) {
					for (int i = 0; i < operators.size(); i++)
						if (str[str.length() - 1] == operators[i]) {
							str = "Syntax Error";
							break;
						}
						else {
							StrForIntr = str.c_str();
							calculator(StrForIntr);
							str = std::to_string(otvet);
							for (int i = str.length() - 1; i > -1; i--)
								if (str[i] == '0' || str[i] == ',')
									str = str.substr(0, i);
								else
									break;
						}
				}
					

			}

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) {
						for(int i = 2; i < 5; i++)//numbers
							for (int j = 0; j < 3; j++) {
								if (Calc[mouseY][mouseX] == Calc[i][j]) {
									int otvet = static_cast<int>(Calc[mouseY][mouseX]);
									str += Calc[mouseY][mouseX];
								}
							}

						for (int i = 0; i < operators.size(); i++)
							if (Calc[mouseY][mouseX] == operators[i])
								str += operators[i];

						if (Calc[mouseY][mouseX] == 'C')
							str = "";

						if (Calc[mouseY][mouseX] == '0')
							str += '0';

						if (Calc[mouseY][mouseX] == '<')
							str = str.substr(0, str.length() - 1);

						if (Calc[mouseY][mouseX] == '=') {
							for(int i = 0; i < operators.size(); i++)
								if (str[str.length() - 1] == operators[i]) {
									str = "Syntax Error";
									break;
								}
							else {
								StrForIntr = str.c_str();
								calculator(StrForIntr);
								str = std::to_string(otvet);
								for (int i = str.length() - 1; i > -1; i--)
									if (str[i] == '0' || str[i] == ',')
										str = str.substr(0, i);
									else
										break;
								
							}

						}

				}
			
		}

		


		window.clear(Color :: White);
		for(int i = 0; i < 6; i++)
			for (int j = 0; j < 4; j++) {
				background.setTextureRect(IntRect(j*cellSize, i*cellSize, cellSize + 12, cellSize + 12));
				background.setPosition(j*cellSize, i*cellSize);
				window.draw(background);
			}

		if (str.length() >= 14)
			str = str.substr(0, 14);
		
		text.setString(str);
		window.draw(text);
		window.display();
	}

	return 0;
}
