#pragma once

#include <string>

class BoardSpace
{
public:
   BoardSpace();

   std::string getMarker();
   void setMarker(const std::string& marker);

   bool isOccupied();
   void setOccupied(const bool is_occupied);

private:
   std::string m_marker;
   bool m_is_occupied;
};