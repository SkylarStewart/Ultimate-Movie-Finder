#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include "Graph.h"
using namespace std;

void parseMovies(Graph& g)
{
    ifstream inFile("newMovieDatabase.csv");

    if (inFile.is_open())
    {
        string line, genres, releaseYear, movieTitle, temp;
        getline(inFile, line);

        while (getline(inFile, line)) {

            istringstream stream(line);

            getline(stream, temp, ',');
            if (temp == "[]")
                continue;
            genres += temp;
            while (temp[temp.size() - 1] != '\"')
            {
                getline(stream, temp, ',');
                genres += temp;
            }

            string temp = genres;
            genres = "";
            string delimiter = ": '";
            while (temp.size() > 0)
            {
                temp.erase(0, temp.find(delimiter) + 3);
                string token = temp.substr(0, temp.find("'}"));
                temp.erase(0, temp.find("'}") + 3);
                genres += token;
            }

            g.movieGenres.insert(genres);

            getline(stream, releaseYear, ',');

            if (releaseYear.size() < 4)
                continue;
            else
            {
                releaseYear = releaseYear.substr(releaseYear.size() - 4, 4);
            }

            getline(stream, movieTitle, ',');

            Movie newMovie = Movie(movieTitle, genres, stoi(releaseYear));
            g.graph.push_back(newMovie);
            g.insert(newMovie);

        }
    }

    cout << "potato" << endl;
}

