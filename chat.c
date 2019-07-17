#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void loginMenu();
void mainMenu();

int main()
{
    loginMenu();
    mainMenu();
    return 0;  
}

void loginMenu()
{
    char input[20],username[20],password[20];
    
    printf("Create account or Sign in.(Case sensitive)\n");
    fgets(input, 20, stdin);
  
    if(strcmp(input, "Create account") == 10) //Checks if they entered create account
    {
        printf("Please choose a new username.\nUsername: ");
        fgets(username,20,stdin);
        //Check if username exists, if it does asks for another username. Also check that username is less that 20 characters.
        printf("Please enter a new password.\nPassword: ");
        fgets(password,20,stdin);

    }
    else if(strcmp(input, "Sign in") == 10) //Checks if they entered sign in 
    {
        printf("Please enter the following to sign in.\nUsername: ");
        fgets(username,20,stdin);
        //Check if username exists, if not ask for another username. Also check that username is less than 20 characters.
        printf("Pasword");
        fgets(password,20,stdin);
        //Check if password matches username, if it does log in.
    }
}

void mainMenu()
{
    int choice;

    printf("Please choose what to do.\n1.Add a friend\n2.Delete a friend\n3.Message a friend\n");
    scanf(" %d", &choice);
    switch(choice){
    case 1: 
              printf("You have selected to add friend.\n");
              //Ask if correct choice, if not ask again	
              //addfriend() if yes
    break;
    case 2:
              printf("You have selected to remove a friend.\n");
              //Ask if correct choice
              //removefriend() if yes, if not ask again
    break;
    case 3:
              printf("You have selected to message a friend.\n");
              //Ask if correct choice
              printf("Please select a friend to message.\n");
    break;
    case 4:   printf("You have selected to play a game of chess with a friend.\n");
	      //Ask if correct choice
	      printf("Please select a friend to play.\n");
    break;
    }
}

void addFriend()
{
    char friend[20];
    printf("Who would you like to add");
    fgets(friend,20,stdin);
    //Check if friend is registered
    //Call function that adds friend
}
void removeFriend()
{
    char friend[20];
    printf("Who would you like to remove");
    fgets(friend,20,stdin);
    //Check if friend is registered
    //Call function that removes friend
}





































