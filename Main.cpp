// Names: Samuel Oseguera, Jose Arellano, Michael Santos, Arnold Rocha
// Date: 1/30/25
//Making a card game

#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>    // For time()

using namespace std;


//class for the card
class Card { // Keeps a card object
public:
  Card(string suit = "", string rank = "", int value = 0)  //constructor which inititalizes the card object
      : suit(suit), rank(rank), value(value) {}
//Getters 
  string get_suit() { return suit; }    //returns suit
  string get_rank() { return rank; }    //retyurns rank
  int get_value() { return value; }     //returns value
//Setters
  void set_suit(string new_suit) { suit = new_suit; }
  void set_rank(string new_rank) { rank = new_rank; }
  void set_value(int new_value) { value = new_value; }
//Prints the card details
  void print_card() {
    cout << rank << " of " << suit << " (Value: " << value << ")" << endl;
  }

private:
  string suit;  //stores the card suit
  string rank;  //stores the card rank
  int value;    //stores the card value
};
//constants
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};       //holds 4 possible SUITS
const string RANKS[] = {"2", "3",  "4",    "5",     "6",    "7",  "8",  //holds all RANKS
                        "9", "10", "Jack", "Queen", "King", "Ace"};
const int VALUES[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};      //assigns numerical value to each rank

Card deck[52];  //full deck of cards
int currentCardIndex = 0; //cardindex set to 0 and this keeps track of ehich card is next in the deck
bool play = true;   //control game loop
int wins = 0;       // tracks the wins
int ties = 0;       // tracks the ties
int loses = 0;      // tracks the losses
string response = ""; //stores user input


//initializing deck Function
void initializeDeck() {
  int deckIndex = 0;                                        //For loop iterates over the four suits and also the rankIndex
  for (int suitIndex = 0; suitIndex < 4; suitIndex++) {
    for (int rankIndex = 0; rankIndex < 13; rankIndex++) {
      deck[deckIndex++] = Card(SUITS[suitIndex], RANKS[rankIndex], VALUES[rankIndex]);
    }
  }
}

//shuffle deck function
// new shuffle each turn
void shuffleDeck() {
  srand((time(0)));
  for (int i = 0; i < 52; i++) {
    int index = rand() % 52;
    Card temp = deck[i];
    deck[i] = deck[index];
    deck[index] = temp;
  }
}

//deal the card 
//ensures it is dealt in order 
Card dealCard() { 
  return deck[currentCardIndex++]; 
}

//deal the cards to the player
int dealInitialPlayerCards() {  
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Your cards: ";
  card1.print_card();       //prints cards
  card2.print_card();       //prints cards
  return card1.get_value() + card2.get_value();
}
//total amount of player
int playerTurn(int playerTotal) {
  while (true) {  //loops until the payer stands or busts if total exceeds 21 the loop automatically breaks
    cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
    string action;
    getline(cin, action);
    if (action == "hit") {
      Card newCard = dealCard();
      playerTotal += newCard.get_value();
      cout << "You drew a ";
      newCard.print_card();
      if (playerTotal > 21) {
        break;
      }
    } else if (action == "stand") {
      break;
    } else {
      cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
    }
  }
  return playerTotal;
}
//dealer cards
int dealInitialDealerCards() {
  Card card1 = dealCard();
  Card card2 = dealCard();
  cout << "Dealer's cards: ";
  card1.print_card();
  card2.print_card();
  return card1.get_value() + card2.get_value(); //returns dealers total vlaue
}

int dealerTurn(int dealerTotal) { //loop for dealer, dealer must hit untiul their toal is 17
  while (dealerTotal < 17) {    //if they reach 17 or more they stop drawing
    Card newCard = dealCard();
    dealerTotal += newCard.get_value();
    cout << "Dealer drew a ";   //prints out what dealer drew
    newCard.print_card();
  }
  return dealerTotal;   //returns the dealterTotal
}

void determineWinner(int playerTotal, int dealerTotal) {  //comapres the date of the player and dealer
  cout << "Your total: " << playerTotal << endl;
  cout << "Dealer's total: " << dealerTotal << endl;
  if (playerTotal > 21) {                       
    cout << "You busted! Dealer wins." << endl;  //if player total is more than 21 dealer wins
    loses++; //losses count up
  } else if (dealerTotal > 21) {    //if dealer total is more than 21 player wins
    cout << "Dealer busted! You win." << endl;
    wins++; //wins count up
  } else if (playerTotal > dealerTotal) { //if player has more they win
    cout << "You win!" << endl;
    wins++;
  } else if (playerTotal < dealerTotal) { //if dealer had more dealer wins 
    cout << "Dealer wins!" << endl;
    loses++;
  } else {
    cout << "It's a tie!" << endl; //tie
    ties++; //ties coutn up
  }
}

int main() {
  while (play == true) { //game loop
    initializeDeck(); 
    shuffleDeck();
    int playerTotal = dealInitialPlayerCards();
    int dealerTotal = dealInitialDealerCards();
    playerTotal = playerTurn(playerTotal);
    if (playerTotal > 21) {
      cout << "You busted! Dealer wins." << endl;
      loses++;
    } else {
      dealerTotal = dealerTurn(dealerTotal);
      determineWinner(playerTotal, dealerTotal);
    }
    cout << "Play again? \n";
    getline(cin, response); //getline 
    
    if (response == "No" ){  //respose to either play again or no
      play = false;
    }
    else if (response == "Yes" ){
      play = true;
    }
    else if (response == "yes" ){
      play = true;
    }
    else if (response == "no" ){
      play = false;
    }
    else {
      cout << "Invalid input";
    }
    cout << "Wins: " << wins << " \n" << "Loses: " << loses << " \n" << "Ties: " << ties << "\n"; //keeps track of wins,losses and ties
  }
  return 0;
