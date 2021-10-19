//----------------------------------------------------------------------------------------------------------------------
//File Name:        CardClassType.h
//Associated file:  CardClassType.cpp
//
//----------------------------------------------------------------------------------------------------------------------
#ifndef CardClassType_h
#define CardClassType_h

#include "Standards.h"

enum suits { hearts = 3, diamonds, clubs, spades };

class Card
{
public:

  // Default constructor
  Card();

  // Overloaded constructor
  Card(suits, int);

  int GetRank() { return rank; }
  suits GetSuit() { return suit; }

  void SetRank(int tempRank);
  void SetSuit(suits tempSuit);

  void PrintCard();

  bool IsCardValid();

  // Destructor
  ~Card();

private:
  int rank;
  suits suit;
};

#endif