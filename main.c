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
