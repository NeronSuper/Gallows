#pragma once
#include "Timer.h"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>

enum class GAME_STATUS
{
	WIN,
	LOSE,
	PLAYING
};


class Gallows
{
public:
	Gallows();

	void readWordsFromFile();
	const std::string& getTheWord() const;
	void wordsDecoding();
	std::string initGuessWord(const size_t& theWordSize);
	bool isLetterIn(const std::string& theWord, std::string& guessingWord, const char& letter);
	bool isRepeatingLetter(const std::vector<char>& mistakesList, const char& letter);
	GAME_STATUS gameStatus(const std::string& theWord, const std::string& guessingWord, const int& mistakes);
	void printResults(const std::string& theWord, const std::vector<char>& mistakes, const int& numberOfTries);
	void printMistakes(const std::vector<char>& mistakes);

	void startMenu();
	void gameMenu(const std::string& guessingWord, const std::vector<char>& mistakes);
	void rules();

	void start();
	void game();

private:
	Timer time;
	std::vector<std::string> words;
};

