#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <windows.h>
#include <iomanip>

using namespace std;

//#define NOMINMAX
//#define WIN32_LEAN_AND_MEAN

void clearScreen() {
    const int PATCH_LINES = 30;
	for (int i = 0; i < PATCH_LINES; i++) cout << endl;
}

void set_color ( int code ) {
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}

void header()
{
    clearScreen();
    set_color(0*16+'B');
    cout << "     Created by nothingg     " << endl;
    set_color(0*16+7);
    cout << endl;
    cout << endl;
}

void welcomeScreen()
{
    clearScreen();
    set_color(3*16+0);
    cout << "     W";
    std::this_thread::sleep_for(300ms);
    cout << "e";
    std::this_thread::sleep_for(300ms);
    cout << "l";
    std::this_thread::sleep_for(300ms);
    cout << "c";
    std::this_thread::sleep_for(300ms);
    cout << "o";
    std::this_thread::sleep_for(300ms);
    cout << "m";
    std::this_thread::sleep_for(300ms);
    cout << "e ";
    std::this_thread::sleep_for(300ms);
    cout << "t";
    std::this_thread::sleep_for(300ms);
    cout << "o ";
    std::this_thread::sleep_for(300ms);
    cout << "H";
    std::this_thread::sleep_for(300ms);
    cout << "A";
    std::this_thread::sleep_for(300ms);
    cout << "N";
    std::this_thread::sleep_for(300ms);
    cout << "G";
    std::this_thread::sleep_for(300ms);
    cout << "M";
    std::this_thread::sleep_for(300ms);
    cout << "A";
    std::this_thread::sleep_for(300ms);
    cout << "N     " << endl;
    std::this_thread::sleep_for(600ms);
    cout << "            .";
    std::this_thread::sleep_for(300ms);
    cout << ".";
    std::this_thread::sleep_for(300ms);
    cout << ".             " << endl;
    std::this_thread::sleep_for(600ms);
}

void displayMenu()
{
    clearScreen();
    header();
    set_color(0*16+6);
    cout << "           HANGMAN     "<<endl;
    cout << "              |    \n"
            "              O    \n"
            "             /|\\  \n"
            "             / \\  \n";
    cout << endl;
    cout << endl;
    cout << "1- Mode\n"
         << "2- Instruction\n"
         << "3- High Score\n"
         << "4- Exit\n";
}

void displayInstruction()
{
    clearScreen();
    header();
    set_color(0*16+7);
    cout << endl;
    cout << "- Press 1 to choose your mode\n"
         << "- Press 2 to display instructions\n"
         << "- Press 3 to display Top Highscore\n"
         << "- Press 4 to exit the game\n";
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "- The computer will random a word for you and your mission is guess this word\n"
         << "- If your guess is true, your guess will be displayed on the exact position of this letter\n"
         << "- If your guess is wrong, your bad guess will increase by one\n"
         << "- Press * for a hint and press ! if you want to win immediately\n"
         << "- If you use them, your bad guess will also increase by one\n"
         << "- First, you will have to choose word themes and difficulty of them, except for random word themes, you don't need to choose difficulty\n"
         << "- You have maximum seven bad guesses in normal and hard mode but only one bad guess in insane mode\n"
         << "- In hard mode, there are two time limit mode for you: 5s per guess or 30s per game\n";
    cout << endl;
    cout << "Press any key to back to the menu!\n";
}

void chooseTheme()
{
    clearScreen();
    header();
    set_color(0*16+7);
    cout << "1-Information technology\n";
    std::this_thread::sleep_for(300ms);
    cout << "2-Animal\n";
    set_color(0*16+4);
    std::this_thread::sleep_for(300ms);
    cout << "3-Random\n";
    set_color(0*16+7);
}

void chooseDifficulty()
{
    clearScreen();
    header();
    set_color(0*16+7);
    cout << "1-Easy\n";
    set_color(0*16+4);
    std::this_thread::sleep_for(300ms);
    cout << "2-Hard\n";
    set_color(0*16+7);
}

void chooseMode()
{
    clearScreen();
    header();
    set_color(0*16+7);
    cout << "1-Normal\n";
    std::this_thread::sleep_for(300ms);
    set_color(0*16+1);
    cout << "2-Hard\n";
    std::this_thread::sleep_for(300ms);
    set_color(0*16+4);
    cout << "3-Insane\n";
    set_color(0*16+7);
}

