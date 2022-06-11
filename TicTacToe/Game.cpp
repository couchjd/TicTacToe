#include "Game.h"
#include <iostream>

Game::Game() :
   m_game_over(false),
   m_player_turn(false),
   m_game_board(nullptr)
{

}

Game::~Game()
{
   delete m_game_board;
}

void 
Game::init()
{
   getBoardDimensions();
}

void 
Game::getBoardDimensions()
{
   if (m_game_board)
   {
      delete m_game_board;
   }

   int x = 0;
   int y = 0;
   int length = 0;
   
   system("cls");

   std::cout << "Input board width: ";
   std::cin >> x;
   std::cout << "\nInput board height: ";
   std::cin >> y;
   std::cout << "\nInput win length: ";
   std::cin >> length;

   m_game_board = new GameBoard(x, y, length);
}

int
Game::getInput(bool& illegal_move)
{
   int input;
   std::cin >> input;
   input--;

   std::string marker = (!m_player_turn ? "X" : "O");
   illegal_move = m_game_board->setBoardSpace(input, marker);
   return input;
}

void
Game::run()
{
   getBoardDimensions();
 
   while (!m_game_over)
   {
      m_game_board->printBoard(m_player_turn, !m_game_over);

      bool illegal_move = false;
      int board_space = getInput(illegal_move);

      if (!illegal_move)
      {
         m_game_over = m_game_board->checkBoard(m_player_turn, board_space);
         
         if (m_game_over)
         {
            m_game_board->printBoard(m_player_turn, !m_game_over);
         }
         else
         {
            m_player_turn = !m_player_turn;
         }
      }
      if (m_game_over)
      {
         char new_game = ' ';
         std::cout << "\nNew game (y/n): ";
         std::cin >> new_game;

         if (new_game == 'y')
         {
            m_game_over = false;
            getBoardDimensions();
         }
      }
   }
}