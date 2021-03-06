/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA
 * Name: Aidan McAlaine
 * USC email: amcalain@usc.edu
 * Comments (you want us to know):
 *
 *
 ******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'};
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  /******** You complete ****************/
  
  //declare array 
  for (int i = 0; i < 52; i++) {
    cards[i] = i; 
  }
  //shuffle the deck
  for (int i = NUM_CARDS-1; i > 0; i--) {
    int j = rand() % (i+1); 
    int temp = cards[i]; 
    cards[i] = cards[j]; 
    cards[j] = temp; 
  } 
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  /******** You complete ****************/
  char classOfCards; 
  if (id <= 12) {
    classOfCards = suit[0]; 
  }
  else if (id <= 25) {
    classOfCards = suit[1]; 
  }
  else if (id <= 38) {
    classOfCards = suit[2]; 
  }
  else {
    classOfCards = suit[3]; 
  }
  cout << type[id % 13] << "-" << classOfCards;
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  int num = id % 13; 
  //check face cards 
  if (num >= 9 && num <= 11) {
    return 10; 
  }
  if (num == 12) {
    return 11; 
  }
  
  //check other cards
  for (int i = 0; i <= 12; i++) {
    if (i == num) {
      //declare sstream
      stringstream str;
      str << type[i];
      
      int casted; 
      str >> casted; 
      return casted; 
    }
  }

}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
  /******** You complete ****************/
  for (int i = 0; i < numCards; i++) {
    printCard(hand[i]); 
    cout << " "; 
  }
  cout << endl; 

}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards)
{
  /******** You complete ****************/
  int total = 0; 
  for (int i = 0; i < numCards; i++) {
    total += cardValue(hand[i]); 
  }  
  //check for Aces 
  if (total > 21) {
    for (int i = 0; i < numCards; i++) {
      if (cardValue(hand[i]) == 11) {
        total -= 10; 
      }
      if (total == 21) {
        return total; 
      }
    }
  }
  return total; 
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{
  //---------------------------------------
  // Do not change this code -- Begin
  //---------------------------------------
  if(argc < 2){
    cout << "Error - Please provide the seed value." << endl;
    return 1;
  }
  int seed = atoi(argv[1]);
  srand(seed);

  int cards[52];
  int dhand[9];
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  
  string userRequest = "y"; 
  while (userRequest != "n") {
    
    //shuffle and declare variables
    shuffle(cards);
    int playerCards = 0; 
    int dealerCards = 0;  
    int playerValue = 0; 
    int dealerValue = 0; 
    
    //deal first 4 cards and add 2 to each deck 
    phand[0] = cards[0]; 
    dhand[0] = cards[1]; 
    phand[1] = cards[2]; 
    dhand[1] = cards[3]; 
    playerCards += 2; 
    dealerCards += 2; 
    
    //prompt
    cout << "Dealer: ? "; 
    printCard(dhand[1]);
    cout << "\n";  
    cout << "Player: "; 
    printHand(phand, playerCards);   
    char move = ' '; 
    
    while(getBestScore(phand, playerCards) < 21) {
      cout << "Type 'h' to hit and 's' to stay: " << endl; 
      cin >> move; 
      if (move == 'h') {
        phand[playerCards] = cards[2+playerCards]; 
        //increment the player's cards
        playerCards++; 
        cout << "Player: "; 
        printHand(phand, playerCards); 
      }
      else {
        break; 
      }
    }
    if (getBestScore(phand, playerCards) > 21) {
      //Player Bust 
      cout << "Player busts" << endl; 
      cout << "Lose ";
      cout << getBestScore(phand, playerCards) << " "; 
      cout << getBestScore(dhand, dealerCards) << endl;
      cout <<"\n"; 
    }
    else if (getBestScore(phand, playerCards) <= 21) {
      //player did not bust
      while (getBestScore(dhand, dealerCards) < 17) {
        //while dealer's count is under 17
        dhand[dealerCards] = cards[dealerCards + playerCards]; 
        dealerCards++; 
      }
      cout << "Dealer: "; 
      printHand(dhand, dealerCards);  
      if (getBestScore(dhand, dealerCards) > 21) {
        //Dealer
        cout << "Dealer busts" << endl; 
        cout << "Win " << getBestScore(phand, playerCards); 
        cout << " " << getBestScore(dhand, dealerCards) << endl; 
        cout << "\n"; 
      }
    
      else {
        //no bust, player score trumps dealer score 
        if (getBestScore(phand, playerCards) > getBestScore(dhand, dealerCards)) {
          cout << "Win " << getBestScore(phand, playerCards);
          cout << " " << getBestScore(dhand, dealerCards) << endl;
          cout << "\n"; 
        }
        //no bust, dealer score trumps player score
        else if (getBestScore(phand, playerCards) < getBestScore(dhand, dealerCards)) {
          cout << "Lose " << getBestScore(phand, playerCards); 
          cout << " " << getBestScore(dhand, dealerCards) << endl;
          cout << "\n"; 
        }
        else {
          //Tie
          cout <<"Tie " << getBestScore(phand, playerCards); 
          cout << " " << getBestScore(dhand, dealerCards) << endl;
          cout << "\n"; 
        }
      }
    }
    //Prompt to play again 
    cout << "Play again? [y/n]" << endl; 
    cin >> userRequest;  
    }
    return 0;
  }
 



