#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(char userChoice []);
void printStartMenu();
void printRules();
void printStats();
void mainGameLogic(char userChoice []);
void resetBuffer(char userChoice []);

int main(){
  char *userChoice = malloc(5 * sizeof(char));// user choice allocated on heap to be refrenced throughout program
  menu(userChoice);
  free(userChoice);
  return 0;
}

void menu(char *userChoice){
  int userSelecting = 1;
    while(userSelecting){ 
      printStartMenu();
      scanf("%s", userChoice);
      printf("buffer is currently (%s)\n",userChoice);
      switch (userChoice[0]) { 
        case '1':
          resetBuffer(userChoice);
          printRules();
          break;
        case '2':
          resetBuffer(userChoice);
          printStats();
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
void printStats(){
  printf("states go here but function is a maybe \n");
}
void resetBuffer(char *userChoice){
  memset(userChoice,0,5);
} // reset buffer
