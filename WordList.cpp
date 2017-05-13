#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <list>
#include <set>
#include "WordList.h"
	
using namespace std;
	
	void WordList::partition(char c){
		for (std::string str : wordList){
			int i=0;
			std::string temp = str;
			//replace every character in string but char c.
			for (int i = 0; i < temp.length(); ++i) {
			    if (temp[i] != c)
			      temp[i] = '-';
			}
			cout << temp << "  ";
		//look up the tempword in the map, if cant find 
		//family for it create new fam, 
		//add the word to fam and add the family to map
		//if found a family for it add the word to the family 
		//http://www.cplusplus.com/reference/map/map/find/
			std::map<string,Family>::iterator it;
			it = fams.find(temp);
			if (it == fams.end()){
				Family newFam;
				newFam.insert(str);
				fams[temp] = newFam;
			}
			else{
				it->second.insert(str);
			}
		}
	}
	
	void WordList::printFam(){
		cout << "___FAMILIES___";
		cout << endl;
		for (auto a : fams){
			cout << a.first << endl;
			for (auto b : a.second)
				cout << b << " ";
			cout << endl << endl;
		}
		cout << endl;
	}
	
	void WordList::print(){
		cout << endl;
		for (string a : wordList){
			cout << a << " ";
		}
		cout << endl;
	}
	
	void WordList::readList(std::string filename, int length){
		std::ifstream file(filename);
		std::string str; 
		while (std::getline(file, str)){
			if (str.length()==length)
			wordList.push_back(str);
		}
		actualSkeltal = std::string(length, '-');
	}
	
	void WordList::refreshSkeleton(std::string str){
		int i = 0;
		for (char s : str){
			if (s != '-'){
				actualSkeltal[i] = s;
			};
			i++;
		}
	}
	
	WordList::WordList(std::string filename, int length){
		readList(filename, length);
	}
	
	std::string WordList::getSkeleton(){
		return actualSkeltal;
	}
	
	bool WordList::contains(char c){
		return actualSkeltal.find(c) != std::string::npos;
	}
	
	void WordList::shortenList(char c){
		partition(c);
		printFam();
		//http://stackoverflow.com/questions/9370945/c-help-finding-the-max-value-in-a-map
		using pair_type = decltype(fams)::value_type;
		auto maxpair = std::max_element
		(
		    std::begin(fams), std::end(fams),
		    [] (const pair_type & p1, const pair_type & p2) {
		        return p1.second.size() < p2.second.size();
		    }
		);
		actualFamily = maxpair->second;
		cout << endl;
		cout << "WINNER FAMILY: " << maxpair->first << endl;;
		cout << endl;
		refreshSkeleton(maxpair->first);
		//convert set to list and make that the wordList
		wordList = std::list<string>(actualFamily.begin(), actualFamily.end());
		//empty the families
		fams.clear();
		//System.gc();
	}