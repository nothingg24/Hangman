
#include <iostream>

using namespace std;

void clearScreen();
void set_color (int code);
void header();
void welcomeScreen();
void displayMenu();
void chooseTheme();
void chooseDifficulty();
void chooseMode();
void displayInstruction();
void renderGame(const string& guessedWord, const string& badGuesses);
void displayFinalResult(bool won, const string& word, const string& meaning);
void chooseTLimitmode();

