#include <string>
#include <iostream>
#include "feelingsgenerator.h"
#include "Movie.h"
#include "parseFiles.h"

using namespace std;

//main is used to test functions, you can clear it out whenever you want.
int main() {
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

	//test to build edges
	vector<Movie>* testGenreEdges = g.graph.at(200).genreEdges;
	vector<Movie>* testYearEdges = g.graph.at(200).yearEdges;

	cout << "test movie name: " << g.graph.at(200).getTitle() << endl;
	cout << "printing year edges:" << endl;

	for (int i = 0; i < testYearEdges->size(); i++) {
		cout << testYearEdges->at(i).getTitle();
		cout << " " << testYearEdges->at(i).getYear();
	}

	cout << "printing genre edges" << endl;
	for (int i = 0; i < testGenreEdges->size(); i++) {
		cout << testGenreEdges->at(i).getTitle();
		cout << " " << testGenreEdges->at(i).getGenres();
	}

	int genreedges = testGenreEdges->size();
	int yearedges = testYearEdges->size();
	int combined = genreedges + yearedges;
	cout << endl << "total edges in this node: " << combined << endl;

	int totaledges = 0;
	for (int i = 0; i < g.graph.size(); i++) {
		testGenreEdges = g.graph.at(i).genreEdges;
		testYearEdges = g.graph.at(i).yearEdges;
		genreedges = testGenreEdges->size();
		yearedges = testYearEdges->size();
		totaledges += genreedges;
		totaledges += yearedges;

	}

	cout << endl << "total edges in the graph: " << totaledges << endl;

}