#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
using namespace std;

string str_hang[7];
int state;
vector <string> answer_list;
string s_answer;
vector <char> p_answer;
int score;
int line;
bool onMatch;
bool isRunning = false;
bool isWinning;

ifstream inFile;

void ga_Init_Game();
void ga_Load_Data();
void ga_Prepare_Game();
void ga_Draw_Game();
void ga_Event_Handle();
void ga_Check_Endgame();
void ga_Close_Game();

int random(int MIN, int MAX);
void gotoxy(int x, int y);

int main()
{
    ga_Init_Game();
    ga_Load_Data();
    while (isRunning)
    {
        ga_Prepare_Game();
        while (onMatch)
        {
            ga_Event_Handle();
            ga_Draw_Game();
        }
        ga_Check_Endgame();
    }
    ga_Close_Game();
}

void ga_Init_Game()
{
    str_hang[0] = "";
    str_hang[1] = "\n\n\n\n\n\n\t\t\t\t\t\t\t_____";
    str_hang[2] = "\n\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t_____";
    str_hang[3] = "\n\n\t\t\t\t\t\t\t  |----+\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t_____";
    str_hang[4] = "\n\n\t\t\t\t\t\t\t  |----+\n\t\t\t\t\t\t\t  |    O\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t_____";
    str_hang[5] = "\n\n\t\t\t\t\t\t\t  |----+\n\t\t\t\t\t\t\t  |    O\n\t\t\t\t\t\t\t  |   -|-\n\t\t\t\t\t\t\t  |\n\t\t\t\t\t\t\t_____";
    str_hang[6] = "\n\n\t\t\t\t\t\t\t  |----+\n\t\t\t\t\t\t\t  |    O\n\t\t\t\t\t\t\t  |   -|-\n\t\t\t\t\t\t\t  |   ( )\n\t\t\t\t\t\t\t_____";

    srand(time(NULL));

    inFile.open("wordlist.txt");
    if (!inFile)
    {
        cout << "Could not open wordlist.txt\n";
        getch();
        exit(-1);
    }
}

void ga_Load_Data()
{
    string text;
    while (inFile >> text)
    {
        answer_list.push_back(text);
    }
    if (answer_list.size() == 0)
    {
        cout << "Word list has no word\n";
        getch();
    }
    else isRunning = true;
}

void ga_Prepare_Game()
{
    state = 0;
    onMatch = true;
    line = 14;
    isWinning = false;
    s_answer = answer_list[random(0, answer_list.size() - 1)];
    score = s_answer.length();
    p_answer.clear();

    system("cls");
    gotoxy(0, 7);
    cout << "\t\t\t\t\t HANGMAN      .........\n\n";
    for (int i = 0; i < s_answer.length(); i++) cout << "_ ";
    cout << "\n\nYOUR ANSWER: ";
}

void ga_Draw_Game()
{
    gotoxy(0, 0);
    cout << str_hang[state];
}

void ga_Event_Handle()
{
    gotoxy(13, 11);
    cout << " ";
    gotoxy(13, 11);
    char answer;
    cin >> answer;
    if (answer >= 'A' && answer <= 'Z') answer += 32;

    bool check = false;
    for (int i = 0; i < p_answer.size(); i++)
    {
        if (p_answer[i] == answer)
        {
            check = true;
            break;
        }
    }
    if (check)
    {
        gotoxy(0, line);
        cout << "Your answer " << (char)(answer - 32) << " is DUPLICATED";
    }
    else
    {
        check = false;
        for (int i = 0; i < s_answer.size(); i++)
        {
            if (s_answer[i] == answer)
            {
                check = true;
                gotoxy(2 * i, 9);
                cout << (char)(answer - 32);
                score--;
            }
        }
        gotoxy(0, line);
        if (check)
        {
            cout << "Your answer " << (char)(answer - 32) << " is RIGHT";
        }
        else
        {
            cout << "Your answer " << (char)(answer - 32) << " is WRONG";
            state++;
        }
        p_answer.push_back(answer);
    }
    line++;
    if (line == 28) line = 14;
    if (score == 0)
    {
        onMatch = false;
        isWinning = true;
    }
    else if (state == 6) onMatch = false;
}

void ga_Check_Endgame()
{
    gotoxy(0, 11);
    if (isWinning) cout << "Congratulations. You win the match !!\n";
    else
    {
        cout << "You're dump !! The answer is ";
        for (int i = 0; i < s_answer.size(); i++) cout << (char)(s_answer[i] - 32);
        cout << endl;
    }
    cout << "Input Y to try again: ";
    char check;
    cin >> check;
    if (check != 'y' && check != 'Y') isRunning = false;
}

void ga_Close_Game()
{
    inFile.close();
}

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
