#pragma once
#include<string>
#include<vector>
using namespace std;
class Movie
{
	string title;
	string genre;
	int year;
	string ID;
	int index;
	int edgeCount = 0;

public:
	//vector<Movie>* yearEdges;
	//vector<Movie>* genreEdges;
	vector<Movie*> edges; //new version for immediate testing, holds the edges of each movie
	Movie() {
		title = "";
		genre = "";
		year = 0;
		ID = "";
	}
	Movie(string theTitle, string theGenre, int theYear) {
		title = theTitle;
		genre = theGenre;
		year = theYear;
		ID += title;
		ID += genre;
		ID += to_string(theYear);
	}

	int getYear()
	{
		return year;
	}
	string getGenres()
	{
		return genre;
	}

	string getTitle()
	{
		return title;
	}

	string getID()
	{
		return ID;
	}

	void setIndex(int index) {
		this->index = index;
	}

	int getIndex() {
		return this->index;
	}

	void addEdge() {
		edgeCount++;
	}

	int returnEdgeCount() {
		return this->edgeCount;
	}



	//insert graphs here
};

void printhi() {
	cout << "hi" << endl;
}
