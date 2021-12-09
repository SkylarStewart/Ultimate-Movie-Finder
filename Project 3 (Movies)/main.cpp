#include <string>
#include <iostream>
#include "feelingsgenerator.h"
#include "Movie.h"
#include "parseFiles.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "TextBox.h"
#include "Button.h"
#include <time.h>
#include <chrono>
using namespace std;

//main is used to test functions, you can clear it out whenever you want.
int main() {
	//sets random time seed
	srand(time(NULL));

	cout << "ran!" << endl;
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
	
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Ultimate Movie Finder // The Movie Finders");

	bool isinvalid = false;
	//0 == bfs
	//1 == dfs
	bool search = false;
	vector<Movie> tenMovies;
	string timeString;

	//Sets background
	sf::Sprite background;
	background.setTexture(TextureManager::GetTexture("forest"));

	vector<Button> buttons;
	//BFS Button
	Button bfs = Button(200, 200, "PressedBFS", "UnpressedBFS");
	buttons.push_back(bfs);
	Button dfs = Button(300, 200, "PressedDFS", "UnpressedDFS");
	buttons.push_back(dfs);

	sf::Font font;
	if (!font.loadFromFile("GothicA1-Black.ttf"))
	{
		cout << "font not loading" << endl;
	}


	float xPosText, yPosText;

	//Textbox
	sf::String text = "Enter Feeling Here";
	TextBox textBox = TextBox(1920 / 2 - 160, 230, 400, 50, text, font, 20);


	//Title box
	text = "The Ultimate MovieFinder";
	xPosText = 1920 / 2 - 210 + 100 / 2;
	yPosText = 100 + 60 / 4;
	TextBox titleBox = TextBox(1920 / 2 - 210, 100, 500, 60, text, font, 30);
	titleBox.setTextPos(xPosText + 5, yPosText);

	//Invalid text when emotion is invalid
	sf::Text invalid;
	invalid.setCharacterSize(15);
	invalid.setString(sf::String("Invalid emotion, try again."));
	invalid.setPosition(1920 / 2 - 163, 285);
	invalid.setFont(font);
	invalid.setFillColor(sf::Color(214, 62, 62));
	invalid.setOutlineColor(sf::Color::Black);
	invalid.setOutlineThickness(.7);

	//Time to run BFS/DFS text
	sf::Text time;
	time.setCharacterSize(15);
	time.setString(sf::String("Time to run: "));
	time.setPosition(1920 / 2 - 163, 854);
	time.setFont(font);
	time.setFillColor(sf::Color::White);
	time.setOutlineColor(sf::Color::Black);
	time.setOutlineThickness(.7);

	//Movie Boxes
	text = "Movie Title";
	vector<TextBox> movieBoxes;
	for (int i = 0; i < 10; i++)
	{
		movieBoxes.push_back(TextBox(1920 / 2 - 160, 350 + 50 * i, 400, 50, text, font, 20));
	}

	sf::String input;

	//GUI Window
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			//If textbox selected and user types, input taken
			else if (event.type == sf::Event::TextEntered && textBox.isSelected())
			{
				if (event.text.unicode < 128 && event.text.unicode != 8 && input.getSize() < 44 && event.text.unicode != 13)
				{
					input += event.text.unicode;
					textBox.updateText(input);
				}
			}
	
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					for (int i = 0; i < buttons.size(); i++)
					{
						//If you click on BFS / DFS, other button is deactivated
						auto bounds = buttons[i].getGlobalBounds();
						if (buttons[i].checkPressed() == false && bounds.contains(mousePos.x, mousePos.y))
						{
							buttons[i].setPressed();
							if (i == 0)
							{
								buttons[1].unPress();
								search = false;
							}
							else
							{
								buttons[0].unPress();
								search = true;
							}
						}
					}

					//Selects box if you click on it
					auto bounds = textBox.getGlobalBounds();
					if (bounds.contains(mousePos.x, mousePos.y) && !textBox.isSelected())
					{
						textBox.setSelect();
					}
					else if (!bounds.contains(mousePos.x, mousePos.y) && textBox.isSelected())
						textBox.unselect();

				}
			}

			//Checks emotion and generates 10 movies if valid
			else if (event.type == sf::Event::KeyPressed)
			{

				if (event.key.code == sf::Keyboard::Enter && textBox.isSelected())
				{
					string baseFeeling = getBasefeeling(input);
					if (baseFeeling == "") {

						isinvalid = true;

					}
					else {
						isinvalid = false;
						vector<Movie> moviesPreParse;
						auto begin = std::chrono::high_resolution_clock::now();
						if (search == 0) {
							if (baseFeeling == "happy") {
								moviesPreParse = g.BFSAdjList("Action", true);
							}
							if (baseFeeling == "sad") {
								moviesPreParse = g.BFSAdjList("Drama", true);
							}
							if (baseFeeling == "nervous") {
								moviesPreParse = g.BFSAdjList("Crime", true);
							}
							if (baseFeeling == "angry") {
								moviesPreParse = g.BFSAdjList("Horror", true);
							}
							if (baseFeeling == "depressed") {
								moviesPreParse = g.BFSAdjList("Romance", true);
							}
						}
						if (search == 1) {
							if (baseFeeling == "happy") {
								moviesPreParse = g.DFSAdjList("Action", true);
							}
							if (baseFeeling == "sad") {
								moviesPreParse = g.DFSAdjList("Drama", true);
							}
							if (baseFeeling == "nervous") {
								moviesPreParse = g.DFSAdjList("Crime", true);
							}
							if (baseFeeling == "angry") {
								moviesPreParse = g.DFSAdjList("Horror", true);
							}
							if (baseFeeling == "depressed") {
								moviesPreParse = g.DFSAdjList("Romance", true);
							}
						}
						//Times how long it takes to generate 10 movies using bfs/dfs
						auto end = std::chrono::high_resolution_clock::now();
						auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
						double timeDouble = elapsed.count() * 1e-6;
						timeString = to_string(timeDouble);
						cout << timeString << endl;



						tenMovies.clear();
						while (tenMovies.size() < 10) {
							int random = rand() % moviesPreParse.size();
							Movie m = moviesPreParse.at(random);
							bool included = false;

							//checks if the movie has already been added
							for (int k = 0; k < tenMovies.size(); k++) {
								if (tenMovies.at(k).getTitle() == m.getTitle()) {
									included = true;
								}
							}

							if (included == false) {
								tenMovies.push_back(m);
							}
						}
					}
				}

				//Puts generated movies into movie boxes
				for (int i = 0; i < tenMovies.size(); i++)
				{
					string title = tenMovies[i].getTitle();
					title += " (" + to_string(tenMovies[i].getYear()) + ')';
					sf::String sfTitle = title;
					movieBoxes[i].updateText(sfTitle);
				}

				//Removes character at end if backspace is pressed
				if (event.key.code == sf::Keyboard::Backspace && input.getSize() > 0
					&& textBox.isSelected())
				{
					input = input.substring(0, input.getSize() - 1);
					textBox.updateText(input);
				}

				time.setString("Time to run: " + timeString + " ms.");

			}
		}

		//Draws all sprites / text
		window.clear();
		window.draw(background);

		for (int i = 0; i < movieBoxes.size(); i++)
			movieBoxes[i].Draw(window);

		textBox.Draw(window);
		titleBox.Draw(window);

		if(isinvalid)
		window.draw(invalid);

		window.draw(time);

		for (int i = 0; i < buttons.size(); i++)
			buttons[i].Draw(window);

		window.display();

	}
}
