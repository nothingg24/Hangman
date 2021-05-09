#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cctype>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unistd.h>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <thread>
#include <MMSystem.h>
#include "draw.h"

using namespace std;


int randomIndex(const char* fileName);
string chooseWord(const char* fileName, const int& index);
char readAGuess();
bool contains(const string& word, char guess);
void updateGuessedWord(string& guessedWord, const string& word, char guess);
void getAHint(const string& word, string& guessedWord);
void getFullHints(const string& word, string& guessedWord);
void playAgain();


int main()
{
    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
    welcomeScreen();
    Sleep(3000);
    int choice;
    displayMenu();
    cin >> choice;
    while (choice!=1&&choice!=2&&choice!=3&&choice!=4)
    {
        cout << "Please re-enter your choice: "<<endl;
        cin >> choice;
    }
    if (choice==3)
    {
        clearScreen();
        header();
        set_color(0*16+7);
        ifstream inStream;
        inStream.open("highscore.txt");
        vector <double> highscore;
        double s;
        while (inStream >> s)
        {
            highscore.push_back(s);
        }
        inStream.close();
        sort (highscore.begin(), highscore.end());
        cout<<"Top highscore: "<<endl;
        for (long long unsigned int i=highscore.size()-1;i>=highscore.size()-3;i--)
        {
            cout<<fixed<<setprecision(2)<<highscore.size()-i<<". "<<highscore.at(i)<<endl;
        }
        cout << "Press any key to back to the menu!" <<endl;
        while (true) { if (_kbhit()) playAgain();}
    }
    else if (choice==2) {displayInstruction(); while (true) { if (_kbhit()) playAgain();}}
    else if (choice==4) return 0;
    else if (choice==1)
    {
        int theme;
        chooseTheme();
        cin >> theme;
        while (theme!=1&&theme!=2&&theme!=3)
        {
            cout << "Please re-enter again: ";
            cin >> theme;
        }
        char DATA_FILE[1000];
        char HINT_FILE[1000];
        if (theme==1)
        {
            int diff;
            chooseDifficulty();
            cin >> diff;
            while (diff!=1&&diff!=2)
            {
                cout << "Please re-enter again: ";
                cin >> diff;
            }
            if (diff==1) {strcpy(DATA_FILE, "it_easy.txt");strcpy(HINT_FILE, "it_easy_meaning.txt");}
            else if (diff==2) {strcpy(DATA_FILE, "it_hard.txt");strcpy(HINT_FILE, "it_hard_meaning.txt");}
        }
        else if (theme==2)
        {
            int diff;
            chooseDifficulty();
            cin >> diff;
            while (diff!=1&&diff!=2)
            {
                cout << "Please re-enter again: ";
                cin >> diff;
            }
            if (diff==1) {strcpy(DATA_FILE, "animal_easy.txt");strcpy(HINT_FILE, "animal_easy_meaning.txt");}
            else if (diff==2) {strcpy(DATA_FILE, "animal_hard.txt");strcpy(HINT_FILE, "animal_hard_meaning.txt");}
        }
        else if (theme==3)
        {
            strcpy(DATA_FILE, "random.txt");
        }
        int mode;
        chooseMode();
        cin >> mode;
        while (mode!=1&&mode!=2&&mode!=3)
        {
            cout << "Please re-enter again: ";
            cin >> mode;
        }
        srand(time(0));
        int index=randomIndex(DATA_FILE);
        string word = chooseWord(DATA_FILE, index);
        string meaning=chooseWord(HINT_FILE, index);
        string guessedWord = string(word.length(), '-');
        string badGuesses = "";
        if (mode==1)
        {
            const int MAX_BAD_GUESSES = 7;
            clock_t start=clock();
            bool useHint=false;
            do {
                    renderGame(guessedWord, badGuesses);
                    if (useHint) cout<<endl<<meaning<<endl;
                    char guess = readAGuess();
                    if (guess=='#')
                    {
                        useHint=true;
                        badGuesses+=guess;
                    }
                    else if (contains(word, guess)) updateGuessedWord(guessedWord, word, guess);
                    else {
                        badGuesses += guess;
                    }
                    if (guess=='!') getFullHints(word, guessedWord);
                    if (guess=='*') getAHint(word, guessedWord);
                    if (badGuesses.length()==MAX_BAD_GUESSES-1) getAHint(word, guessedWord);
            } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
            clock_t finish=clock();
            displayFinalResult(badGuesses.length() < MAX_BAD_GUESSES && word==guessedWord, word, meaning);
            double duration=(double) (finish-start)/CLOCKS_PER_SEC;
            cout<<"You have played the game for "<<duration<<" seconds"<<endl;
            if (badGuesses.length() < MAX_BAD_GUESSES&&word==guessedWord)
            {
                double score=((7-badGuesses.length())*word.length()*60)/duration;
                ofstream outStream;
                outStream.open("highscore.txt", ios::app);
                outStream << score <<endl;
                outStream.close();
                cout<<"Your score is: "<<score<<endl;
            }
            ifstream inStream;
            inStream.open("highscore.txt");
            vector <double> highscore;
            double s;
            while (inStream >> s)
            {
                highscore.push_back(s);
            }
            inStream.close();
            sort (highscore.begin(), highscore.end());
            cout<<"Top highscore: "<<endl;
            for (long long unsigned int i=highscore.size()-1;i>=highscore.size()-3;i--)
            {
                cout<<fixed<<setprecision(2)<<highscore.size()-i<<". "<<highscore.at(i)<<endl;
            }
            cout << "Do you want to play again? <Y/N>"<<endl;
            char output;
            cin>>output;
            while (output!='y'&&output!='n'&&output!='Y'&&output!='N')
            {
                cout << "Please re-enter again: " <<endl;
                cin>>output;
            }
            if (output=='y'||output=='Y') playAgain();
        }
        else if (mode==2)
        {
            int m;
            chooseTLimitmode();
            cin>>m;
            while (m!=1&&m!=2)
            {
                cout << "Please re-enter again: ";
                cin >> m;
            }
            const int MAX_BAD_GUESSES = 7;
            clock_t start=clock();
            clock_t point1, point2;
            point1=clock();
            bool useHint=false;
            if (m==1)
            {
                do {
                        renderGame(guessedWord, badGuesses);
                        if (useHint) cout<<endl<<meaning<<endl;
                        point2=clock();
                        char guess = readAGuess();
                        if (((point2-point1)/CLOCKS_PER_SEC)>4) {break;}
                        if (guess=='#')
                        {
                            useHint=true;
                            badGuesses+=guess;
                        }
                        else if (contains(word, guess)) updateGuessedWord(guessedWord, word, guess);
                        else {
                            badGuesses += guess;
                        }
                        if (guess=='!') getFullHints(word, guessedWord);
                        if (guess=='*') getAHint(word, guessedWord);
                        if (badGuesses.length()==MAX_BAD_GUESSES-1) getAHint(word, guessedWord);
                } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
            }
            else if (m==2)
            {
                do {
                        renderGame(guessedWord, badGuesses);
                        if (useHint) cout<<endl<<meaning<<endl;
                        char guess = readAGuess();
                        if (guess=='#')
                        {
                            useHint=true;
                            badGuesses+=guess;
                        }
                        else if (contains(word, guess)) updateGuessedWord(guessedWord, word, guess);
                        else {
                            badGuesses += guess;
                        }
                        point2=clock();
                        if (((point2-point1)/CLOCKS_PER_SEC)>29) {break;}
                        if (guess=='!') getFullHints(word, guessedWord);
                        if (guess=='*') getAHint(word, guessedWord);
                        if (badGuesses.length()==MAX_BAD_GUESSES-1) getAHint(word, guessedWord);
                } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
            }
            clock_t finish=clock();
            displayFinalResult(badGuesses.length() < MAX_BAD_GUESSES && word==guessedWord, word, meaning);
            double duration=(double) (finish-start)/CLOCKS_PER_SEC;
            cout<<"You have played the game for "<<duration<<" seconds"<<endl;
            if (badGuesses.length() < MAX_BAD_GUESSES&&word==guessedWord)
            {
                double score=((7-badGuesses.length())*word.length()*60)/duration;
                ofstream outStream;
                outStream.open("highscore.txt", ios::app);
                outStream << score <<endl;
                outStream.close();
                cout<<"Your score is: "<<score<<endl;
            }
            ifstream inStream;
            inStream.open("highscore.txt");
            vector <double> highscore;
            double s;
            while (inStream >> s)
            {
                highscore.push_back(s);
            }
            inStream.close();
            sort (highscore.begin(), highscore.end());
            cout<<"Top highscore: "<<endl;
            for (long long unsigned int i=highscore.size()-1;i>=highscore.size()-3;i--)
            {
                cout<<fixed<<setprecision(2)<<highscore.size()-i<<". "<<highscore.at(i)<<endl;
            }
            cout << "Do you want to play again? <Y/N>"<<endl;
            char output;
            cin>>output;
            while (output!='y'&&output!='n'&&output!='Y'&&output!='N')
            {
                cout << "Please re-enter again: " <<endl;
                cin>>output;
            }
            if (output=='y'||output=='Y') playAgain();
        }
        else if (mode==3)
        {
            const int MAX_BAD_GUESSES = 1;
            clock_t start=clock();
            do {
                    renderGame(guessedWord, badGuesses);
                    char guess = readAGuess();
                    if (contains(word, guess)) updateGuessedWord(guessedWord, word, guess);
                    else {
                        badGuesses += guess;
                    }
            } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
            clock_t finish=clock();
            displayFinalResult(badGuesses.length() < MAX_BAD_GUESSES && word==guessedWord, word, meaning);
            double duration=(double) (finish-start)/CLOCKS_PER_SEC;
            cout<<"You have played the game for "<<duration<<" seconds"<<endl;
            if (badGuesses.length() < MAX_BAD_GUESSES&&word==guessedWord)
            {
                double score=((7-badGuesses.length())*word.length()*60)/duration;
                ofstream outStream;
                outStream.open("highscore.txt", ios::app);
                outStream << score <<endl;
                outStream.close();
                cout<<"Your score is: "<<score<<endl;
            }
            ifstream inStream;
            inStream.open("highscore.txt");
            vector <double> highscore;
            double s;
            while (inStream >> s)
            {
                highscore.push_back(s);
            }
            inStream.close();
            sort (highscore.begin(), highscore.end());
            cout<<"Top highscore: "<<endl;
            for (long long unsigned int i=highscore.size()-1;i>=highscore.size()-3;i--)
            {
                cout<<fixed<<setprecision(2)<<highscore.size()-i<<". "<<highscore.at(i)<<endl;
            }
            cout << "Do you want to play again? <Y/N>"<<endl;
            char output;
            cin>>output;
            while (output!='y'&&output!='n'&&output!='Y'&&output!='N')
            {
                cout << "Please re-enter again: " <<endl;
                cin>>output;
            }
            if (output=='y'||output=='Y') playAgain();
        }
    }
}

