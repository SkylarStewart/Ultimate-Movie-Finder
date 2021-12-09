#pragma once
#include "Movie.h"
#include <stack>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <random>
#include <time.h>

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
	void buildEdgeList();
	void buildIndexMap();

	//the various different search algorithms for the various different 
	vector<Movie> DFSAdjList(string input, bool multiOrSingle);
	vector<Movie> BFSAdjList(string input, bool multiOrSingle);
	vector<Movie> DFSEdgeList(string input, bool multiOrSingle);
	vector<Movie> BFSEdgeList(string input, bool multiOrSingle);


	int edges = 0;
	int edgeListLength = 0;

	//this vector is very important, it stores the graph. it is a vector of movies, and each movie has a container of edges.
	vector<Movie> graph;
	vector<pair<Movie*, Movie*>> edgeList;
	map<string, int> indexMap;
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
	srand(time(NULL));
	for (int i = 0; i < graph.size(); i++) {
		//cout << "current number: " << i << endl;
		//cout << "current movie: " << graph.at(i).getTitle() << endl;
		int currentYear = graph.at(i).getYear();
		string currentGenre = graph.at(i).getGenres();
		string currentTitle = graph.at(i).getTitle();
		//builds genre edges
		for (int j = 0; j < sameGenres.size(); j++) {
			if (sameGenres.at(j).at(0).getGenres() == currentGenre) {
				int counter = 0;
				bool TorF = true;
				int max = 0;
				int totalEdges = sameGenres.at(j).size();
				if (totalEdges <= 5) {
					max = totalEdges;
				}
				else {
					max = 5;
				}
				//this code will select 5 random movies of the same genre and form an edge.
				while (true) {

					int randomInt = rand() % sameGenres.at(j).size();
					if (sameGenres.at(j).at(randomInt).getTitle() == graph.at(i).getTitle()) {
						if (max == 1) {
							break;
						}
						if (max == 2) {
							bool thesame = true;
							for (int m = 0; m < sameGenres.at(j).size(); m++) {
								if (sameGenres.at(j).at(m).getTitle() != currentTitle) {
									thesame = false;
								}
							}
							if (thesame) {
								break;
							}
						}
						continue;
					}
					else {
						graph.at(i).edges.push_back(&sameGenres.at(j).at(randomInt));
						graph.at(i).addEdge();
						edges++;
						counter++;
					}
					if (counter >= max) {
						break;
					}
				}
				//graph.at(i).genreEdges = &sameGenres.at(j);
			}
		}

		//builds year edges
		for (int j = 0; j < sameYears.size(); j++) {
			if (sameYears.at(j).at(0).getYear() == currentYear) {
				int counter = 0;
				bool TorF = true;
				int max = 0;
				int totalEdges = sameYears.at(j).size();
				if (totalEdges <= 5) {
					max = totalEdges;
				}
				else {
					max = 5;
				}

				//this code will select 5 random movies of the same genre and form an edge.
				while (true) {

					int randomInt = rand() % sameYears.at(j).size();
					if (sameYears.at(j).at(randomInt).getTitle() == graph.at(i).getTitle()) {
						if (max == 1) {
							break;
						}
						continue;
					}
					else {
						graph.at(i).edges.push_back(&sameYears.at(j).at(randomInt));
						graph.at(i).addEdge();
						edges++;
						counter++;
					}
					if (counter >= max) {
						break;
					}
				}
				//graph.at(i).yearEdges = &sameYears.at(j);
			}
		}
	}
}

//requires the built up adjacency list. iterates through the entirety of the edge list, and each pair is added to the 
//edge list data structure.
void Graph::buildEdgeList() {
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph.at(i).edges.size(); j++) {
			pair<Movie*, Movie*> newpair;
			newpair.first = &graph.at(i);
			newpair.second = graph.at(i).edges.at(j);
			edgeListLength++;
			edgeList.push_back(newpair);
		}
	}
}

//depth first search using an adjacency list. inspired by the algorithms in the lecture notes
vector<Movie> Graph::DFSAdjList(string input, bool multiOrSingle) {
	cout << "Started DFS" << endl;
	vector<Movie> returnvec;
	set<string> visited;
	stack<string> q;
	visited.insert(graph.at(0).getID());
	q.push(graph.at(0).getID());

	if (multiOrSingle) {
		while (!q.empty()) {
			string u = q.top();
			Movie m = graph.at(indexMap.find(u)->second);
			if (m.getGenres() == input) {
				returnvec.push_back(m);
			}
			q.pop();
			vector<Movie*> neighbors = m.edges;

			for (Movie* movie : neighbors) {
				if (visited.count(movie->getID()) == 0) {
					visited.insert(movie->getID());
					q.push(movie->getID());
				}
			}
		}
	}
	if (!multiOrSingle) {
		while (!q.empty()) {
			string u = q.top();
			Movie m = graph.at(indexMap.find(u)->second);
			if (m.getTitle() == input) {
				returnvec.push_back(m);
				return returnvec;
			}
			q.pop();
			vector<Movie*> neighbors = m.edges;

			for (Movie* movie : neighbors) {
				if (visited.count(movie->getID()) == 0) {
					visited.insert(movie->getID());
					q.push(movie->getID());
				}
			}
		}
	}
	return returnvec;
}

