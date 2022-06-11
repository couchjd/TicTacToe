#pragma once
#include "GameBoard.h"

class Game
{
public:
   Game();
   ~Game();

   void run();
   int getInput(bool& illegal_move);

private:
   void init();
   void getBoardDimensions();
   
   bool m_game_over;
   bool m_player_turn;

   GameBoard* m_game_board;

};