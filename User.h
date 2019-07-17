#ifndef USER_H
#define USER_H

#include "UserInfo.h"

//Create a new user account
USER *NewUser(char *UserName, char *Password);

//Create a new contact
CONTACT *NewContact(char *UserName);

//Delete a user account
void RemoveUser(USER *u);

//Delete a contact
void RemoveContact(CONTACT *ct);

//Print the information of the user
void PrintUser(USER *u);

//Print the information of the contact
void PrintContact(CONTACT *ct);
#endif