//depth first search using an adjacency list. inspired by the algorithms in the lecture notes

vector<Movie> Graph::BFSAdjList(string input, bool multiOrSingle) {
	cout << "Started BFS" << endl;
	vector<Movie> returnvec;
	set<string> visited;
	queue<string> q;
	visited.insert(graph.at(0).getID());
	q.push(graph.at(0).getID());

	if (multiOrSingle) {
		while (!q.empty()) {
			string u = q.front();
			Movie m = graph.at(indexMap.find(u)->second);
			if (m.getGenres() == input) {
				returnvec.push_back(m);
			}
			q.pop();
			vector<Movie*> neighbors = m.edges;

			for (Movie* movie : neighbors) {
				if (visited.count(movie->getID()) == 0) {
					visited.insert(movie->getID());
					q.push(movie->getID());
				}
			}
		}
	}
	if (!multiOrSingle) {
		while (!q.empty()) {
			string u = q.front();
			Movie m = graph.at(indexMap.find(u)->second);
			if (m.getTitle() == input) {
				returnvec.push_back(m);
				return returnvec;
			}
			q.pop();
			vector<Movie*> neighbors = m.edges;

			for (Movie* movie : neighbors) {
				if (visited.count(movie->getID()) == 0) {
					visited.insert(movie->getID());
					q.push(movie->getID());
				}
			}
		}
	}
	return returnvec;
}

vector<Movie> Graph::DFSEdgeList(string input, bool multiOrSingle) {
	cout << "Started DFS" << endl;
	vector<Movie> returnvec;
	set<string> visited;
	stack<string> q;
	visited.insert(graph.at(0).getID());
	q.push(graph.at(0).getID());

	if (multiOrSingle) {
		while (!q.empty()) {
			string u = q.top();
			Movie m = graph.at(indexMap.find(u)->second);
			if (m.getGenres() == input) {
				returnvec.push_back(m);
			}
			q.pop();
			vector<Movie*> neighbors = m.edges;

			for (Movie* movie : neighbors) {
				if (visited.count(movie->getID()) == 0) {
					visited.insert(movie->getID());
					q.push(movie->getID());
				}
			}
		}
	}
	if (!multiOrSingle) {
		while (!q.empty()) {
			string u = q.top();
			Movie m = graph.at(indexMap.find(u)->second);
			if (m.getTitle() == input) {
				returnvec.push_back(m);
				return returnvec;
			}
			q.pop();
			vector<Movie*> neighbors = m.edges;

			for (Movie* movie : neighbors) {
				if (visited.count(movie->getID()) == 0) {
					visited.insert(movie->getID());
					q.push(movie->getID());
				}
			}
		}
	}
	return returnvec;
}

vector<Movie> Graph::BFSEdgeList(string input, bool multiOrSingle) {
	vector<Movie> returnvec;
	set<string> visited;
	queue<string> q;
	visited.insert(graph.at(0).getID());
	q.push(graph.at(0).getID());

	if (multiOrSingle) {
		while (!q.empty()) {
			string u = q.front();
			Movie m = graph.at(indexMap.find(u)->second);
			if (m.getGenres() == input) {
				returnvec.push_back(m);
			}
			q.pop();
			vector<Movie*> neighbors = m.edges;

			for (Movie* movie : neighbors) {
				if (visited.count(movie->getID()) == 0) {
					visited.insert(movie->getID());
					q.push(movie->getID());
				}
			}
		}
	}
	if (!multiOrSingle) {
		while (!q.empty()) {
			string u = q.front();
			Movie m = graph.at(indexMap.find(u)->second);
			if (m.getTitle() == input) {
				returnvec.push_back(m);
				return returnvec;
			}
			q.pop();
			vector<Movie*> neighbors = m.edges;

			for (Movie* movie : neighbors) {
				if (visited.count(movie->getID()) == 0) {
					visited.insert(movie->getID());
					q.push(movie->getID());
				}
			}
		}
	}
	return returnvec;
}

void Graph::buildIndexMap() {
	for (int i = 0; i < graph.size(); i++) {
		this->indexMap.emplace(graph.at(i).getID(), i);
	}
}


