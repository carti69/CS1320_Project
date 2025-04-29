#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(char userChoice [],int wins, int losses);
void printStartMenu();
void printRules();
void printStats(int wins, int losses);
void mainGameLogic(char userChoice []);
void resetBuffer(char userChoice []);
FILE* handleUserStatsFile();
void writeStats(FILE *stats, int wins, int losses);
void readStats(FILE *stats, int *wins, int *losses);
int main(){  
  int wins = 0, losses = 0;
  FILE *userStats = handleUserStatsFile();//pointer to address of file where stats are stored
  char *userChoice = malloc(5 * sizeof(char));// user choice allocated on heap to be refrenced throughout program and to be able to clear buffer easier
  menu(userChoice,wins,losses);
  free(userChoice);//deallocate memory to prevent memory leak
  fclose(userStats);//deallocate points to prevent memory leak
  return 0;

}
FILE* handleUserStatsFile(){//creates file not file does not exist and also returns pointer to the file
  FILE *stats = fopen("stats.txt","a+");
  if(stats == NULL){
    perror("error opening file");
  }
  return stats;
}
void writeStats(FILE *stats,int wins,int losses){//writes to the file
  fprintf(stats,"Wins: %d\nLosses: %d\n",wins,losses);
}
void readStats(FILE *stats,int *wins, int *losses){//returns values from file and assigns it to values
  rewind(stats); //rewind is used to reset the cursor back to the top of the file
  fscanf(stats,"Wins: %d\nLosses: %d",wins,losses);
}
void printStats(int wins, int losses){//prints stats
  printf("Wins: %d, Losses: %d\n",wins,losses);
}
void menu(char *userChoice,int wins,int losses){//handles menu operations
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
          printStats(wins,losses);
          break;
        case '3':
          mainGameLogic(userChoice);
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

void mainGameLogic(char *userChoice){
  printf("enter \"menu\" to return to the main menu \n");
  do{
    resetBuffer(userChoice);
    printf("enter a letter \n");
    scanf("%s", userChoice);
    if(userChoice[0] == 's' || userChoice[0] == 'S'){
      printf("you stand \n");
    }
    else if (userChoice[0] == 'h' || userChoice[0] == 'H') {
      printf("you hit\n");
    }
    else if (strcmp("menu", userChoice) == 0) {
      return; 
    }
    else {
      printf("error \n");
    }
  }while(1);
}
void printRules(){
  printf("rules go here\n");
}
void resetBuffer(char *userChoice){
  memset(userChoice,0,5);
} // reset buffer
int dealCard() {
  int card = (rand() % 13) + 1;
  return (card > 10) ? 10 : card;  // Face cards (Jack, Queen, King) are worth 10
}

// Function to calculate the value of a hand
int calculateHandValue(int *hand, int cardCount) {
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

const int MAX_CARDS = 10; // Maximum number of cards in a hand
    srand(time(NULL));  // Initialize random number generator

    int playerHand[MAX_CARDS] = {0};  // Player's hand
    int dealerHand[MAX_CARDS] = {0};  // Dealer's hand
    int playerCardCount = 0;          // Number of cards the player has
    int dealerCardCount = 0;          // Number of cards the dealer has
    char choice[3];                   // Input choice from the player

    // Deal two cards to the player and dealer
    playerHand[playerCardCount++] = dealCard();
    playerHand[playerCardCount++] = dealCard();
    dealerHand[dealerCardCount++] = dealCard();
    dealerHand[dealerCardCount++] = dealCard();

    printf("Welcome to Blackjack!\n");

    // Player's turn
    int playerBust = 0;
    while (1) {
        printf("\nYour cards: ");
        displayHand(playerHand, playerCardCount, "Player");
        int playerValue = calculateHandValue(playerHand, playerCardCount);
        printf("Your total value: %d\n", playerValue);

        if (playerValue > 21) {
            printf("You bust! Dealer wins.\n");
            playerBust = 1;
            break;
        }

        printf("Do you want to (h)it or (s)tand? ");
        fgets(choice, sizeof(choice), stdin);
        clearBuffer();  // Clear the newline character left by fgets

        if (choice[0] == 's' || choice[0] == 'S') {
            break;  // Player stands, end the loop
        } else if (choice[0] == 'h' || choice[0] == 'H') {
            playerHand[playerCardCount++] = dealCard();  // Player hits, draw a new card
        } else {
            printf("Invalid choice. Please enter 'h' to hit or 's' to stand.\n");
        }
    }

    if (playerBust) return 0;  // End the game if player busted

    // Dealer's turn (dealer must hit if their total is less than 17)
    printf("\nDealer's cards: ");
    displayHand(dealerHand, dealerCardCount, "Dealer");
    int dealerValue = calculateHandValue(dealerHand, dealerCardCount);
    printf("Dealer's total value: %d\n", dealerValue);

    while (dealerValue < 17) {
        printf("Dealer hits.\n");
        dealerHand[dealerCardCount++] = dealCard();
        dealerValue = calculateHandValue(dealerHand, dealerCardCount);
        printf("Dealer's new total value: %d\n", dealerValue);
    }

    if (dealerValue > 21) {
        printf("Dealer busts! You win!\n");
    } else if (dealerValue > calculateHandValue(playerHand, playerCardCount)) {
        printf("Dealer wins!\n");
    } else if (dealerValue < calculateHandValue(playerHand, playerCardCount)) {
        printf("You win!\n");
    } else {
        printf("It's a tie!\n");
    }

    return 0;
