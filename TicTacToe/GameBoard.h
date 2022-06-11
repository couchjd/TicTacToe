#pragma once

#include "BoardSpace.h"

class GameBoard
{
public:
   GameBoard(int width, int height, int win_length);

   ~GameBoard();

   bool isBoardFull();
   
   void printBoard(const bool player, bool game_over);
   
   bool setBoardSpace(
      const int space_number,
      const std::string& value);

   bool checkBoard(bool& player, const int board_space);

   bool checkHorizontal(const std::string& marker, const int board_space);
   
   bool checkVertical(const std::string& marker, const int board_space);
   
   bool checkDiagonal(const std::string& marker, const int board_space);

   bool checkDiagonalLtoR(const std::string& marker, const int board_space);

   bool checkDiagonalRtoL(const std::string& marker, const int board_space);

   void initBoard(int x, int y, int length);

private:
   void initBoard();

   BoardSpace* m_spaces;

   int m_filled_spaces;
   int m_spaces_count;
   int m_width;
   int m_height;
   int m_win_length;
   int m_format_spaces;
};
