#include <iostream>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
void ReadInputAsSet(set<string> &unique, string fileName);
void ReadInputAsVector(vector<string> &tokens, string fileName);
void OutputSetContents(const set<string> &unique, string fileName);
void OutputVectorContents(const vector<string> &tokens, string fileName);
void CreateMapFromVector(const vector<string> &tokens, map<string, string> &wordMap);
void OutputMapContents(const map<string, string> &wordMap, string fileName);
int main(int argc, char* argv[]) {
	string fileName = argv[1];

	vector<string> tokens;
    set<string> unique;
	ReadInputAsSet(unique, fileName);
	ReadInputAsVector(tokens, fileName);

	OutputSetContents(unique, fileName);
	OutputVectorContents(tokens, fileName);

	map<string, string> wordMap;
	CreateMapFromVector(tokens, wordMap);
	OutputMapContents(wordMap, fileName);
	return 0;
}

void ReadInputAsSet(set<string> &unique, string fileName) {
	string next_line;
	
    ifstream in(fileName);
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for(auto &c : token) {     
                if (isalpha(c)) {
                    nopunct +=c;       
                }
            }
		    unique.insert(nopunct);
	    }
    }
	in.close();
}

void ReadInputAsVector(vector<string> &tokens, string fileName) {
	string next_line;
	
    ifstream in(fileName);
    while (getline(in, next_line)) {
        istringstream iss(next_line);
        string token;
        while (iss >> token) {
            string nopunct = "";
            for(auto &c : token) {      
                if (isalpha(c)) {
                    nopunct +=c;       
                }
            }
	        tokens.push_back(nopunct);
	    }
    }
	in.close();
}

void OutputSetContents(const set<string> &unique, string fileName) {
	ofstream outputFile(fileName + "_set.txt");

    for (set<string>::iterator it = unique.begin(); it != unique.end(); it++) {
		outputFile << *it << "\n";
	}

	outputFile.close();
}

void OutputVectorContents(const vector<string> &tokens, string fileName) {
	ofstream outputFile(fileName + "_vector.txt");
    for (string const& word : tokens) {
		outputFile << word << "\n";
	}

	outputFile.close();
}

void CreateMapFromVector(const vector<string> &tokens, map<string, string> &wordMap) {
	wordMap[""] = tokens.at(0);
    for (int i = 1; i < tokens.size() - 1; i++) {
		wordMap[tokens.at(i)] = tokens.at(i+1);
	}
}

void OutputMapContents(const map<string, string> &wordMap, string fileName) {
	// Iterate through the map or cycle through the keys
	for(map<string, string>::iterator it = wordMap.begin(); )
}