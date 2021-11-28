#pragma once
#include<string>
using namespace std;
class Movie
{
	string title;
	string genre;
	int year;

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

	//insert graphs here
};

void printhi() {
	cout << "hi" << endl;
}
