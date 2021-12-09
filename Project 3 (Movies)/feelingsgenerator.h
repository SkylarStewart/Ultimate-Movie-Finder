#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//function for getting the "base" (one of 5) feelings from an extended list of adjectives
string getBasefeeling(string input) {

	//initialization
	string lowerInput = input;
	for (int i = 0; i < lowerInput.size(); i++)
	{
		lowerInput[i] = tolower(lowerInput[i]);
	}
	string returnVal = "";
	vector<string> first;
	vector<string> second;
	std::ifstream infile("emotions.txt");
	std::string str;

	//goes through the list, gets inputs
	while (std::getline(infile, str)) {

		string s = str;
		string delimit = ":";
		string part1 = s.substr(0, s.find(delimit));
		string part2 = s.substr(s.find(delimit)+1, s.size()-1);
		first.push_back(part1);
		second.push_back(part2);
	}

	//finds a matching word (if it exists)
	for (int i = 0; i < first.size(); i++) {
		if (first.at(i) == lowerInput) {
			returnVal = second.at(i);
		}
	}

	//returns the return value
	return returnVal;

}