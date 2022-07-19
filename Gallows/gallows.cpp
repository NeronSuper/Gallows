#include "Gallows.h"

Gallows::Gallows()
{
	readWordsFromFile();
}

void Gallows::readWordsFromFile()
{
	std::ifstream myfile("words.txt");
	std::string tmp;

	if (myfile.is_open())
	{
		while (myfile >> tmp)
		{
			words.push_back(tmp);
		}
	}

	wordsDecoding();

	myfile.close();
}

const std::string& Gallows::getTheWord() const
{
	srand(std::time(NULL));

	return words[rand() % (words.size() - 1)];
}

void Gallows::wordsDecoding()
{
	for (auto word = words.begin(); word != words.end(); ++word)
	{
		for (int i = 0; i < word->size(); ++i)
		{
			if ((*word)[i] == 'a')
				(*word)[i] = 'z';
			else
				--(*word)[i];
		}
	}
}

std::string Gallows::initGuessWord(const size_t& theWordSize)
{
	std::string tmp;
	for (int i = 0; i < theWordSize; i++)
	{
		tmp.push_back('_');
	}

	return tmp;
}

bool Gallows::isLetterIn(const std::string& theWord, std::string& guessingWord, const char& letter)
{
	bool check = false;

	auto guessing_word = guessingWord.begin();
	for (auto the_word = theWord.begin(); the_word != theWord.end(); ++the_word, ++guessing_word)
	{
		if (*the_word == letter)
		{
			*guessing_word = letter;

			check = true;
		}
	}

	return check;
}

bool Gallows::isRepeatingLetter(const std::vector<char>& mistakesList, const char& letter)
{
	for (auto i = mistakesList.begin(); i < mistakesList.end(); ++i)
	{
		if (*i == letter)
			return true;
	}

	return false;
}

GAME_STATUS Gallows::gameStatus(const std::string& theWord, const std::string& guessingWord, const int& mistakes)
{
	if (mistakes >= 7)
		return GAME_STATUS::LOSE;
	else if (theWord == guessingWord)
		return GAME_STATUS::WIN;
	else
		return GAME_STATUS::PLAYING;
}

void Gallows::printResults(const std::string& theWord, const std::vector<char>& mistakes, const int& numberOfTries)
{
	std::cout << "\nStatus of the game";

	std::cout << "\nThe Word: " << theWord;
	std::cout << "\nYour letters: "; printMistakes(mistakes);
	std::cout << "\nNumber of tries: " << numberOfTries;
	std::cout << "\nYour time: " << time.elapsed() << std::endl;

	std::system("pause");
}

void Gallows::printMistakes(const std::vector<char>& mistakes)
{
	if (mistakes.size() > 0)
	{
		std::cout << mistakes[0];
		for (auto i = mistakes.begin() + 1; i != mistakes.end(); ++i)
		{
			std::cout << ", " << *i;
		}
	}
}

void Gallows::startMenu()
{
	std::system("cls");

	std::cout << "1. Start a game\n" <<
				 "2. Rules\n" <<
				 "3. Exit\n";
}

void Gallows::gameMenu(const std::string& guessingWord, const std::vector<char>& mistakes)
{
	std::system("cls");

	std::cout << "The word: " << guessingWord;

	std::cout << "\nMistakes(" << mistakes.size() << "): ";
	printMistakes(mistakes);

	std::cout << "\nYour letter: ";
}

void Gallows::rules()
{
	std::system("cls");

	std::cout << "In this game, you need to guess the hidden word by entering one letter at a time.\n";

	std::system("pause");
}

void Gallows::start()
{
	do
	{
		startMenu();

		char response;
		std::cin >> response;

		switch (response)
		{
		case '1': game(); break;
		case '2': rules(); break; // need a code
		case '3': return;

		default: break;
		}
	}
	while (true);
}

void Gallows::game()
{
	time.reset();

	const std::string theWord = getTheWord();
	std::vector<char> mistakes = {};
	int numberOfTries = 0;

	std::string guessingWord = initGuessWord(theWord.size());

	char letter; 
	do
	{
		gameMenu(guessingWord, mistakes);

		std::cin.clear();
		std::cin.ignore(32767, '\n');
		std::cin >> letter;
		numberOfTries++;

		if (isRepeatingLetter(mistakes, letter)) // if the user entered the same letter
		{
			std::cout << "\nYou have already entered this letter\n";
			std::system("pause");
			continue;
		}

		if (!isLetterIn(theWord, guessingWord, letter))
		{
			mistakes.push_back(letter);
		}

		switch (gameStatus(theWord, guessingWord, mistakes.size()))
		{
		case GAME_STATUS::WIN:
			std::system("cls");
			std::cout << "YOU WON!\n";
			printResults(theWord, mistakes, numberOfTries);

			return;
		case GAME_STATUS::LOSE:
			std::system("cls");
			std::cout << "YOU LOSE!\n";
			printResults(theWord, mistakes, numberOfTries);

			return;
		case GAME_STATUS::PLAYING:
			break;
		}

	}
	while (true);
}