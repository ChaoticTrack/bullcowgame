#include "FBullCowGame.h"

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (false) // if the guess isn't all lowercase
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
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "planet";
	
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount; // return value
	int32 WordLength = GetHiddenWordLength();

	// loop through all letters in the GUESS
	for (int32 GChar = 0; GChar < WordLength; GChar++) {
		// compare letters against the hidden word
		for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				((GChar == MHWChar) ? BullCowCount.Bulls++ : BullCowCount.Cows++);
			} // end of check for matching letters
		} // end of check for a single letter in guess
	} // end of check for all letters in guess

	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	} else {
		bGameIsWon = false;
	}

	return BullCowCount;
}
