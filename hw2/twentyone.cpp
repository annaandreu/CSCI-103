/*******************************************************************************
 * CS 103 Twenty-One (Blackjack) PA 2
/******************************************************************************/

// Add other #includes if you need
#include <iostream>
#include <cstdlib>

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
  int j;
  int temp;
  for (int k= 0; k < NUM_CARDS; k++){ // initialize array cards 0-51
    cards[k] = k;
  }

   for (int i = NUM_CARDS -1 ; i >= 1; i--){ // randomize deck
    j= rand() % (i+1);
    temp= cards[i]; 
		cards[i]= cards[j];
		cards[j]= temp; 
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
  //for _? cards 
  if (id % 13 == 0 && id < 60) { // 0, 13, 26, 39
    cout << "2-" ;
  }

  else if (id % 13 == 1 && id < 60){ // 2nd row
    cout << "3-" ;
  }
  else if (id % 13 == 2 && id < 60){ // third 
    cout << "4-";
  }
  else if (id % 13 == 3 && id < 60){ // etc
    cout << "5-";
  }
  else if (id % 13 == 4 && id < 60){
    cout << "6-";
  }
  else if (id % 13 == 5 && id < 60){
    cout << "7-";
  }
  else if (id % 13 == 6 && id < 60){
    cout << "8-";
  }
  else if (id % 13 == 7 && id < 60){
    cout << "9-";
  }
  else if (id % 13 == 8 && id < 60){
    cout << "10-";
  }
  else if (id % 13 == 9 && id < 60){
    cout << "J-";
  }
  else if (id % 13 == 10 && id < 60){
    cout << "Q-";
  }
  else if (id % 13 == 11 && id < 60){
    cout << "K-";
  }
  else if (id % 13 == 12 && id < 60){
    cout << "A-";
  }

  // for ?_ cards
  if (id >= 0 && id <= 12){
    cout << "H" ;
  }
  else if (id >= 13 && id <= 25){
    cout << "S" ;
  }
  else if (id >= 26 && id <= 38){
    cout << "D" ;
  }
  else if (id >= 39 && id <= 51){
    cout << "C" ;
  }
  cout << " " ;
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id)
{
  /******** You complete ****************/
  int value; 
  if (id % 13 == 12){ // if ace 
    value= 11; 
  }
  else if (id % 13 > 8 ){ // if face card not ace 
    value= 10; 
  }
  else { // any number card 
    value= (id % 13) +2 ;
  }
  return value;

}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards) 
{
  /******** You complete ****************/
  for (int y = 0; y < numCards +1; y++){
    printCard(hand[y]); 
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
  int sum = 0; 
  int aceCount= 0;

  for (int s= 0; s < numCards; s++){
    if (cardValue(hand[s]) == 11 && sum + 11 <= 21){ // if ace and sum+11 <= 21
      sum+= cardValue(hand[s]); // add 11
      aceCount++; // only for aces worth 11 
    }
    else if (cardValue(hand[s]) == 11 && sum + 11 > 21){ // if ace and sum+11 > 21
      sum++; // add one
    }

    else if (sum <= 21){ // if not ace and sum less than 21 add to sum
      sum+= cardValue(hand[s]); 
    }
  }
  // if after adding all cards sum > 21 and there are aces with value 11 in hand 
  for (int a= 0; a < numCards; a++){ 
    if (sum > 21 && aceCount > 0){
    sum= sum - 10; // make ace worth 1 
    aceCount--; 
    }
    else { // if no aces or sum <= 21
      break; 
    }

  }

  return sum; 
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
  int dhand[9] {60, 60, 60, 60, 60, 60, 60, 60, 60};
  int phand[9];
  //---------------------------------------
  // Do not change this code -- End
  //---------------------------------------

  /******** You complete ****************/
  bool repeat = true; 

  while (repeat){ 
    shuffle(cards); // shuffle/randomize the deck 


    for(int t=0; t < 2; t++){ // starting hand alternate btwn player & dealer
        phand[t] = cards[2*t]; // 1 card player, 2 card assigned to player hand array
        dhand[t] = cards[2*t+1]; // 1 card dealer, 2 card assigned to dealer hand array
    }

    cout << "Dealer: ? " ; // first dealer's card 'dhand[0]' hidden
    printCard(dhand[1]); // display dealer's second card 
    cout << endl;
    
    cout << "Player: " ; // print both player's drawn cards 
    printCard(phand[0]); 
    printCard(phand[1]);
    cout << endl;

    char player_choice; // cin >> h or s 
    int Pnumcards= 2; // current player num cards 
    int Dnumcards= 2; // current dealer num cards
    int Tnumcards= 4; 


    ////////// PLAYER'S TURN(S)

    while(getBestScore(phand, Pnumcards) <= 21) { // while plauyer sum not greater than 21,, ask h or s
      
      if (getBestScore(phand, Pnumcards) == 21){ // if 21 exit loop,, dealer's turn
        break;
      }
      
      cout << "Type 'h' to hit and 's' to stay: " << endl; 
      cin >> player_choice; 


      if (player_choice == 'h') { // more cards
        phand[Pnumcards]= cards[Tnumcards]; // even numbers in cards array ex. phand[2]= cards[4] 
        cout << "Player: " ; 
        printHand(phand, Pnumcards); 
        Pnumcards++; 
        Tnumcards++;
      }
      else { // player stands,, dealer's turn 
        break; 
      }

      if (getBestScore(phand, Pnumcards) > 21){ // if over 21 
        cout << "Player busts" << endl; 
        cout << "Lose " ; // print player card sum and dealer card sum
        cout << getBestScore(phand, Pnumcards) << " " << getBestScore(dhand, Dnumcards) << endl; 
        break;
      }
    } // while loop 


  ////////// DEALER'S TURN(S)

    while (getBestScore(dhand, Dnumcards) <= 21){
      if (getBestScore(dhand, Dnumcards) < 17){ // less than 17 dealer hits
        dhand[Dnumcards] = cards[Tnumcards]; // odd numbers in cards array 
        Dnumcards++;
        Tnumcards++;
      } 
      else { // score > 17,, dealer stands 
      break;
      }
    } // while loop2

  ////////// WIN / LOSE
    // Tie
    if (getBestScore(phand, Pnumcards) == getBestScore(dhand, Dnumcards) && getBestScore(phand, Pnumcards) <= 21){
      cout << "Dealer: " ; 
      printHand(dhand, Dnumcards);
      cout << "Tie " << getBestScore(phand, Pnumcards) << " " << getBestScore(dhand, Dnumcards) << endl;
    }

      // player looses 

    // player busts
    else if (getBestScore(phand, Pnumcards) > 21){ // over 21 
        // already accounted for
    }
    // dealer better score
    else if (getBestScore(phand, Pnumcards) < getBestScore(dhand, Dnumcards) && getBestScore(dhand, Dnumcards) <= 21){
        cout << "Dealer: " ; 
        printHand(dhand, Dnumcards);
        cout << "Lose " << getBestScore(phand, Pnumcards) << " " << getBestScore(dhand, Dnumcards) << endl;
    }

      // player wins

    // dealer busts
    else if (getBestScore(dhand, Dnumcards) > 21){
    cout << "Dealer: " ; 
    printHand(dhand, Dnumcards);
    cout << "Dealer Busts" << endl;
    cout << "Win " << getBestScore(phand, Pnumcards) << " " << getBestScore(dhand, Dnumcards) << endl;
    } 
    // player higher score 
    else if (getBestScore(phand, Pnumcards) > getBestScore(dhand, Dnumcards) && getBestScore(phand, Pnumcards) <= 21){
      cout << "Dealer: " ; 
      printHand(dhand, Dnumcards); 
      cout << "Win " << getBestScore(phand, Pnumcards) << " " << getBestScore(dhand, Dnumcards) << endl;
    }

    cout << "" << endl; 
    cout << "Play again? [y/n]" << endl;
    char play; 
    cin >> play; 
    if( play != 'y'){
      repeat = false;
    }      
    
}


  return 0;
}
