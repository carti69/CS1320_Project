#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu(char *userChoice ,int *playerHand, int *playerCardCount, int *dealerHand, int *dealerCardCount);
void printStartMenu();
void printRules();
void printStats();
void mainGameLogic(char userChoice [], int *playerHand,int playerCardCount, int *dealerHand, int dealerCardCount);
void resetBuffer(char userChoice []);
void resetHand(int *Hand,int *cardCount);
FILE* handleUserStatsFile();
void writeStats(FILE *stats);
void readStats(FILE *stats,int *wins, int *losses);
int dealCard();
int calculateHandValue(int *hand, int cardCount);
void displayHand(int *hand,int cardCount, const char *who);
int initializeDealerHand(int *dealerHand, int dealerCardCount);
int checkBust(int playerValue, int dealerValue);
int checkWin(int playerValue, int dealerValue);
void InitializeHands(int *playerHand, int *dealerHand, int *playerCardCount, int *dealerCardCount);

const int MAX_CARDS = 10;
int wins = 0, losses = 0;


int main(){

  srand(time(NULL));
  int *playerHand = malloc(MAX_CARDS * sizeof(int));//player hand
  int *dealerHand = malloc(MAX_CARDS * sizeof(int));//dealer hand
  int playerCardCount = 0;          // Number of cards the player has
  int dealerCardCount = 0;

  FILE *userStats = handleUserStatsFile();//pointer to address of file where stats are stored
  char *userChoice = malloc(5 * sizeof(char));// user choice allocated on heap to be refrenced throughout program and to be able to clear buffer easier
  menu(userChoice, playerHand, &playerCardCount, dealerHand, &dealerCardCount);
  //deallocate memory to prevent memory leak
  free(playerHand);
  free(dealerHand);
  free(userChoice);
  fclose(userStats);
  return 0;

}//end of main


FILE* handleUserStatsFile(){//creates file not file does not exist and also returns pointer to the file
  FILE *stats = fopen("stats.txt","a+");
  if(stats == NULL){
    perror("error opening file");
  }
  return stats;
}
void writeStats(FILE *stats){//writes to the file
  fprintf(stats,"Wins: %d\nLosses: %d\n",wins,losses);
}
void readStats(FILE *stats,int *wins, int *losses){//returns values from file and assigns it to values
  rewind(stats); //rewind is used to reset the cursor back to the top of the file
  fscanf(stats,"Wins: %d\nLosses: %d",wins,losses);
}
void printStats(){//prints stats
  printf("Wins: %d, Losses: %d\n",wins,losses);
}


void menu(char *userChoice,int *playerHand, int *playerCardCount, int *dealerHand, int *dealerCardCount){//handles menu operations
  int userSelecting = 1;
    while(userSelecting){ //infinite loop to keep user here
      printStartMenu();
      scanf("%s", userChoice);
      switch (userChoice[0]) { 
        case '1':
          resetBuffer(userChoice);
          printRules();
          break;
        case '2':
          resetBuffer(userChoice);
          readStats(handleUserStatsFile(),&wins,&losses);
          printStats();
          break;
        case '3':
          mainGameLogic(userChoice, playerHand, *playerCardCount,dealerHand, *dealerCardCount);
          break;
        case '4':
          printf("have a nice day, we look forward to seeing you again \n");
          return;
        default:
          printf("invalid choice \n");
          break;
      } 
    }
}
void printStartMenu(){
  printf("Welcome to BlackJack, are you ready to test your luck today? \n");
  printf("1.See Rules \n");
  printf("2.See stats \n");
  printf("3.Start Game \n");
  printf("4.Exit \n");
}
int checkBust(int playerValue, int dealerValue){
  if (dealerValue > 21) {
    printf("Dealer busts! You win!\n");
    wins++;
    return 1;
  }
  if (playerValue > 21) {
    printf("You bust! Dealer win!\n");
    losses++;
    return 1;
  }
  return 0;//no one bust
}
int checkWin(int playerValue, int dealerValue) {
  if (dealerValue >  playerValue) {
    printf("Dealer wins! \n");
    losses++;
    return 1;
  }
  else if (dealerValue < playerValue) {
    printf("You win! \n");
    wins++;
    return 1;
  }
  else if (dealerValue == playerValue) {
    printf("Its a tie! \n");
    return 1;
  }
  return 0;

}

