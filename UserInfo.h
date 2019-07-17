#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <stdbool.h>

typedef struct User USER;
typedef struct UserList ULIST;
typedef struct UserEntry UENTRY;
typedef struct Contact CONTACT;
typedef struct ContactEntry CENTRY;
typedef struct ContactList CLIST;

struct UserList{
    int Length;    //Length of the user list
    UENTRY *First; //The first entry in the list
    UENTRY *Last;  //The last entry in the list
};

struct UserEntry{
    ULIST *List; //Points to the list that holds all the users
    UENTRY *Next;//Points to the next entry in the list, NULL when
                 //the current entry is the last entry
    UENTRY *Prev;//Points to the previous entry in the list, NULL
                 //when the current entry is the first entry
    USER *user;  //Points to the corresponding user account
};

struct User{
    CLIST *Friends;      //List that holds all the contact of this user
    char UserName[10];   //User name with maximum length of 20 characters
    char Password[10];   //Password with maximum length of 20 characters
    int color;           //Preferred text color 
    bool Status;         //Current status, 0 for off-line, 1 for on-line
};

struct Contact{
    char UserName[10];
    int color;
    bool Status;
};

struct ContactEntry{
    CLIST *List;
    CENTRY *Prev;
    CENTRY *Next;
    CONTACT *contact;
};

struct ContactList{
    int Length;
    CENTRY *First;
    CENTRY *Last;
};

#endif
