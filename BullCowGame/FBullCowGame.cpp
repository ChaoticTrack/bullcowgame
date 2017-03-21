#pragma once

#include "FBullCowGame.h"
#include <map>

// to make more UNreal friendly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {1,3}, {2,4}, {3,5}, {4,7}, {5,10}, {6,15}, {7, 20} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Incorrect_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyWordLength = 3;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

void FBullCowGame::SetWordLength()
{
	int32 WordLengthChoice = 0;
	std::cout << "How long would you like the word to be? (3-7)" << std::endl;
	while (true)
	{
		std::cout << "Word length: ";
		std::cin >> WordLengthChoice;
		if (!std::cin.good() || WordLengthChoice < 3 || WordLengthChoice > 7) {
			std::cout << "Word length must be a number between 3 and 7. \n" << std::endl;
			std::cin.clear();
			std::cin.ignore(128, '\n');
		}
		else {
			std::cin.clear();
			std::cin.ignore(128, '\n');
			std:: cout << std::endl;
			break;
		}
	}

	MyWordLength = WordLengthChoice;
	
	// TODO make a word list for hidden word
	switch (MyWordLength)
	{
	case 1:
		MyHiddenWord = "a";
		break;
	case 2:
		MyHiddenWord = "my";
		break;
	case 3:
		MyHiddenWord = "air";
		break;
	case 4:
		MyHiddenWord = "goal";
		break;
	case 5:
		MyHiddenWord = "birds";
		break;
	case 6:
		MyHiddenWord = "planet";
		break;
	case 7:
		MyHiddenWord = "isogram";
		break;
	default:
		MyHiddenWord = "error";
	}

	return;
}

// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount; // return value
	int32 WordLength = GetHiddenWordLength();

	for (int32 GChar = 0; GChar < WordLength; GChar++) {
		for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				((GChar == MHWChar) ? BullCowCount.Bulls++ : BullCowCount.Cows++);
			} 
		} 
	} 

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	 
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the Word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { return false; } // not an isogram 
		else { LetterSeen[Letter] = true; }
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if ( !islower(Letter) ) { return false; }
	}
	return true;
}
