#include "GameBoard.h"

#include <iomanip>
#include <iostream>

#include <stdlib.h>

GameBoard::GameBoard(int width, int height, int win_length) :
   m_filled_spaces(0),
   m_spaces_count(width * height),
   m_width(width),
   m_height(height),
   m_win_length(win_length),
   m_spaces(nullptr)
{
   initBoard();
}

GameBoard::~GameBoard()
{
   delete[] m_spaces;
   m_spaces = nullptr;
}

void
GameBoard::initBoard()
{
   m_spaces = new BoardSpace[m_height * m_width];

   int marker = 0;

   for (int x = 0; x < m_height; x++)
   {
      for (int y = 0; y < m_width; y++)
      {
         BoardSpace* space = m_spaces + (m_width * x + y);
         marker = ((m_width * x) + y) + 1;
         space->setMarker(std::to_string(marker));
      }
   }

   m_format_spaces = std::to_string(marker + 1).length();
}

void
GameBoard::initBoard(int x, int y, int length)
{
   m_width = x;
   m_height = y;
   m_win_length = length;
   initBoard();
}

bool 
GameBoard::isBoardFull()
{
   return m_spaces_count == m_filled_spaces;
}

void
GameBoard::printBoard(const bool player, bool running)
{
   system("cls");

   for (int x = 0; x < m_height; x++)
   {
      for (int y = 0; y < m_width; y++)
      {
         BoardSpace* space = m_spaces + (m_width * x + y);
         std::string marker = " ";
         
         if (space)
         {
            marker = space->getMarker();
         }
         
         std::cout << std::setw(m_format_spaces) << marker << (y < m_width ? '|' : '\n');
      }
      std::cout << '\n';
      if (x < m_height - 1)
      {
         for (int z = 0; z < m_width * (m_format_spaces + 1); z++)
         {
            std::cout << "-";
         }
      }
      std::cout << '\n';
   }

   if (!running && isBoardFull())
   {
      system("cls");
      std::cout << "No winner." << std::endl;
      return;
   }

   if (running)
   {
      std::cout << (!player ? "Player 1 " : "Player 2 ") << "choose a space: ";
   }
   else
   {
      std::cout << (!player ? "Player 1 " : "Player 2 ") << "wins!";
   }
}

bool 
GameBoard::setBoardSpace(
   const int space_number,
   const std::string& value)
{
   BoardSpace* board_space = m_spaces + space_number;
   bool is_occupied = board_space->isOccupied();
   if (!is_occupied)
   {
      board_space->setMarker(value);
      board_space->setOccupied(true);
   }

   return is_occupied;
}

bool
GameBoard::checkBoard(bool& player, const int board_space)
{
   std::string marker = !player ? "X" : "O";
   
   bool is_winner = checkHorizontal(marker, board_space);
   
   if (!is_winner)
   {
      is_winner = checkVertical(marker, board_space);
   }
   
   if (!is_winner)
   {
      is_winner = checkDiagonal(marker, board_space);
   }

   return is_winner;
}

bool 
GameBoard::checkHorizontal(const std::string& marker, const int board_space)
{
   bool result = false;

   int row_number = board_space / m_height;

   int count = 0;

   for (int x = 0; x < m_width; ++x)
   {
      BoardSpace* space = m_spaces + (row_number * m_width + x);
      if (space && space->getMarker() == marker)
      {
         ++count;
         
         if(count == m_win_length)
         { 
            result = true;
            break;
         }
      }
      else
      {
         count = 0;
      }
   }
   return result;
}

bool 
GameBoard::checkVertical(const std::string& marker, const int board_space)
{
   bool result = false;
   
   int row_number = board_space / m_height;
   
   int column_number = board_space - (row_number * m_width);

   int count = 0;

   for (int x = 0; x < m_height; ++x)
   {
      BoardSpace* space = m_spaces + (column_number + (x * m_width));
      if (space && space->getMarker() == marker)
      {
         ++count;

         if (count == m_win_length)
         {
            result = true;
            break;
         }
      }
      else
      {
         count = 0;
      }
   }
   return result;
}

bool GameBoard::checkDiagonal(const std::string& marker, const int board_space)
{
   bool result = checkDiagonalLtoR(marker, board_space);
   
   if (!result)
   {
      result = checkDiagonalRtoL(marker, board_space);
   }

   return result;
}

bool 
GameBoard::checkDiagonalLtoR(const std::string& marker, const int board_space)
{
   bool result = false;
   int starting_space = board_space;
   
   // Find the topmost or leftmost space for the diagonal containing the selected space
   while(true)
   {
      int row_number = starting_space / m_height;
      int column_number = starting_space - (row_number * m_width);

      if (row_number == 0 || column_number == 0)
      {
         break;
      }
      else
      {
         starting_space -= (m_width + 1);
      }
   }

   int count = 0;
   int space_number = starting_space;
   while(true)
   {
      int row_number = space_number / m_height;
      int column_number = space_number - (row_number * m_width);

      BoardSpace* space = m_spaces + space_number;
      if (space && space->getMarker() == marker)
      {
         ++count;
         
         if (count == m_win_length)
         {
            result = true;
            break;
         }
      }
      else
      {
         if (!space)
         {
            break;
         }
         count = 0;
      }
      space_number += (m_width + 1);
      
      if (space_number > m_spaces_count - 1)
      {
         break;
      }
   }

   return result;
}

bool 
GameBoard::checkDiagonalRtoL(const std::string& marker, const int board_space)
{
   bool result = false;
   int starting_space = board_space;

   // Find the topmost or rightmost space for the diagonal containing the selected space
   while (true)
   {
      int row_number = starting_space / m_height;
      int column_number = starting_space - (row_number * m_width);

      if (row_number == 0 || column_number == m_width - 1)
      {
         break;
      }
      else
      {
         starting_space -= (m_width - 1);
      }
   }

   int count = 0;
   int space_number = starting_space;
   while (true)
   {
      int row_number = space_number / m_height;
      int column_number = space_number - (row_number * m_width);

      BoardSpace* space = m_spaces + space_number;
      if (space && space->getMarker() == marker)
      {
         ++count;

         if (count == m_win_length)
         {
            result = true;
            break;
         }
      }
      else
      {
         if (!space)
         {
            break;
         }
         count = 0;
      }
      space_number += (m_width - 1);

      if (space_number > m_spaces_count - 1)
      {
         break;
      }
   }

   return result;
}