void chooseTLimitmode()
{
    clearScreen();
    header();
    set_color(0*16+7);
    cout << "1 - 5s per guess" << endl;
    std::this_thread::sleep_for(300ms);
    cout << "2 - 30s per game" << endl;
}


/**void cls()
{
    // Get the Win32 handle representing standard output.
    // This generally only has to be done once, so we make it static.
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    COORD topLeft = { 0, 0 };

    // std::cout uses a buffer to batch writes to the underlying console.
    // We need to flush that to the console because we're circumventing
    // std::cout entirely; after we clear the console, we don't want
    // stale buffered text to randomly be written out.
    std::cout.flush();

    // Figure out the current width and height of the console window
    if (!GetConsoleScreenBufferInfo(hOut, &csbi)) {
        // TODO: Handle failure!
        abort();
    }
    DWORD length = csbi.dwSize.X * csbi.dwSize.Y;

    DWORD written;

    // Flood-fill the console with spaces to clear it
    FillConsoleOutputCharacter(hOut, TEXT(' '), length, topLeft, &written);

    // Reset the attributes of every character to the default.
    // This clears all background colour formatting, if any.
    FillConsoleOutputAttribute(hOut, csbi.wAttributes, length, topLeft, &written);

    // Move the cursor back to the top left for the next sequence of writes
    SetConsoleCursorPosition(hOut, topLeft);
}*/

const string FIGURE[] = {
        "   -------------    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |                \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |                \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |           |    \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|    \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |                \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          /     \n"
        "   |     \n"
        " -----   \n",
        "   -------------    \n"
        "   |           |    \n"
        "   |           O    \n"
        "   |          /|\\  \n"
        "   |          / \\  \n"
        "   |     \n"
        " -----   \n"
    };

void renderGame(const string& guessedWord, const string& badGuesses)
{
	clearScreen();
	header();
	set_color(0*16+7);
	int badGuessCount = badGuesses.length();
	cout << FIGURE[badGuessCount] << endl;
	cout << "Secret word: " << guessedWord << endl;
	if (badGuessCount > 0) {
		cout << "You've made " << badGuessCount << " wrong ";
		cout << (badGuessCount == 1 ? "guess" : "guesses");
		cout << ": " << badGuesses << endl;
	}
}

const string& getNextDancingMan() {
    const static string figure[] = {
    "     O     \n"
    "    /|\\   \n"
    "    | |    \n",
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n",
    "   __O__   \n"
    "     |     \n"
    "    / \\   \n",
    "    \\O/   \n"
    "     |     \n"
    "    / \\   \n",
    "   __O__   \n"
    "     |     \n"
    "    / \\   \n",
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n" ,
    "    O      \n"
    "    /|\\   \n"
    "    / \\   \n" ,
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n" ,
    "      O    \n"
    "    /|\\   \n"
    "    / \\   \n" ,
    "     O     \n"
    "    /|\\   \n"
    "    / \\   \n" ,


    };
    const static int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

const string& getNextHangMan() {
    const static string figure[] = {
    "   ------------+    \n"
    "   |    /           \n"
    "   |    O      \n"
    "   |   /|\\    \n"
    "   |   / \\    \n"
    "   |        \n"
    " -----      \n" ,
    "   ------------+     \n"
    "   |     |           \n"
    "   |     O           \n"
    "   |    /|\\         \n"
    "   |    / \\         \n"
    "   |        \n"
    " -----      \n",
    "   ------------+     \n"
    "   |      \\         \n"
    "   |      O          \n"
    "   |     /|\\        \n"
    "   |     / \\        \n"
    "   |      \n"
    " -----    \n",
    "   ------------+     \n"
    "   |     |           \n"
    "   |     O           \n"
    "   |    /|\\         \n"
    "   |    / \\         \n"
    "   |        \n"
    " -----      \n"
    };
    const static int NUMBER_OF_FIGURES = sizeof(figure) / sizeof(string);
    static int currentFigure = 0;
    return figure[(currentFigure++) % NUMBER_OF_FIGURES];
}

void displayFinalResult(bool won, const string& word, const string& meaning) {
    int k=0;
    while (k<=10) {
        set_color(0*16+7);
        clearScreen();
        if (won)
            {cout << "Congratulations! You win! Your word is " << word << endl;
            cout << "Word meaning: " << meaning << endl;}
        else
            {cout << "You lost. The correct word is " << word << endl;
            cout << "Word meaning: " << meaning << endl;}
        cout << (won ? getNextDancingMan() : getNextHangMan());
        this_thread::sleep_for(chrono::milliseconds(500));
        k++;
    }
}

