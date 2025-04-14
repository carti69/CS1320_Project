#include <stdio.h>

int userChoice; //user choice is in heap so it can be refrenced throughout program
void printStartMenu(int userChoice);
void printRules();
void printStats();
void mainGameLogic(int userChoice);

int main(){
  printStartMenu(userChoice);
  return 0;
}

void printStartMenu(int userChoice){
  printf("Welcome to BlackJack, are you ready to test your luck today? \n");
  printf("1.See Rules \n");
  printf("2.See stats \n");
  printf("3.Start Game \n");
  userChoice = getchar();
  switch (userChoice) { //doesnt work buffer read error
    case 1:
     printRules();
      break;
    case 2:
     printStats();
      break;
    case 3:
      mainGameLogic(userChoice);
      break;
    default:
      printf("invalid choice \n");
      break;
  }
}

void mainGameLogic(int userChoice){
  do{
    printf("enter a letter \n");
    userChoice = getchar();
    if(userChoice == 's' || userChoice == 'S'){
      printf("you stand \n");
    }
    else if (userChoice == 'h' || userChoice == 'H') {
      printf("you hit\n");
    }
    else {
      printf("error");
    }
  }while(userChoice != 'e' || userChoice != 'E');
}
void printRules(){
  printf("rules go here");
}
void printStats(){
  printf("states go here but function is a maybe \n");
}
