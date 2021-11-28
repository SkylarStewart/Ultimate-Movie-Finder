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