string getLowerCaseString(const string& s)
{
    string res = s;
    transform(s.begin(), s.end(), res.begin(), ::tolower);
    return res;
}

int randomIndex(const char* fileName)
{
    vector<string> wordList;
	ifstream file(fileName);
  	if (file.is_open()) {
	    string word;
		while (file >> word) {
            wordList.push_back(word);
        }
    	file.close();
  	}
  	if (wordList.size() > 0) {
  		int random = rand() % wordList.size();
        return random;
    }
    else return -1;
}

string chooseWord(const char* fileName, const int& index)
{
	vector<string> wordList;
	ifstream file(fileName);
  	if (file.is_open()) {
	    string word;
		while (getline(file, word)) {
            wordList.push_back(word);
        }
    	file.close();
  	}
  	else return "";
    return getLowerCaseString(wordList[index]);
}

char readAGuess()
{
	char input;
	cout << "Your guess: ";
	cin >> input;
	return tolower(input);
}

bool contains(const string& word, char c)
{
	return (word.find_first_of(c) != string::npos);
}

void updateGuessedWord(string& guessedWord, const string& word, char guess)
{
	for (int i = word.length() - 1; i >= 0; i--) {
        if (word[i] == guess) {
            guessedWord[i] = guess;
        }
    }
}

void getAHint(const string& word, string& guessedWord)
{
    int time=0;
    srand(time);
    long long unsigned int randomNumber=rand()%(word.length());
    vector <long long unsigned int> b;
    for (long long unsigned int i=0;i<=word.length()-1;i++)
    {
        if (word[i]==guessedWord[i])
        {
                b.push_back(i);
        }
    }
    for (long long unsigned int i=0;i<b.size();i++)
    {
        if (b.at(i)==randomNumber)
        {
            time++;
            randomNumber=rand()%(word.length());
        }
    }
    for (long long unsigned int i=0;i<=word.length()-1;i++)
    {
        if (word[i]==word[randomNumber])
        {
            guessedWord[i]=word[i];
        }
    }
}

