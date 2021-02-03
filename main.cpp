#include <iostream>
#include <set>
#include <map>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>

// comment refresh please
#define M 3
#define SIZE 140

using namespace std;
void ReadInputAsSet(set<string> &unique, string fileName);
void ReadInputAsVector(vector<string> &tokens, string fileName);
void OutputSetContents(const set<string> &unique, string fileName);
void OutputVectorContents(const vector<string> &tokens, string fileName);
void CreateMapFromVector(const vector<string> &tokens, map<string, string> &wordMap);
void OutputMapContents(const map<string, string> &wordMap, string fileName);
void PrintCyclicalSermon(const map<string, string> &wordMap);
void CreateVectorMap(map<string, vector<string>> &allFollowWords, const vector<string> &tokens);
void PrintVectorSermon(map<string, vector<string>> &allFollowWords);
void CreateContextMap(map<list<string>, vector<string>> &contextMap, const vector<string> &tokens);
void PrintContextSermon(const map<list<string>, vector<string>> &contextMap);
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

	//PrintCyclicalSermon(wordMap);

	map<string, vector<string>> allFollowWords;
	CreateVectorMap(allFollowWords, tokens);
	//PrintVectorSermon(allFollowWords);

	map<list<string>, vector<string>> contextMap;
	CreateContextMap(contextMap, tokens);
	PrintContextSermon(contextMap);
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
	ofstream setFile(fileName + "_set.txt");

    for (set<string>::const_iterator it = unique.begin(); it != unique.end(); it++) {
		setFile << *it << "\n";
	}

	setFile.close();
}

void OutputVectorContents(const vector<string> &tokens, string fileName) {
	ofstream vectorFile(fileName + "_vector.txt");
    for (string const& word : tokens) {
		vectorFile << word << endl;
	}

	vectorFile.close();
}

void CreateMapFromVector(const vector<string> &tokens, map<string, string> &wordMap) {
	wordMap[""] = tokens.at(0);
	string previousValue = tokens.at(0);
	for (vector<string>::const_iterator it = tokens.begin(); it != tokens.end(); it++) {
		wordMap[previousValue] = *it;
		previousValue = *it;
	}
}

void OutputMapContents(const map<string, string> &wordMap, string fileName) {
	// Iterate through the map or cycle through the keys
	ofstream mapFile(fileName + "_map.txt");
	string currentKey = "";
	for (map<string, string>::const_iterator it = wordMap.begin(); it != wordMap.end(); it++) {
		mapFile << it->first << ", " << it->second << endl;
	}

	mapFile.close();
}

void PrintCyclicalSermon(const map<string, string> &wordMap) {
	string state = "";
	for(int i = 0; i < 100; i++){
	cout << wordMap.at(state) << " ";
	state = wordMap.at(state);
	}
	cout << endl;
}

void CreateVectorMap(map<string, vector<string>> &allFollowWords, const vector<string> &tokens) {
	string state = "";
	for(vector<string>::const_iterator it=tokens.begin(); it !=tokens.end(); it++) {
		allFollowWords[state].push_back(*it);
		state = *it;
	}

	/*
	for(vector<string>::iterator it = allFollowWords["Nephi"].begin(); it != allFollowWords["Nephi"].end(); it++) {
		cout << *it << " ";
	}
	*/
}

void PrintVectorSermon(map<string, vector<string>> &allFollowWords) {
	srand(time(NULL)); // this line initializes the random number generated
                   // so you dont get the same thing every time
	string state = "";
	for (int i = 0; i < 100; i++) {
		int ind = rand() % allFollowWords[state].size();
		cout << allFollowWords.at(state).at(ind) << " ";
		state = allFollowWords.at(state).at(ind);
	}
	cout << endl;
}

void CreateContextMap(map<list<string>, vector<string>> &contextMap, const vector<string> &tokens) {
	list<string> state;
	for (int i = 0; i < M; i++) {
		state.push_back("");
	}

	for (vector<string>::const_iterator it=tokens.begin(); it!= tokens.end(); it++) {
		contextMap[state].push_back(*it);
		state.push_back(*it);
		state.pop_front();
	}
}

void PrintContextSermon(const map<list<string>, vector<string>> &contextMap) {
	list<string> state;
	state.clear();
	for (int i = 0; i < M; i++) {
		state.push_back("");
	}
	for (int i = 0; i < SIZE; i++) {
		if(contextMap.at(state).size() == 0) {
			state.clear();
			for (int i = 0; i < M; i++) {
				state.push_back("");
			}
		}
		int ind = rand() % contextMap.at(state).size();
		cout << contextMap.at(state)[ind]<<" ";
		state.push_back(contextMap.at(state)[ind]);
		state.pop_front();
	}
	cout << endl;
}