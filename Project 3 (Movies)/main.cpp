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

	//tests to build edges (will take between 7-8 minutes to run :( not optimal)
	//vector<Movie>* testGenreEdges = g.graph.at(200).genreEdges;
	//vector<Movie>* testYearEdges = g.graph.at(200).yearEdges;
	vector<Movie*> edgeList = g.graph.at(1000).edges;

	cout << "test movie name: " << g.graph.at(1000).getTitle() << endl;
	cout << "printing edges with year and genre: " << endl;
	for (int i = 0; i < g.graph.at(1000).edges.size(); i++) {
		cout << "Name: " << g.graph.at(1000).edges.at(i)->getTitle() << endl;
		cout << "Genre: " << g.graph.at(1000).edges.at(i)->getGenres() << endl;
		cout << "Year: " << g.graph.at(1000).edges.at(i)->getYear() << endl;
	}
	cout << endl << "total edges in the graph: " << g.edges << endl;
	g.buildEdgeList();
	cout << "total edge list length: " << g.edgeListLength << endl;

}