void getFullHints(const string& word,string& guessedWord)
{
    for (long long unsigned int i=0;i<=word.length()-1;i++)
        guessedWord[i]=word[i];
}

void playAgain()
{
    PlaySound(TEXT("music.wav"), NULL, SND_FILENAME|SND_LOOP|SND_ASYNC);
    int choice;
    displayMenu();
    cin >> choice;
    while (choice!=1&&choice!=2&&choice!=3&&choice!=4)
    {
        cout << "Please re-enter your choice: "<<endl;
        cin >> choice;
    }
    if (choice==3)
    {
        ifstream inStream;
        inStream.open("highscore.txt");
        vector <double> highscore;
        double s;
        while (inStream >> s)
        {
            highscore.push_back(s);
        }
        inStream.close();
        sort (highscore.begin(), highscore.end());
        cout<<"Top highscore: "<<endl;
        for (long long unsigned int i=highscore.size()-1;i>=highscore.size()-3;i--)
        {
            cout<<fixed<<setprecision(2)<<highscore.size()-i<<". "<<highscore.at(i)<<endl;
        }
        cout << "Press any key to back to the menu!" << endl;
        while (true) {if (_kbhit()) playAgain();}
    }
    else if (choice==2) {displayInstruction(); while (true) {if (_kbhit()) playAgain();}}
    else if (choice==4) exit(0);
    else if (choice==1)
    {
        int theme;
        chooseTheme();
        cin >> theme;
        while (theme!=1&&theme!=2&&theme!=3)
        {
            cout << "Please re-enter again: ";
            cin >> theme;
        }
        char DATA_FILE[1000];
        char HINT_FILE[1000];
        if (theme==1)
        {
            int diff;
            chooseDifficulty();
            cin >> diff;
            while (diff!=1&&diff!=2)
            {
                cout << "Please re-enter again: ";
                cin >> diff;
            }
            if (diff==1) {strcpy(DATA_FILE, "it_easy.txt");strcpy(HINT_FILE, "it_easy_meaning.txt");}
            else if (diff==2) {strcpy(DATA_FILE, "it_hard.txt");strcpy(HINT_FILE, "it_hard_meaning.txt");}
        }
        else if (theme==2)
        {
            int diff;
            chooseDifficulty();
            cin >> diff;
            while (diff!=1&&diff!=2)
            {
                cout << "Please re-enter again: ";
                cin >> diff;
            }
            if (diff==1) {strcpy(DATA_FILE, "animal_easy.txt");strcpy(HINT_FILE, "animal_easy_meaning.txt");}
            else if (diff==2) {strcpy(DATA_FILE, "animal_hard.txt");strcpy(HINT_FILE, "animal_hard_meaning.txt");}
        }
        else if (theme==3)
        {
            strcpy(DATA_FILE, "random.txt");
        }
        int mode;
        chooseMode();
        cin >> mode;
        while (mode!=1&&mode!=2&&mode!=3)
        {
            cout << "Please re-enter again: ";
            cin >> mode;
        }
        srand(time(0));
        int index=randomIndex(DATA_FILE);
        string word = chooseWord(DATA_FILE, index);
        string meaning=chooseWord(HINT_FILE, index);
        string guessedWord = string(word.length(), '-');
        string badGuesses = "";
        if (mode==1)
        {
            const int MAX_BAD_GUESSES = 7;
            clock_t start=clock();
            bool useHint=false;
            do {
                    renderGame(guessedWord, badGuesses);
                    if (useHint) cout<<endl<<meaning<<endl;
                    char guess = readAGuess();
                    if (guess=='#')
                    {
                        useHint=true;
                        badGuesses+=guess;
                    }
                    else if (contains(word, guess)) updateGuessedWord(guessedWord, word, guess);
                    else {
                        badGuesses += guess;
                    }
                    if (guess=='!') getFullHints(word, guessedWord);
                    if (guess=='*') getAHint(word, guessedWord);
                    if (badGuesses.length()==MAX_BAD_GUESSES-1) getAHint(word, guessedWord);
            } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
            clock_t finish=clock();
            displayFinalResult(badGuesses.length() < MAX_BAD_GUESSES && word==guessedWord, word, meaning);
            double duration=(double) (finish-start)/CLOCKS_PER_SEC;
            cout<<"You have played the game for "<<duration<<" seconds"<<endl;
            if (badGuesses.length() < MAX_BAD_GUESSES&&word==guessedWord)
            {
                double score=((7-badGuesses.length())*word.length()*60)/duration;
                ofstream outStream;
                outStream.open("highscore.txt", ios::app);
                outStream << score <<endl;
                outStream.close();
                cout<<"Your score is: "<<score<<endl;
            }
            ifstream inStream;
            inStream.open("highscore.txt");
            vector <double> highscore;
            double s;
            while (inStream >> s)
            {
                highscore.push_back(s);
            }
            inStream.close();
            sort (highscore.begin(), highscore.end());
            cout<<"Top highscore: "<<endl;
            for (long long unsigned int i=highscore.size()-1;i>=highscore.size()-3;i--)
            {
                cout<<fixed<<setprecision(2)<<highscore.size()-i<<". "<<highscore.at(i)<<endl;
            }
            cout << "Do you want to play again? <Y/N>"<<endl;
            char output;
            cin>>output;
            while (output!='y'&&output!='n'&&output!='Y'&&output!='N')
            {
                cout << "Please re-enter again: " <<endl;
                cin>>output;
            }
            if (output=='y'||output=='Y') playAgain();
        }
        else if (mode==2)
        {
            int m;
            chooseTLimitmode();
            cin>>m;
            while (m!=1&&m!=2)
            {
                cout << "Please re-enter again: ";
                cin >> m;
            }
            const int MAX_BAD_GUESSES = 7;
            clock_t start=clock();
            clock_t point1, point2;
            point1=clock();
            bool useHint=false;
            if (m==1)
            {
                do {
                        renderGame(guessedWord, badGuesses);
                        if (useHint) cout<<endl<<meaning<<endl;
                        point2=clock();
                        char guess = readAGuess();
                        if (((point2-point1)/CLOCKS_PER_SEC)>4) {break;}
                        if (guess=='#')
                        {
                            useHint=true;
                            badGuesses+=guess;
                        }
                        else if (contains(word, guess)) updateGuessedWord(guessedWord, word, guess);
                        else {
                            badGuesses += guess;
                        }
                        if (guess=='!') getFullHints(word, guessedWord);
                        if (guess=='*') getAHint(word, guessedWord);
                        if (badGuesses.length()==MAX_BAD_GUESSES-1) getAHint(word, guessedWord);
                } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
            }
            else if (m==2)
            {
                do {
                        renderGame(guessedWord, badGuesses);
                        if (useHint) cout<<endl<<meaning<<endl;
                        char guess = readAGuess();
                        if (guess=='#')
                        {
                            useHint=true;
                            badGuesses+=guess;
                        }
                        else if (contains(word, guess)) updateGuessedWord(guessedWord, word, guess);
                        else {
                            badGuesses += guess;
                        }
                        point2=clock();
                        if (((point2-point1)/CLOCKS_PER_SEC)>29) {break;}
                        if (guess=='!') getFullHints(word, guessedWord);
                        if (guess=='*') getAHint(word, guessedWord);
                        if (badGuesses.length()==MAX_BAD_GUESSES-1) getAHint(word, guessedWord);
                } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
            }
            clock_t finish=clock();
            displayFinalResult(badGuesses.length() < MAX_BAD_GUESSES && word==guessedWord, word, meaning);
            double duration=(double) (finish-start)/CLOCKS_PER_SEC;
            cout<<"You have played the game for "<<duration<<" seconds"<<endl;
            if (badGuesses.length() < MAX_BAD_GUESSES&&word==guessedWord)
            {
                double score=((7-badGuesses.length())*word.length()*60)/duration;
                ofstream outStream;
                outStream.open("highscore.txt", ios::app);
                outStream << score <<endl;
                outStream.close();
                cout<<"Your score is: "<<score<<endl;
            }
            ifstream inStream;
            inStream.open("highscore.txt");
            vector <double> highscore;
            double s;
            while (inStream >> s)
            {
                highscore.push_back(s);
            }
            inStream.close();
            sort (highscore.begin(), highscore.end());
            cout<<"Top highscore: "<<endl;
            for (long long unsigned int i=highscore.size()-1;i>=highscore.size()-3;i--)
            {
                cout<<fixed<<setprecision(2)<<highscore.size()-i<<". "<<highscore.at(i)<<endl;
            }
            cout << "Do you want to play again? <Y/N>"<<endl;
            char output;
            cin>>output;
            while (output!='y'&&output!='n'&&output!='Y'&&output!='N')
            {
                cout << "Please re-enter again: " <<endl;
                cin>>output;
            }
            if (output=='y'||output=='Y') playAgain();
        }
        else if (mode==3)
        {
            const int MAX_BAD_GUESSES = 1;
            clock_t start=clock();
            do {
                    renderGame(guessedWord, badGuesses);
                    char guess = readAGuess();
                    if (contains(word, guess)) updateGuessedWord(guessedWord, word, guess);
                    else {
                        badGuesses += guess;
                    }
            } while (badGuesses.length() < MAX_BAD_GUESSES && word != guessedWord);
            clock_t finish=clock();
            displayFinalResult(badGuesses.length() < MAX_BAD_GUESSES && word==guessedWord, word, meaning);
            double duration=(double) (finish-start)/CLOCKS_PER_SEC;
            cout<<"You have played the game for "<<duration<<" seconds"<<endl;
            if (badGuesses.length() < MAX_BAD_GUESSES&&word==guessedWord)
            {
                double score=((7-badGuesses.length())*word.length()*60)/duration;
                ofstream outStream;
                outStream.open("highscore.txt", ios::app);
                outStream << score <<endl;
                outStream.close();
                cout<<"Your score is: "<<score<<endl;
            }
            ifstream inStream;
            inStream.open("highscore.txt");
            vector <double> highscore;
            double s;
            while (inStream >> s)
            {
                highscore.push_back(s);
            }
            inStream.close();
            sort (highscore.begin(), highscore.end());
            cout<<"Top highscore: "<<endl;
            for (long long unsigned int i=highscore.size()-1;i>=highscore.size()-3;i--)
            {
                cout<<fixed<<setprecision(2)<<highscore.size()-i<<". "<<highscore.at(i)<<endl;
            }
            cout << "Do you want to play again? <Y/N>"<<endl;
            char output;
            cin>>output;
            while (output!='y'&&output!='n'&&output!='Y'&&output!='N')
            {
                cout << "Please re-enter again: " <<endl;
                cin>>output;
            }
            if (output=='y'||output=='Y') playAgain();
        }
    }
}





