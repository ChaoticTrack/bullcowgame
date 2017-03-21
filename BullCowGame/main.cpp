/*	This is the console execeutable, which makes use of the BullCow class.
This acts as the view in an MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include <cstdlib> // system
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool bAskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

// entry point for application
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();

		bPlayAgain = bAskToPlayAgain();
	}
	while (bPlayAgain);

	std::cout << "\nThanks for playing Bulls and Cows!" << std::endl;

	return 0; // exit point for application
}



void PrintIntro()
{
	if (system("CLS")) system("clear");
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << R"(
                    \  |  /         ___________
     ____________  \ \_# /         |  ___      |       _________
    |            |  \  #/          | |   |     |      | = = = = |
    | |   |   |  |   \\#           | |`v'|     |      |         |
    |            |    \#  //       |  --- ___  |      | |  || | |
    | |   |   |  |     #_//        |     |   | |      |         |
    |            |  \\ #_/_______  |     |   | |      | |  || | |
    | |   |   |  |   \\# /_____/ \ |      ---  |      |         |
    |            |    \# |+ ++|  | |  |^^^^^^| |      | |  || | |
    |            |    \# |+ ++|  | |  |^^^^^^| |      | |  || | |
 ^^^|    (^^^^^) |^^^^^#^| H  |_ |^|  | |||| | |^^^^^^|         |
    |    ( ||| ) |     # ^^^^^^    |  | |||| | |      | ||||||| |
    ^^^^^^^^^^^^^________/  /_____ |  | |||| | |      | ||||||| |
         `v'-                      ^^^^^^^^^^^^^      | ||||||| |
          || |`.      (__)    (__)                          ( )
                      (oo)    (oo)                       /---V
               /-------\/      \/ --------\             * |  |
              / |     ||        ||_______| \
             *  ||W---||        ||      ||  *
                ^^    ^^        ^^      ^^
 ___           _    _             _____       ___                           
(  _`\        (_ ) (_ )          (  _  )     (  _`\                         
| (_) ) _   _  | |  | |   ___    `\  ,/'     | ( (_)   _    _   _   _   ___ 
|  _ <'( ) ( ) | |  | | /',__)    /'_`\/\    | |  _  /'_`\ ( ) ( ) ( )/',__)
| (_) )| (_) | | |  | | \__, \   | (_> ,<`   | (_( )( (_) )| \_/ \_/ |\__, \
(____/'`\___/'(___)(___)(____/   `\___/\/'   (____/'`\___/'`\___x___/'(____/                                                          
	)" << std::endl;
	std::cout << "In this game, you must guess a isogram, which is a word \n"
		<< "without any repeating letters. \n" << std::endl;
	std::cout << "Bull: correct letter in the correct position. \n"
		<< "Cow: correct letter in the wrong position. \n"<< std::endl;

	return;
}

// plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// user chooses word length
	BCGame.SetWordLength();

	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength()
		<< " letter isogram I'm thinking of? \n" << std::endl;

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
		FText Guess = GetValidGuess(); 

		// submit VALID guess to the game, receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n" << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters. \n" << std::endl;
			break;
		case EGuessStatus::Incorrect_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n" << std::endl;
			break;
		default: // OK
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool bAskToPlayAgain()
{
	std::cout << "Would you like to play again? (y/n)" << std::endl;
	FText response = "";
	std::getline(std::cin, response);
	
	return (response[0] == 'y') || (response[0] == 'Y');
}

// post game messages
void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << R"(
  __     __          __          _ _       _ 
  \ \   / /          \ \        / (_)     | |
   \ \_/ /__  _   _   \ \  /\  / / _ _ __ | |
    \   / _ \| | | |   \ \/  \/ / | | '_ \| |
     | | (_) | |_| |    \  /\  /  | | | | |_|
     |_|\___/ \__,_|     \/  \/   |_|_| |_(_)

  *      *   *   **                 *   *       * 
*   ** *        *  *            **           **   
 *         *  **    ** * * **  *     *** * **    *
  *                                 *             
     *               **     *              * *    
               *                     * * **      *
 *    **     *  *  **     *                   * * 
              *  *      *               *         
   *              *            *  **        *     
*   *    ****                         *        *  
**    *  *         *   * **     **        *       
        *                  * **                                                       
		)" << std::endl;
		std::cout << "NICE WORK - YOU WIN!" << std::endl;
	}
	else {
		std::cout << R"(                            
@@@ @@@   @@@@@@   @@@  @@@     @@@        @@@@@@    @@@@@@   @@@@@@@@  
@@@ @@@  @@@@@@@@  @@@  @@@     @@@       @@@@@@@@  @@@@@@@   @@@@@@@@  
@@! !@@  @@!  @@@  @@!  @@@     @@!       @@!  @@@  !@@       @@!       
!@! @!!  !@!  @!@  !@!  @!@     !@!       !@!  @!@  !@!       !@!       
 !@!@!   @!@  !@!  @!@  !@!     @!!       @!@  !@!  !!@@!!    @!!!:!    
  @!!!   !@!  !!!  !@!  !!!     !!!       !@!  !!!   !!@!!!   !!!!!:    
  !!:    !!:  !!!  !!:  !!!     !!:       !!:  !!!       !:!  !!:       
  :!:    :!:  !:!  :!:  !:!      :!:      :!:  !:!      !:!   :!:       
   ::    ::::: ::  ::::: ::      :: ::::  ::::: ::  :::: ::    :: ::::  
   :      : :  :    : :  :      : :: : :   : :  :   :: : :    : :: ::   

		)" << std::endl;
		std::cout << "You ran out of tries! Better luck next time." << std::endl;
		std::cout << "The correct answer was " << BCGame.GetHiddenWord() << ". \n";
	}
}
