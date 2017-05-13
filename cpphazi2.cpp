#include <iostream>
#include "WordList.h"
#include <set>

using namespace std;

static bool verifyLength(int length){
	if (length > 30 || length <= 0){
		cout << "Invalid length, try again. " << endl;
		return false;
	}
	return true;
}

static bool verifyDifficulty(int difficulty){
	if (difficulty <= 0){
		cout << "Invalid difficulty, try again. " << endl;
		return false;
	}
	return true;
}

int main()
{
	int length = 0;
	int numberOfTries;
	bool end = false;
	
	set<char> characters;
	
	cout << "__________________EVIL HANGMAN 2017__________________" << endl;
	do{
		cout << "Enter the desired length: " << endl;
		cin >> length;
	} while (!verifyLength(length));
	do {
		cout << "Enter the desired difficulty: " << endl;
		cin >> numberOfTries;
	} while (!verifyDifficulty(numberOfTries));
	
	WordList wordList("dictionary.txt", length);
	
	while (!end){
		char c;
		cout << "enter the character: " << endl;
		cin >> c;
		//http://stackoverflow.com/questions/13934085/stdfind-on-a-legacy-array
		if (std::end(characters) != std::find(std::begin(characters), std::end(characters), c)){
			cout << "Please choose another character. " << endl;
		}
		else{
			wordList.shortenList(c);
			if (wordList.contains(c)){
				cout << "Correct guess for character " << c << endl;
			}
			else{
				cout << "WRONG GUESS" << endl;;
				if (numberOfTries-- == 0)
					end = true;
			}
			characters.insert(c);
		}
		cout << wordList.getSkeleton() << endl;
		cout << "Number of tries left: " << numberOfTries << endl;
		cout << "Used characters so far: ";
		for (char c : characters){
			cout << c << " ";
		}
		cout << endl;
#ifdef DEBUG
		wordList.print();
#endif
	
	if (!wordList.contains('-')){
		end = true;
		cout << "Your winner" << endl;
	}
		
	}
	
    return 0;
}