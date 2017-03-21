/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind
*/
#pragma once

#include <iostream>
#include <string>

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	Not_Isogram,
	Not_Lowercase,
	Incorrect_Length,
	OK
};

class FBullCowGame
{
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString Guess) const;
	
	void Reset();
	void SetWordLength();

	// counts bulls and cows, and increases try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString Guess);	

private:
	int32 MyCurrentTry;
	int32 MyWordLength;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};