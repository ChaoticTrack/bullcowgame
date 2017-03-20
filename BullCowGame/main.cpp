/*	This is the console execeutable, which makes use of the BullCow class.
This acts as the view in an MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText Guess);
bool bAskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();

		bPlayAgain = bAskToPlayAgain();
	}
	while (bPlayAgain);

	return 0;
}



// Functions ////////////////////////////////////////////////////
void PrintIntro()
{
	// TODO get current word length from game method
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game. \n"
		"Can you guess the " << BCGame.GetHiddenWordLength()
		<< " letter isogram I'm thinking of? \n" << std::endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) { // TODO change from FOR to WHILE
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	// TODO summarize game
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters." << std::endl;
			break;
		case EGuessStatus::Incorrect_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		default: // OK
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

void PrintGuess(FText Guess)
{
	std::cout << "Your Guess was: " << Guess << std::endl;
	return;
}

bool bAskToPlayAgain()
{
	std::cout << "Would you like to play again? (y/n)" << std::endl;
	FText response = "";
	std::getline(std::cin, response);
	
	return (response[0] == 'y') || (response[0] == 'Y');
}