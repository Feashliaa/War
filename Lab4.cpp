//----------------------------------------------------------------------------------------------------------------------
//Lab 4
//Name: Riley Dorrington  
//----------------------------------------------------------------------------------------------------------------------

#include "Stack.h"

enum winner { player = 1, computer = 2, tie = 3 };

// Global Boolean Flag
bool autoPlay = false;

void PrintDivider(char symbol, int amount);
void PrintCard(Card PlayerOneCard, Card PlayerTwoCard);

void DealStarterCards(Deck* TheDeckOfCards, Stack* DealStack);

void DealCardsToPlayers(Stack* DealStack, Stack* PlayerStack, Stack* ComputerStack);

void Play();

winner War(Stack* TableStack, Card PlayerCard, Card ComputerCard, 
  Stack* PlayerStack, Stack* ComputerStack, Stack* PlayerWinStack, Stack* ComputerWinStack);

bool PlayAgain();

void checkForAutoPlay();

int main(void)
{
  //----------------------------------------------------------------------------------------------------------------------
  // Playing The Game
  //----------------------------------------------------------------------------------------------------------------------
  bool playAgain = false;

  char inputChar;
  string inputString;
  cout << "Would You Like To Play The Game of War? (Y|N)" << endl;
  
  do
  {
    cin.get(inputChar);
    // If Y inputted, play game
    if (inputChar == 'y' || inputChar == 'Y')
    {
      cin.ignore();
      playAgain = true;
      Play();
    }
    else
    {
      cout << endl;
      cout << "Oh well. Thanks For Playing!" << endl;
      cout << endl;
      // set the flag to pop out of the game
      playAgain = false;
    }

  } while (playAgain);

  system("pause");

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: PrintDivider
// Description: This function is used to output a divider to the screen
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void PrintDivider(char symbol, int amount)
{
  // output the divider to the screen and output file
  std::cout << setfill(symbol) << setw(amount) << symbol << setfill(' ') << endl;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: PrintCard
// Description: This function is used to output the cards to the screen
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void PrintCard(Card PlayerOneCard, Card PlayerTwoCard)
{
  std::cout << "You:      ";
  PlayerOneCard.PrintCard();
  std::cout << "Computer: ";
  PlayerTwoCard.PrintCard();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: 
// Description: 
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void DealStarterCards(Deck* TheDeckOfCards, Stack* DealStack)
{
  // Shuffling the deck of cards
  TheDeckOfCards->ShuffleDeck();

  // While the deck of cards isn't empty
  while (!TheDeckOfCards->isDeckEmpty())
  {
    // fill the stack of cards
    DealStack->Push(TheDeckOfCards->DrawCard());
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: Play
// Description: Plays the game of war
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void Play()
{
  // outputs message
  cout << "After each round, press Enter to Play or press any key then enter, to auto play the game:" << endl;

  bool Playing = true;
  static int rounds = 1;

  // Skipping lines for readability
  cout << endl;
  cout << endl;
  cout << endl;

  do
  {
    // set the auto-play flag to false for the first run through, i.e. it auto plays 1 hand
    autoPlay = false;

    // Creating a deck of cards
    Deck* TheDeckOfCards = new Deck();
    // Instance of a stack of 52 cards
    Stack* DealStack = new Stack();

    // Two stacks of 26 cards, 1 for each player
    Stack* PlayerStack = new Stack();
    Stack* ComputerStack = new Stack();

    // Stacks dealing with game-play
    Stack* PlayerWinStack = new Stack();
    Stack* ComputerWinStack = new Stack();

    Stack* TableStack = new Stack();

    // Temp Cards
    Card TempCardType;

    // Deals the starter cards, i.e. constructs the deck
    DealStarterCards(TheDeckOfCards, DealStack);

    // Splits the cards to 2 separate stacks
    DealCardsToPlayers(DealStack, PlayerStack, ComputerStack);

    do
    {
      // While neither stack is empty, play the game
      while (!PlayerStack->IsEmpty() && !ComputerStack->IsEmpty())
      {

        // Popping cards out of each deck
        Card PlayerCard = PlayerStack->Pop();
        Card ComputerCard = ComputerStack->Pop();

        // Printing both cards to the screen
        PrintCard(PlayerCard, ComputerCard);

        // if the two cards are of equal rank
        if (PlayerCard.GetRank() == ComputerCard.GetRank())
        {

          // Pushing the two cards to the table stack
          TableStack->Push(PlayerCard);
          TableStack->Push(ComputerCard);

          // Jumping into the war function, returns an enumeration
          winner winnerOfGame = War(TableStack, PlayerCard, ComputerCard, PlayerStack, ComputerStack, PlayerWinStack, ComputerWinStack);

          // if the winner is the player
          if (winnerOfGame == player)
          {
            // Output a statement
            cout << endl;
            cout << "User won the war";
            cout << endl;
          }
          // if the winner is the computer
          else if (winnerOfGame == computer)
          {
            // Output a statement
            cout << endl;
            cout << "Computer won the war";
            cout << endl;
          }
          // if the war results in a tie
          else if (winnerOfGame == tie)
          {
            // Output a statement
            cout << endl;
            cout << "Tie" << endl;
            cout << endl;
            cout << "No one won the war";
            cout << endl;
          }
        }
        // If the player card is of a higher rank than the computer card
        else if (PlayerCard.GetRank() > ComputerCard.GetRank())
        {
          // Push the cards to players's win stack
          PlayerWinStack->Push(PlayerCard);
          PlayerWinStack->Push(ComputerCard);

          cout << endl;

          // Output a statement
          cout << "User won the round" << endl;

          cout << endl;
        }
        // If the computers card is of a higher rank than the players card
        else if (PlayerCard.GetRank() < ComputerCard.GetRank())
        {
          // Push the cards to computers's win stack
          ComputerWinStack->Push(PlayerCard);
          ComputerWinStack->Push(ComputerCard);

          cout << endl;

          // Output a statement
          cout << "Computer won the round" << endl;

          cout << endl;
        }

        if (++rounds > MAX_ROUNDS)
        {
          cout << "The Game is Infinite" << endl;
          Playing = false;
          rounds = 0;
        }
        // Checks this flag, if true, the game is auto-played, otherwise, continue to take in input
        if (!autoPlay) checkForAutoPlay();
      }

      // If the player stack, and the computer stack is empty
      if (PlayerStack->IsEmpty() && ComputerStack->IsEmpty())
      {

        // Output that both are empty
        cout << endl;
        cout << "Both the player stack, and the computer stack is empty" << endl;

        // Check if both of the win stacks are empty
        if (PlayerWinStack->IsEmpty() && ComputerWinStack->IsEmpty())
        {
          cout << endl;
          cout << "The Game Was A Tie" << endl;
          cout << endl;
          // exit the game
          Playing = false;
          break;
        }
        // check if just the players win stack is empty
        else if (PlayerWinStack->IsEmpty())
        {
          cout << endl;
          cout << "Player ran out of cards, Computer Wins The Game" << endl;
          cout << endl;
          // exit the game
          Playing = false;
          break;
        }
        // check if the just the computer win stack is empty
        else if (ComputerWinStack->IsEmpty())
        {
          cout << endl;
          cout << "Computer ran out of cards, User wins the game" << endl;
          cout << endl;
          // exit the game
          Playing = false;
          break;
        }
        // check if both are not empty
        else if (!PlayerWinStack->IsEmpty() && !ComputerWinStack->IsEmpty())
        {

          cout << endl;
          cout << "Both Win Stacks are not empty" << endl;
          cout << endl;

          // while the player win stack is not empty
          while (!PlayerWinStack->IsEmpty())
          {
            // pop the cards from the win stack, and push them into the Player stack
            PlayerStack->Push(PlayerWinStack->Pop());
          }
          // while the computer win stack is not empty
          while (!ComputerWinStack->IsEmpty())
          {
            // pop the cards from the win stack, and push them into the ComputerStack
            ComputerStack->Push(ComputerWinStack->Pop());
          }
        }
      }
      // if only the player stack is empty
      else if (PlayerStack->IsEmpty())
      {
        // if their win stack is also empty
        if (PlayerWinStack->IsEmpty())
        {
          cout << endl;
          cout << "Player is out of cards in win stack, Computer Wins The Game" << endl;
          // exit the game
          Playing = false;
        }
        // if their win stack isn't empty
        else
        {
          cout << endl;

          cout << "Giving the user cards from their win stack" << endl;

          cout << endl;
          // otherwise, while the win stack isn't empty
          while (!PlayerWinStack->IsEmpty())
          {
            // pop the cards from the win stack, and push them into the PlayerStack
            PlayerStack->Push(PlayerWinStack->Pop());
          }
        }
      }
      // if only the computers stack is empty
      else if (ComputerStack->IsEmpty())
      {
        // if their win stack is also empty
        if (ComputerWinStack->IsEmpty())
        {
          cout << endl;
          cout << "Computer is out of cards in win stack, User Wins The Game" << endl;
          Playing = false;
        }
        // if their win stack isn't empty
        else
        {
          cout << endl;

          cout << "Giving computer cards from win stack" << endl;

          cout << endl;
          // otherwise, while the win stack isn't empty
          while (!ComputerWinStack->IsEmpty())
          {
            // pop the cards from the win stack, and push them into the ComputerStack
            ComputerStack->Push(ComputerWinStack->Pop());
          }
        }
      }


      // Used to sort the cards
      nodePtr tempPtr;
      tempPtr = PlayerStack->GetTop();

      // if the top contains no value
      if (tempPtr == nullptr)
      {
        cout << endl;

        cout << "Player has no cards..." << endl;

        cout << endl;
        // exit the game
        Playing = false;
      }
      // otherwise, sort the player's stack
      else
      {
        //PlayerStack->selectionSort(tempPtr);
        PlayerStack->ShuffleStack();
      }

      tempPtr = ComputerStack->GetTop();

      // if the top contains no value
      if (tempPtr == nullptr)
      {
        cout << endl;

        cout << "Computer has no cards..." << endl;

        cout << endl;
        // exit the game
        Playing = false;
      }
      // otherwise, sort the computer's stack
      else
      {
        //ComputerStack->selectionSort(tempPtr);
        ComputerStack->ShuffleStack();
      }

      rounds = 0;

    } while (Playing); // while the game is being played

    // After the game is done being played
    // Free and Delete the lists
    DealStack->FreeTheList();
    PlayerStack->FreeTheList();
    PlayerWinStack->FreeTheList();
    ComputerStack->FreeTheList();
    ComputerWinStack->FreeTheList();
    TableStack->FreeTheList();
    delete DealStack;
    delete PlayerStack;
    delete PlayerWinStack;
    delete ComputerStack;
    delete ComputerWinStack;
    delete TableStack;

    // Refresh the deck of cards
    TheDeckOfCards->RefreshTopCard();

  } while (PlayAgain()); // while the user has said yes to play again
}


///////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: DealCardsToPlayers
// Description:     Takes the deck of cards constructed, and splits it among 2 decks of 26 cards
//                    Called once per run through the game
///////////////////////////////////////////////////////////////////////////////////////////////////
void DealCardsToPlayers(Stack* DealStack, Stack* PlayerStack, Stack* ComputerStack)
{
  // boolean flags
  bool tempFlag = true;

  Card TempCardType;

  // while the stack isn't empty
  while (!DealStack->IsEmpty())
  {
    // pops a card out of the dealer stack
    TempCardType = DealStack->Pop();
    // if flag
    if (tempFlag)
    {
      // push the popped out card into player one's stack
      PlayerStack->Push(TempCardType);
      // switch flag
      tempFlag = false;
    }
    // if not flag
    else
    {
      // push the popped out card into the computers stack
      ComputerStack->Push(TempCardType);
      // switch flag
      tempFlag = true;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: War
// Description: This function is called if the table enters a war, i.e. 
//                when the two cards played are the same.
///////////////////////////////////////////////////////////////////////////////////////////////////
winner War(Stack* TableStack, Card PlayerCard, Card ComputerCard, 
  Stack* PlayerStack, Stack* ComputerStack, Stack* PlayerWinStack, Stack* ComputerWinStack)
{
  winner whoWon = tie;

  Card playerTempCard;
  Card computerTempCard;
  Card TempPlayerCardOne;
  Card TempComputerCardOne;

  do
  {
    cout << endl;
    cout << "WAR!" << endl;
    cout << endl;
    if (!autoPlay) checkForAutoPlay();

    //If a player is out of cards, then the other player wins
    if (PlayerStack->IsEmpty() && ComputerStack->IsEmpty())
    {
      // Pop cards off of table
      ComputerCard = TableStack->Pop();
      PlayerCard = TableStack->Pop();
      whoWon = tie;
      PrintCard(PlayerCard, ComputerCard);
      break;
    }
    // if only a player is out of cards
    else if (PlayerStack->IsEmpty())
    {
      // Pop cards off of table
      ComputerCard = TableStack->Pop();
      PlayerCard = TableStack->Pop();
      cout << "User is out of cards in their hand." << endl;
      whoWon = computer;
      PrintCard(PlayerCard, ComputerCard);
      break;
    }
    // if only the computer is out of cards
    else if (ComputerStack->IsEmpty())
    {
      // Pop cards off of table
      ComputerCard = TableStack->Pop();
      PlayerCard = TableStack->Pop();
      cout << "Computer is out of cards in their hand." << endl;
      whoWon = player;
      PrintCard(PlayerCard, ComputerCard);
      break;
    }

    // Popping two cards off of the table stack
    TempComputerCardOne = TableStack->Pop();
    TempPlayerCardOne = TableStack->Pop();

    // putting 3 cards down, face down
    for (int iterator = 0; iterator < 3; iterator++)
    {
      if (PlayerStack->GetStackSize() > 1)
      {
        TableStack->Push(PlayerStack->Pop());
      }

      if (ComputerStack->GetStackSize() > 1)
      {
        TableStack->Push(ComputerStack->Pop());
      }
    }

    // Popping 1 card out of each stack, popping them to the table
    PlayerCard = PlayerStack->Pop();
    ComputerCard = ComputerStack->Pop();
    TableStack->Push(PlayerCard);
    TableStack->Push(ComputerCard);

    PrintCard(PlayerCard, ComputerCard);

  } while (PlayerCard.GetRank() == ComputerCard.GetRank()); // While the current cards are equal to each other

  // if the player card is greater than the computer card
  if (PlayerCard.GetRank() > ComputerCard.GetRank())
  {
    // push 2 cards to the player win stack
    PlayerWinStack->Push(TempComputerCardOne);
    PlayerWinStack->Push(TempPlayerCardOne);

    Card TempCard;
    // popping 2 cards off the stack
    TempCard = TableStack->Pop();
    PlayerWinStack->Push(TempCard);
    TempCard = TableStack->Pop();
    PlayerWinStack->Push(TempCard);

    // if the size of stack is greater than 0
    int sizeOfStack = TableStack->GetStackSize();
    if (sizeOfStack > 0)
    {
      cout << endl;
      cout << "Cards That Were Flipped Over" << endl;
      cout << endl;
    }
    // outputting the cards from the table stack, then pushing them into the player win stack
    for (int iterator = 0; iterator < sizeOfStack; iterator++)
    {
      TempCard = TableStack->Pop();
      TempCard.PrintCard();
      cout << endl;
      PlayerWinStack->Push(TempCard);
    }
    // set the win flag
    whoWon = player;
  }
  // if the computer's card is larger than the player's card
  else if (PlayerCard.GetRank() < ComputerCard.GetRank())
  {
    // push 2 cards to the computer win stack
    ComputerWinStack->Push(TempComputerCardOne);
    ComputerWinStack->Push(TempPlayerCardOne);

    Card TempCard;
    // popping 2 cards off the stack
    TempCard = TableStack->Pop();
    ComputerWinStack->Push(TempCard);
    TempCard = TableStack->Pop();
    ComputerWinStack->Push(TempCard);

    // if the size of stack is greater than 0
    int sizeOfStack = TableStack->GetStackSize();
    if (sizeOfStack > 0)
    {
      cout << endl;
      cout << "Cards That Were Flipped Over" << endl;
      cout << endl;
    }
    // outputting the cards from the table stack, then pushing them into the computer win stack
    for (int iterator = 0; iterator < sizeOfStack; iterator++)
    {
      TempCard = TableStack->Pop();
      TempCard.PrintCard();
      cout << endl;
      ComputerWinStack->Push(TempCard);
    }

    // setting win flag
    whoWon = computer;
  }
  // returning the win flag
  return whoWon;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: PlayAgain
// Description: Asks the user if they want to play the game again, if so, play again, otherwise, 
//                leave the game
///////////////////////////////////////////////////////////////////////////////////////////////////
bool PlayAgain()
{
  cin.ignore();
  char Choice;

  // asks the user if they want to play again
  cout << "Do you want to play war again? (Y|N)" << endl;
  
  cin >> Choice;

  // return if the choice is yes
  return(Choice == 'Y' || Choice == 'y');
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Function Name: checkForAutoPlay
// Description: Checks user input, if its anything but nothing, it will auto play the game
//
///////////////////////////////////////////////////////////////////////////////////////////////////
void checkForAutoPlay()
{
  char Choice;
  cin.get(Choice);
  // if the choice is not null
  autoPlay = (Choice != '\n');
}