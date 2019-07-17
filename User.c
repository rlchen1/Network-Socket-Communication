#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "User.h"
#include "UserList.h"

//Create a new user account
USER *NewUser(char *UserName, char *Password)
{
    USER *u;
    //int len;
    
    //Allocate memory for user account
    u = malloc(sizeof(USER));
    //If memory allocation failed, print the
    //following information
    if(u == NULL){
        printf("Memory allocation for user account failed.. \n");
        printf("Aborting.. \n");
        exit(10);
    }

    //Copy user name
    strncpy(u->UserName, UserName, 10);
    //len = strlen(UserName);
    //u->UserName[len-1] = '\0';
    //Copy password
    strncpy(u->Password, Password, 10);
    //len = strlen(Password);
    //u->Password[len-1] = '\0';
    //Default status is off-line
    u->Status = 0;
    //Deafult friend list is empty
    u->Friends = CreateCList();

    return u;
}

//Create a new contact
CONTACT *NewContact(char *UserName)
{
    CONTACT *ct;

    //Allocate memory for contact info
    ct = malloc(sizeof(CONTACT));
    //If memory allocation failed, print
    //the following information
    if(ct == NULL){
        printf("Memory allocation for contact failed..\n");
        printf("Aborting..\n");
        exit(10);
    }

    //Copy user name
    strncpy(ct->UserName, UserName, 10);
    //ct->UserName[20] = '\0';
    //Default status is offline
    ct->Status = 0;

    return ct;
}

void RemoveUser(USER *u)
{
    //Check if *u points to a valid memory address
    assert(u);
    //Delete the contact list
    DeleteCList(u->Friends);
    //Free the allocated memory
    free(u);
}

void RemoveContact(CONTACT *ct)
{
    //Check if *ct points to a valid memory address
    assert(ct);
    //Free the allocated memory
    free(ct);
}

void PrintUser(USER *u)
{
    //Check if *u points to a valid memory address
    assert(u);
    printf("UserName: %s\n", u->UserName);
    PrintCList(u->Friends);
    //printf("Password: %s\n", u->Password);
    //printf("Status: %d\n", u->Status);
}

void PrintContact(CONTACT *ct)
{
    //Check if *ct points to a valid memory address
    assert(ct);
    printf("Contact UserName: %s\n", ct->UserName);
    //printf("Status: %d\n", ct->Status);
}
