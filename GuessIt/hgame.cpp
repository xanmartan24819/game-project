#include "hgame.h"
#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

void cgame::ga_Init()
{
    srand(time(NULL));
}
void cgame::ga_ChooseLevel()
{
    clear_screen();
    cout << "\t\t\t\t GUESS IT\n\n";
    cout << "\t\t\t Choose your level\n\n";
    cout << "\t 1: EASY        0 ~ 500\n";
    cout << "\t 2: MEDIUM   -500 ~ 500\n";
    cout << "\t 3: HARD    -1000 ~ 1000\n\n";
    cout << "Your choice: ";
    short choice = 0;
    while (choice < 1 || choice > 3)
    {
        gotoxy(13, 8);
        cout << "       ";
        gotoxy(13, 8);
        cin >> choice;
    }
    if (choice == 1)
    {
        rangeMin = 0;
        rangeMax = 500;
    }
    else if (choice == 2)
    {
        rangeMin = -500;
        rangeMax = 500;
    }
    else if (choice == 3)
    {
        rangeMin = -1000;
        rangeMax = 1000;
    }
    cout << "\nAre you a human? (Y / N): ";
    char choice2;
    cin >> choice2;
    if (choice2 == 'y' || choice2 == 'Y') isPlayer = true;
    else isPlayer = false;
    clear_screen();
}

void cgame::ga_Prepare()
{
    num_guess = 0;
    answer = random(rangeMin, rangeMax);
    if (!isPlayer)
    {
        botMin = rangeMin;
        botMax = rangeMax;
    }
    cout << "\t\t\t\t GUESS IT\n\n";
    cout << "Range: " << rangeMin << " ~ " << rangeMax;
    if (!isPlayer) cout << "\t\t Bot Mode";
    cout << "\n";
    cout << "Your tries: " << num_guess << "\n\n";
    cout << "Your answer: ";
}

void cgame::ga_GetInput()
{
    if (isPlayer) cin >> player_answer;
    else
    {
        player_answer = (botMax + botMin) / 2;
        cout << player_answer;
        getch();
    }
}

void cgame::ga_Calculate()
{
    reply = checkAnswer();
    num_guess++;
    if (reply == RIGHT)
    {
        ga_onMatch = false;
    }
    if (!isPlayer)
    {
        if (reply == BELOW) botMin = player_answer;
        else if (reply == ABOVE) botMax = player_answer;
        else if (reply == FBELOW) botMin = player_answer + (rangeMax - rangeMin) / 4;
        else if (reply == FABOVE) botMax = player_answer - (rangeMax + rangeMin) / 4;
    }
}

void cgame::ga_Draw()
{
    if (num_guess % 20 == 0)
    {
        for (int i = 1; i <= 20; i++)
        {
            gotoxy(0, 7 + i);
            cout << "                                                                         ";
        }
    }
    gotoxy(0, 7 + num_guess % 20);
    if (reply == FBELOW) cout << "Your answer " << player_answer << " is TOO FAR BELOW. Never give up";
    else if (reply == BELOW) cout << "Your answer " << player_answer << " is BELOW. You've almost got it";
    else if (reply == FABOVE) cout << "Your answer " << player_answer << " is TOO FAR ABOVE. Come on, you can do it";
    else if (reply == ABOVE) cout << "Your answer " << player_answer << " is ABOVE. Give it the best shot";
    else if (reply == RIGHT) cout << "Your answer " << player_answer << " is RIGHT. Congratulations";
    else if (reply == OUTRANGE) cout << "Your answer " << player_answer << " is OUT OF RANGE. Let's try again";
    gotoxy(12, 3);
    cout << num_guess;
    gotoxy(13, 5);
    cout << "           ";
    gotoxy(13, 5);
}

e_answer cgame::checkAnswer()
{
    int range = (rangeMax - rangeMin) / 4;
    if (player_answer < rangeMin || player_answer > rangeMax) return OUTRANGE;
    else if (player_answer < answer - range) return FBELOW;
    else if (player_answer >= answer - range && player_answer < answer) return BELOW;
    else if (player_answer == answer) return RIGHT;
    else if (player_answer > answer && player_answer <= answer + range) return ABOVE;
    else return FABOVE;
}

void cgame::ga_PlayAgain()
{
    gotoxy(0, 5);
    cout << "Input Y to play again: ";
    char key;
    cin >> key;
    if (key != 'y' && key != 'Y')
    {
        ga_isRunning = false;
        clear_screen();
        cout << "\t\t\tTHANK FOR PLAYING\n";
        getch();
    }
    else ga_onMatch = true;
}


// ============================ ASSISTANT FUNCTION
void gotoxy(int x, int y)
{
   COORD coord;
   coord.X = x;
   coord.Y = y;
   SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), coord );
}
int random(int MIN, int MAX)
{
	return MIN + rand() % (MAX - MIN + 1);
}
void clear_screen()
{
    system("cls");
}
