#ifndef HGAME_H_INCLUDED
#define HGAME_H_INCLUDED

enum e_answer
{
    FBELOW, BELOW, RIGHT, ABOVE, FABOVE, OUTRANGE
};

class cgame
{
    public:
        void ga_Init();
        void ga_ChooseLevel();
        void ga_Prepare();
        void ga_GetInput();
        void ga_Calculate();
        void ga_Draw();
        void ga_PlayAgain();
        bool ga_isRunning;
        bool ga_onMatch;
    private:
        int rangeMin;
        int rangeMax;
        int player_answer;
        int answer;
        int num_guess;
        bool isPlayer;
        int botMin;
        int botMax;

        e_answer reply;
        e_answer checkAnswer();
};

void gotoxy(int x, int y);
int random(int MIN, int MAX);
void clear_screen();

#endif // HGAME_H_INCLUDED
