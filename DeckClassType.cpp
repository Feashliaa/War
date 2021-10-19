#include"DeckClassType.h"

//----------------------------------------------------------------------------------------------------------------------
// Deck - Constructs a deck of cards
//----------------------------------------------------------------------------------------------------------------------
Deck::Deck()
{
  // setting the top card counter
  topCard = 0;

  // Filling the deck of cards
  for (int i = 2; i <= 14; ++i)
  {
    // Calling card constructor based on the suits
    // After the card is constructed, set the card
    Card cardOne(hearts, i);
    cards[topCard++] = cardOne;

    Card cardTwo(diamonds, i);
    cards[topCard++] = cardTwo;

    Card cardThree(clubs, i);
    cards[topCard++] = cardThree;

    Card cardFour(spades, i);
    cards[topCard++] = cardFour;
  }
}

//----------------------------------------------------------------------------------------------------------------------
// DrawCard - Gets a card
//----------------------------------------------------------------------------------------------------------------------
Card Deck::DrawCard()
{
  // if the deck isn't empty 
  if (!isDeckEmpty())
  {
    // return the current card 
    return cards[--topCard];
  }
  else
  {
    cout << "The Deck Is Empty" << endl;
  }
}

//----------------------------------------------------------------------------------------------------------------------
// ShuffleDeck - Shuffles a Deck of cards
//----------------------------------------------------------------------------------------------------------------------
void Deck::ShuffleDeck()
{

  srand(time(nullptr));

  int randSpot;
  int randomNumber = rand() % 100;

  for (int index = 0; index < randomNumber; index++)
  {
    for (int i = 0; i < MAX; i++)
    {
      randSpot = rand() % MAX;
      swap(cards[i], cards[randSpot]);
    }
  }

}

//----------------------------------------------------------------------------------------------------------------------
// Swap - Swaps the cards
//----------------------------------------------------------------------------------------------------------------------
void Deck::Swap(Card& first, Card& second)
{
  Card temp;

  temp = first;
  first = second;
  second = temp;
}

//----------------------------------------------------------------------------------------------------------------------
// isDeckEmpty - Checks if the deck of cards is empty
//----------------------------------------------------------------------------------------------------------------------
bool Deck::isDeckEmpty()
{
  // return true if the top card is less than or equal to 0
  return (topCard <= 0);
}

//----------------------------------------------------------------------------------------------------------------------
// RefreshTopCard - Resets the top card counter
//----------------------------------------------------------------------------------------------------------------------
void Deck::RefreshTopCard()
{
  topCard = MAX;
}

//----------------------------------------------------------------------------------------------------------------------
// ~Deck - Deck destructor
//----------------------------------------------------------------------------------------------------------------------
Deck::~Deck()
{

}