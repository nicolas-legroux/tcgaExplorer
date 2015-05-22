#include <iostream>
#include <vector>
#include <string>

#include "utilities.hpp"

using namespace std;

void printAdvancement(unsigned int currentCount, unsigned int totalCount){
	cout << (100*currentCount)/(totalCount) << "% \r" << flush;
}

vector<string> split(const string &s, const vector<char> &delimiters){
	vector<string> strs;
	string currentString;

	for(const char &c : s){
		if(find(delimiters.cbegin(), delimiters.cend(), c) == delimiters.cend()){
			currentString.push_back(c);
		}
		else{
			strs.push_back(currentString);
			currentString.erase();
		}
	}

	strs.push_back(currentString);

	return strs;
}

int numberOfPairs(int n){
	return n*(n-1)/2;
}

/*
 *
 * DISTANCE MEASURES
 *
 */

double euclideanDistance(const std::vector<double> &a,
		const std::vector<double> &b) {
	double dist = 0.0;
	for_each_two_ranges(a.cbegin(), a.cend(), b.cbegin(),
			[&dist](double x, double y) {
				dist += (x-y)*(x-y);
			});
	return sqrt(dist);
}

double manhattanDistance(const std::vector<double> &a, const std::vector<double> &b) {
	double dist = 0.0;
	for_each_two_ranges(a.cbegin(), a.cend(), b.cbegin(),
			[&dist](double x, double y) {
				dist += abs(x-y);
			});
	return dist;
}
