#include <string>
#include <iostream>
#include "feelingsgenerator.h"
#include "Movie.h"
#include "parseFiles.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "TextBox.h"
#include "Button.h"
using namespace std;

//main is used to test functions, you can clear it out whenever you want.
int main() {
	/*cout << "ran!" << endl;
	cout << getBasefeeling("joyous");
	Graph g;
	parseMovies(g);
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < g.sameGenres[i].size(); j++)
		{
			cout << g.sameGenres[i][j].getTitle() << g.sameGenres[i][j].getGenres() << endl;
		}
	}
	g.buildEdges();

	//tests to build edges (will take between 7-8 minutes to run :( not optimal)
	//vector<Movie>* testGenreEdges = g.graph.at(200).genreEdges;
	//vector<Movie>* testYearEdges = g.graph.at(200).yearEdges;
	vector<Movie*> edgeList = g.graph.at(1000).edges;

	g.buildEdgeList();
	g.buildIndexMap();
	cout << "test movie name: " << g.graph.at(1000).getTitle() << endl;
	cout << "printing edges with year and genre: " << endl;
	for (int i = 0; i < g.graph.at(1000).edges.size(); i++) {
		cout << "Name: " << g.graph.at(1000).edges.at(i)->getTitle() << endl;
		cout << "Genre: " << g.graph.at(1000).edges.at(i)->getGenres() << endl;
		cout << "Year: " << g.graph.at(1000).edges.at(i)->getYear() << endl;
	}
	cout << endl << "total edges in the graph: " << g.edges << endl;
	cout << "total edge list length: " << g.edgeListLength << endl;
	vector<Movie> testVector = g.DFSAdjList("Three Godfathers", false);
	for (int i = 0; i < testVector.size(); i++) {
		cout << testVector.at(i).getTitle() << endl;
		cout << testVector.at(i).getGenres() << endl;
	}
	*/
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Ultimate Movie Finder // The Movie Finders");

	//Sets background
	sf::Sprite background;
	background.setTexture(TextureManager::GetTexture("forest"));

	vector<Button> buttons;
	//BFS Button
	Button bfs = Button(150, 150, "PressedBFS", "UnpressedBFS");
	buttons.push_back(bfs);
	Button dfs = Button(150, 250, "PressedDFS", "UnpressedDFS");
	buttons.push_back(dfs);

	sf::Font font;
	if (!font.loadFromFile("GothicA1-Black.ttf"))
	{
		cout << "font not loading" << endl;
	}

	//Textbox
	TextBox textBox = TextBox(1920 / 2 - 200, 200, 400, 80, "Enter Feeling Here", font);

	//Movie Boxes
	vector<TextBox> movieBoxes;
	for (int i = 0; i < 5; i++)
	{
		movieBoxes.push_back(TextBox(1920 / 2 - 200, 350 + 80 * i, 400, 80, "Movie Title", font));
	}

	sf::Color textColor = sf::Color(0, 253, 171);
	sf::String input;
	sf::Text text;
	text.setFont(font);
	text.setString("Hello World");
	text.setCharacterSize(24);
	text.setFillColor(textColor);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			else if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode < 128 && event.text.unicode != 8)
				{
					input += event.text.unicode;
					text.setString(input);
				}
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Backspace && input.getSize() > 0)
				{
					input = input.substring(0, input.getSize() - 1);
					text.setString(input);
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					for (int i = 0; i < buttons.size(); i++)
					{
						auto bounds = buttons[i].getGlobalBounds();
						if (buttons[i].checkPressed() == false && bounds.contains(mousePos.x, mousePos.y))
						{
							buttons[i].setPressed();
							for (int j = 0; j < buttons.size(); j++)
								if (i != j)
									buttons[j].unPress();
						}
					}
				}
			}
		}

		window.clear();
		window.draw(background);

		for (int i = 0; i < 5; i++)
			movieBoxes[i].Draw(window);

		textBox.Draw(window);

		window.draw(text);

		for (int i = 0; i < buttons.size(); i++)
			buttons[i].Draw(window);
		window.display();

	}
}