void mainGameLogic(char *userChoice, int *playerHand, int playerCardCount, int *dealerHand, int dealerCardCount){
  printf("Welcome to Blackjack!\n");
  printf("if you would like to back to the menu at any time type \"menu\" \n");
  int inGame = 1;
  int currentRound = 1;
  int playerStands = 0;
  while (inGame) {
    InitializeHands(playerHand, dealerHand, &playerCardCount, &dealerCardCount);
    int dealerValue = calculateHandValue(dealerHand, dealerCardCount);
    int playerValue = calculateHandValue(playerHand, playerCardCount);
    displayHand(playerHand, playerCardCount, "Player");
    printf("Player's total value: %d\n", playerValue);
    while (currentRound) {
      resetBuffer(userChoice);
      printf("Do you want to (h)it or (s)tand? \n");
      scanf("%s", userChoice);
      if(userChoice[0] == 's' || userChoice[0] == 'S'){
        playerStands = 1;
        printf("you stand \n");
        while (dealerValue < 17) {
          printf("Dealer hits...\n");
          dealerHand[dealerCardCount++] = dealCard();
          dealerValue = calculateHandValue(dealerHand, dealerCardCount);
        }
        printf("Dealer Stands...\n");
        printf("Dealer's total value: %d\n", dealerValue);
        displayHand(dealerHand, dealerCardCount, "Dealer");
      }
      else if (userChoice[0] == 'h' || userChoice[0] == 'H') {
        printf("you hit\n");
        playerHand[playerCardCount++] = dealCard();
        playerValue = calculateHandValue(playerHand,playerCardCount);
        displayHand(playerHand, playerCardCount, "Player");
        printf("Player's total value: %d\n", playerValue);
      }
      else if (strcmp("menu", userChoice) == 0) {
        return;
      }
      else {
        printf("invalid choice please hit or stand \n");
      }
      if(checkBust(playerValue, dealerValue)) {
        break;
      }
      if (playerStands && dealerValue >= 17) {
        if (checkWin(playerValue, dealerValue)) {
          break;
        }
      }
    }//end of current round while
    resetHand(playerHand,&playerCardCount);
    resetHand(dealerHand, &dealerCardCount);
    int debatingLifeChoices = 1;
    while (debatingLifeChoices) {
      resetBuffer(userChoice);
      printf("Would you like to play again? (y)es or (n)o\n");
      scanf("%s", userChoice);
      if (userChoice[0] == 'y' || userChoice[0] == 'Y') {
        currentRound = 1;
        debatingLifeChoices = 0;
      }
      else if (userChoice[0] == 'n' || userChoice[0] == 'N') {
        inGame = 0;
        debatingLifeChoices = 0;
      }
      else {
        printf("invalid choice please type (y)es or (n)o\n");
      }//conditional
    }//exit debating while
  }//exit game while
}//end main game logic function
void printRules() {
  printf("\n=== Blackjack Rules ===\n");
  printf("1. The goal is to get as close to 21 as possible, without going over.\n");
  printf("2. Number cards (2-10) are worth their face value. Face cards (Jack, Queen, King) are worth 10. Aces are worth 1 or 11.\n");
  printf("3. Both you and the dealer are dealt two cards at the start. One of the dealer's cards is hidden.\n");
  printf("4. On your turn, you can choose to 'hit' (draw another card) or 'stand' (end your turn).\n");
  printf("5. If your hand exceeds 21, you bust and lose the round.\n");
  printf("6. Once you stand, the dealer reveals their hidden card and must draw cards until their total is 17 or higher.\n");
  printf("7. If the dealer busts (goes over 21), you win.\n");
  printf("8. If neither busts, whoever is closer to 21 wins. If both have the same total, it's a tie (push).\n");
  printf("9. BlackJack (Ace + 10 or face card as first two cards) is an automatic win unless the dealer also has Blackjack.\n");
  printf("=======================\n\n");
}

void resetBuffer(char *userChoice){
  memset(userChoice,0,5);
} // reset buffer
void resetHand(int *Hand,int *cardCount) {
  memset(Hand,0,MAX_CARDS*sizeof(int));
  *cardCount = 0;
}//reset the hand

int dealCard() {//helper function
  int card = (rand() % 13) + 1;
  return (card > 10) ? 10 : card;  // Face cards (Jack, Queen, King) are worth 10
}

// Function to calculate the value of a hand
int calculateHandValue(int *hand, int cardCount) {//helper function
  int value = 0;
  int aceCount = 0;
  
  for (int i = 0; i < cardCount; i++) {
      value += hand[i];
      if (hand[i] == 1) {
          aceCount++;  // Count the number of Aces
      }
  }

  // Adjust for Aces being worth 11 if possible
  while (value <= 11 && aceCount > 0) {
      value += 10;
      aceCount--;
  }

  return value;
}

// Function to display a hand
void displayHand(int *hand, int cardCount, const char *who) {
  printf("%s's cards: ", who);
  for (int i = 0; i < cardCount; i++) {
      printf("%d ", hand[i]);
  }
  printf("\n");
}
void InitializeHands(int *playerHand, int *dealerHand, int *playerCardCount, int *dealerCardCount) {
  playerHand[*playerCardCount] = dealCard();
  *playerCardCount += 1;
  playerHand[*playerCardCount] = dealCard();
  *playerCardCount += 1;
  dealerHand[*dealerCardCount] = dealCard();
  *dealerCardCount += 1;
  dealerHand[*dealerCardCount] = dealCard();
  *dealerCardCount += 1;
}