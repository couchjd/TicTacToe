#include "BoardSpace.h"

BoardSpace::BoardSpace() :
   m_is_occupied(false),
   m_marker("")
{}

std::string
BoardSpace::getMarker()
{
   return m_marker;
}

void
BoardSpace::setMarker(const std::string& marker)
{
   m_marker = marker;
}

bool
BoardSpace::isOccupied()
{
   return m_is_occupied;
}

void
BoardSpace::setOccupied(const bool occupied)
{
   m_is_occupied = occupied;
}