#ifndef WORDLIST_H_INCLUDED
#define WORDLIST_H_INCLUDED

#include <string>
#include <map>
#include <list>
#include <set>

class WordList{
private:
	using Family = std::set<std::string>;
	std::list<std::string> wordList;
	std::map<std::string,Family> fams;
	Family actualFamily;
	std::string actualSkeltal;
	
	void partition(char c);
	
	void readList(std::string filename, int length);
	
	void refreshSkeleton(std::string str);
	
public:
	WordList(std::string filename, int length);
	
	std::string getSkeleton();
	
	bool contains(char c);
	
	void shortenList(char c);
	
	void print();
	
	void printFam();
};


#endif // WORDLIST_H_INCLUDED 