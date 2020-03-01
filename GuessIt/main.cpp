#include "hgame.h"

int main(int argc, char* argv[])
{
    cgame* game = new cgame;
    game->ga_Init();
    while (game->ga_isRunning)
    {
        game->ga_ChooseLevel();
        game->ga_Prepare();
        while (game->ga_onMatch)
        {
            game->ga_GetInput();
            game->ga_Calculate();
            game->ga_Draw();
        }
        game->ga_PlayAgain();
    }
    delete game;
    return 0;
}
