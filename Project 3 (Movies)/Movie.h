#pragma once
#include<string>
#include<vector>
using namespace std;
class Movie
{
	string title;
	string genre;
	int year;

public:
	//vector<Movie>* yearEdges;
	//vector<Movie>* genreEdges;
	vector<Movie*> edges; //new version for immediate testing, holds the edges of each movie
	Movie() {
		title = "";
		genre = "";
		year = 0;
	}
	Movie(string theTitle, string theGenre, int theYear) {
		title = theTitle;
		genre = theGenre;
		year = theYear;
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

	//insert graphs here
};

void printhi() {
	cout << "hi" << endl;
}
