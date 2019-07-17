#ifndef USERLIST_H
#define USERLIST_H

#include "UserInfo.h"
#include "User.h"

//Retrieve data from the .txt file
ULIST *RetrieveData(FILE *f);

//Check login information, returns 1
//if there's matching result; returns
//0 if password doesn't match; returns
//-1 if username is not found;
int LoginCheck(ULIST *l, char *UserName, char *Password);

//Check register information, returns 1
//if username for register is available, 
//returns 0 if the username has been used
int RegisterCheck(ULIST *l, char *UserName);

//Check if the username already exist in
//a given contact list, if yes return 1, 
//if not return 0
int ContactCheck(CLIST *cl, char *UserName);

//Allocate memory for a list of users
ULIST *CreateList(void);

//Allocate memory for contact list
CLIST *CreateCList(void);

//Deallocate memory for a list of users
void DeleteList(ULIST *l);

//Deallocate memory for contact list
void DeleteCList(CLIST *cl);

//Allocate memory for a user entry
UENTRY *CreateEntry(USER *u);

//Allocate memory for a contact entry
CENTRY *CreateCEntry(CONTACT *ct);

//Deallocate memory for a user entry
USER *DeleteEntry(UENTRY *e);

//Deallocate memory for a contact entry
CONTACT *DeleteCEntry(CENTRY *ce);

//Append a user entry to the list
void AppendEntry(ULIST *l, USER *u);

//Append a contact entry to the contact list
void AppendCEntry(CLIST *cl, CONTACT *ct);

//Delete the first entry from the list
USER *DeleteFirst(ULIST *l);

//Delete the first entry from the list
CONTACT *DeleteFirstC(CLIST *cl);

//Delete an arbitrary entry from the list
USER *RemoveEntry(ULIST *l, UENTRY *e);

//Delete an arbitrary entry from the list
CONTACT *RemoveCEntry(CLIST *cl, CENTRY *ce);

//Delete the last entry from the list
USER *DeleteLast(ULIST *l);

//Delete the last entry from the contact list
CONTACT *DeleteLastC(CLIST *cl);

//Print the list
void PrintList(ULIST *l);

//Print the list
void PrintCList(CLIST *cl);

#endif
