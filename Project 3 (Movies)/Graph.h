#pragma once
#include "Movie.h"
#include <vector>
#include <set>
#include <map>
struct Graph
{
	set<int> movieYears;
	set<string> movieGenres;

	map<int, int> yearMapper;
	map<string, int> genreMapper;

	vector<vector<Movie>> sameYears;
	vector<vector<Movie>> sameGenres;

	void insert(Movie movie);
	void insert(string genre);
	void buildEdges();

	//this vector is very important, it stores the graph. it is a vector of movies, and each movie has a container of edges.
	vector<Movie> graph;
};

void Graph::insert(Movie movie)
{
	vector<Movie> newVec;
	movieYears.insert(movie.getYear());
	if (yearMapper.find(movie.getYear()) == yearMapper.end())
	{
		yearMapper[movie.getYear()] = sameYears.size();
		sameYears.push_back(newVec);
	}
	sameYears[yearMapper[movie.getYear()]].push_back(movie);

	vector<Movie> newVec2;
	movieGenres.insert(movie.getGenres());
	if (genreMapper.find(movie.getGenres()) == genreMapper.end())
	{
		genreMapper[movie.getGenres()] = sameGenres.size();
		sameGenres.push_back(newVec2);
	}
	sameGenres[genreMapper[movie.getGenres()]].push_back(movie);

}

//builds the graph using sameYears and sameGenres.
//can only be run after the graph is built in the parsefiles.h
void Graph::buildEdges() {
	for (int i = 0; i < graph.size(); i++) {
		cout << "current number: " << i << endl;
		int currentYear = graph.at(i).getYear();
		string currentGenre = graph.at(i).getGenres();

		//builds genre edges
		for (int j = 0; j < sameGenres.size(); j++) {
			if (sameGenres.at(j).at(0).getGenres() == currentGenre) {
				graph.at(i).genreEdges = &sameGenres.at(j);
			}
		}

		//builds year edges
		for (int j = 0; j < sameYears.size(); j++) {
			if (sameYears.at(j).at(0).getYear() == currentYear) {
				graph.at(i).yearEdges = &sameYears.at(j);
			}
		}
	}
}

