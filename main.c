#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void menu(char *userChoice, int *wins, int *losses);
void printStartMenu();
void printRules();
void printStats(int wins, int losses);
void mainGameLogic(char *userChoice, int *wins, int *losses);
void resetBuffer(char *userChoice);
FILE* handleUserStatsFile();
void writeStats(FILE *stats, int wins, int losses);
void readStats(FILE *stats, int *wins, int *losses);
int dealCard();
void dealCardToPlayer(int *playerCards, int *playerCardCount);
void dealCardToDealer(int *dealerCards, int *dealerCardCount);
int calculateHandValue(int *cards, int cardCount);

int main() {
    srand(time(NULL));  // Seed the random number generator
    int wins = 0, losses = 0;
    FILE *userStats = handleUserStatsFile(); // pointer to the address of the file where stats are stored
    char *userChoice = malloc(5 * sizeof(char)); // user choice allocated on the heap to be referenced throughout the program
    menu(userChoice, &wins, &losses);  // Pass wins and losses as pointers to modify them
    free(userChoice);  // Deallocate memory to prevent memory leak
    fclose(userStats); // Close the stats file to prevent memory leak
    return 0;
}

FILE* handleUserStatsFile() {
    FILE *stats = fopen("stats.txt", "a+");
    if (stats == NULL) {
        perror("Error opening file");
    }
    return stats;
}

void writeStats(FILE *stats, int wins, int losses) {
    fprintf(stats, "Wins: %d\nLosses: %d\n", wins, losses);
}

void readStats(FILE *stats, int *wins, int *losses) {
    rewind(stats); // Reset the cursor back to the top of the file
    fscanf(stats, "Wins: %d\nLosses: %d", wins, losses);
}

void printStats(int wins, int losses) {
    printf("Wins: %d, Losses: %d\n", wins, losses);
}

void menu(char *userChoice, int *wins, int *losses) {
    int userSelecting = 1;
    while (userSelecting) {  // Infinite loop to keep user here
        printStartMenu();
        fgets(userChoice, 5, stdin); // Use fgets to read input (to handle line breaks)
        resetBuffer(userChoice);  // Clear the buffer after input
        switch (userChoice[0]) {
            case '1':
                printRules();
                break;
            case '2':
                printStats(*wins, *losses);  // Dereference the pointer to get values
                break;
            case '3':
                mainGameLogic(userChoice, wins, losses);  // Pass wins and losses as pointers
                break;
            case '4':
                printf("Have a nice day, we look forward to seeing you again.\n");
                return;
            default:
                printf("Invalid choice.\n");
                break;
        }
    }
}

void printStartMenu() {
    printf("Welcome to BlackJack, are you ready to test your luck today?\n");
    printf("1. See Rules\n");
    printf("2. See Stats\n");
    printf("3. Start Game\n");
    printf("4. Exit\n");
}

void mainGameLogic(char *userChoice, int *wins, int *losses) {
    int playerCards[10] = {0};  // Player's hand (array of cards)
    int playerCardCount = 0;  // Counter for the number of cards the player has
    int dealerCards[10] = {0};  // Dealer's hand (array of cards)
    int dealerCardCount = 0;  // Counter for the number of cards the dealer has

    // Deal initial cards to both player and dealer
    dealCardToPlayer(playerCards, &playerCardCount);
    dealCardToPlayer(playerCards, &playerCardCount);
    dealCardToDealer(dealerCards, &dealerCardCount);
    dealCardToDealer(dealerCards, &dealerCardCount);

    printf("Enter \"menu\" to return to the main menu.\n");

    do {
        printf("Your cards: ");
        for (int i = 0; i < playerCardCount; i++) {
            printf("%d ", playerCards[i]);
        }
        printf("\nDealer's cards: %d (One card face-up)\n", dealerCards[0]);

        printf("Enter 'h' to hit, 's' to stand, or 'menu' to return to the menu:\n");
        fgets(userChoice, 5, stdin); // Use fgets to read input
        resetBuffer(userChoice);  // Clear the buffer after input

        if (userChoice[0] == 's' || userChoice[0] == 'S') {
            printf("You stand.\n");

            int playerHandValue = calculateHandValue(playerCards, playerCardCount);
            int dealerHandValue = calculateHandValue(dealerCards, dealerCardCount);

            printf("Your total value: %d\n", playerHandValue);
            printf("Dealer's total value: %d\n", dealerHandValue);

            if (playerHandValue > 21) {
                printf("You bust! Dealer wins.\n");
                (*losses)++;
            } else if (dealerHandValue > 21 || playerHandValue > dealerHandValue) {
                printf("You win!\n");
                (*wins)++;
            } else if (dealerHandValue > playerHandValue) {
                printf("Dealer wins.\n");
                (*losses)++;
            } else {
                printf("It's a tie!\n");
            }

            break;  // End the game loop if player stands
        } else if (userChoice[0] == 'h' || userChoice[0] == 'H') {
            dealCardToPlayer(playerCards, &playerCardCount);  // Player hits, so deal another card
            printf("You hit. Your new cards: ");
            for (int i = 0; i < playerCardCount; i++) {
                printf("%d ", playerCards[i]);
            }
            printf("\n");
        } else if (strcmp("menu", userChoice) == 0) {
            return;  // Return to the main menu if the user types "menu"
        } else {
            printf("Error: Invalid input.\n");
        }

    } while (1);
}

void printRules() {
    printf("Blackjack rules:\n");
    printf("1. The goal is to get as close to 21 points as possible without exceeding it.\n");
    printf("2. Face cards (Jack, Queen, King) are worth 10 points.\n");
    printf("3. Aces can be worth either 1 or 11 points, depending on what is more beneficial.\n");
    printf("4. Aces can only be counted as 11 if it doesn't cause the player to bust (go over 21).\n");
    printf("5. The player is dealt two cards, and the dealer is dealt two cards (one face-up, one face-down).\n");
    printf("6. The player can choose to 'hit' (draw another card) or 'stand' (end their turn).\n");
    printf("7. The dealer must hit if their score is less than 17.\n");
}

void resetBuffer(char *userChoice) {
    memset(userChoice, 0, 5);  // Reset buffer to avoid leftovers
}

int dealCard() {
    int card = (rand() % 13) + 1;  // Generate a random card value (1-13)
    return (card > 10) ? 10 : card;  // Face cards = 10
}

void dealCardToPlayer(int *playerCards, int *playerCardCount) {
    playerCards[*playerCardCount] = dealCard();
    (*playerCardCount)++;
}

void dealCardToDealer(int *dealerCards, int *dealerCardCount) {
    dealerCards[*dealerCardCount] = dealCard();
    (*dealerCardCount)++;
}

int calculateHandValue(int *cards, int cardCount) {
    int totalValue = 0;
    int aceCount = 0;

    for (int i = 0; i < cardCount; i++) {
        totalValue += cards[i];
        if (cards[i] == 1) {
            aceCount++;  // Count the number of Aces
        }
    }

    // Adjust for Aces being worth 11 if possible
    while (totalValue <= 11 && aceCount > 0) {
        totalValue += 10;
        aceCount--;
    }

    return totalValue;
}
