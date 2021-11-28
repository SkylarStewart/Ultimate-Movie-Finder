#pragma once
#include<string>
using namespace std;
class Movie
{
	string title;
	string genre;
	int year;

public:
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
