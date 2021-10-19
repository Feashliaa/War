//----------------------------------------------------------------------------------------------------------------------
//File Name:        DeckClassType.h
//Associated file:  DeckClassType.cpp
//
//----------------------------------------------------------------------------------------------------------------------
#ifndef DeckClassType_h
#define DeckClassType_h
const int MAX = 52;

#include "CardClassType.h"

class Deck
{
public:

  Deck();

  void ShuffleDeck();

  void Swap(Card& first, Card& second);

  bool isDeckEmpty();

  Card DrawCard();

  void RefreshTopCard();

  ~Deck();

private:

  Card cards[MAX];
  int topCard;

};
#endif