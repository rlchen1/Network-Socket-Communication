#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "UserList.h"

//Retrieve data from UserData.txt
ULIST *RetrieveData(FILE *f)
{
    char UID[20], Password[20];
    //int counter = 0; // Counter for number of users
    USER *u;
    CONTACT *ct;
    ULIST *l = CreateList();
    //Read data from the file
    while(!feof(f)){
        FILE *fp;
        char fname[40] = "";
        char FID[20];
        int len;
        //int ncounter = 0; // Counter for number of contacts
        if((fgets(UID, 20, f) != NULL)&&(fgets(Password, 20, f) != NULL)){ //read username and password
            len = strlen(UID);
            UID[len-1] = 0;
            len = strlen(Password);
            Password[len-1] = 0;
            u = NewUser(UID, Password); //Create a new user struct with the username and password
            AppendEntry(l, u); //Append the user struct to the user list
            strncpy(fname, "S-", 2);
            strcat(fname, u->UserName); //Prepare the file name for contact info
            strcat(fname, "Friends.txt");        //Prepare the file name for contact info
            if((fp = fopen(fname, "a+")) == NULL){ //Open the file
                printf("Failed to open %s\n", fname);
                exit(10);
            }
            do{
               if((fgets(FID, 20, fp)) != NULL){
                   len = strlen(FID); //Get the length of username
                   FID[len-1] = 0;
                   ct = NewContact(FID); //Create a new contact struct
                   AppendCEntry(u->Friends, ct); //Append the contact struct to the contact list of
                                                 //The current user
                   //ncounter++;
               }
            }while(!feof(fp));
            fclose(fp);
            //counter++;
        }
    }
    return l;
}

//Check login information, returns 1
//if there's matching result; returns
//0 if password doesn't match; returns
//-1 if username is not found;
int LoginCheck(ULIST *l, char *UserName, char *Password)
{
    assert(l);
    assert(UserName);
    assert(Password);

    UENTRY *e = NULL, *n = NULL;
    int flag = -1;
    int len = l->Length;
    int i = 0;

    e = l->First;
    while(e)
    {
        n = e->Next;
        //Check if the input username match the
        //the username in the current entry
        if(strcmp(UserName, e->user->UserName) == 0){
            //If username matches, check
            //if the password matches
            if(strcmp(Password, e->user->Password) == 0){
                //If password matches, set flag = 1 and
                //break from the loop
                flag = 1;
                break;
            }
            else{
                //If password doesn't match, set flag = 0
                //and break from the loop
                flag = 0;
                break;
            }
        }
        //If username does not match, increment i and check
        //the next entry
        i++;
        e = n;
    }

    //If the input username doesn't match any username in
    //the whole list, set flag = -1
    if(i == len){
        flag = -1;
    }

    return flag;
}

//Check register information, returns 1
//if username for register is available, 
//returns 0 if the username has been used
int RegisterCheck(ULIST *l, char *UserName)
{
    assert(l);
    assert(UserName);

    int flag = 1;
    UENTRY *e = NULL, *n = NULL;
    int len = l->Length;
    int i = 0;

    e = l->First;
    while(e)
    {
        n = e->Next;
        //Check if the input username
        //matches any of the existing
        //ones, if yes, set flag = 0
        if(strcmp(UserName, e->user->UserName) == 0){
            flag = 0;
            break;
        }
        i++;
        e = n;
    }

    //If the username doesn't match
    //any of the existing ones, set
    //flag = 1
    if(i == len){
        flag = 1;
    }

    return flag;
}

//Check if the username already exist in
//a given contact list, if yes return 1, 
//if not return 0
int ContactCheck(CLIST *cl, char *UserName)
{
    assert(cl);
    assert(UserName);

    int flag = 0;
    int i = 0;
    CENTRY *e = NULL, *n = NULL;
    int len = cl->Length;

    e = cl->First;
    while(e){
        n = e->Next;
        //Check if the input username
        //matches any of the existing
        //ones, if yes, set flag = 1
        if(strcmp(UserName, e->contact->UserName) == 0){
            flag = 1;
            //printf("User %s found!\n", UserName);
            break;
        }
        //printf("Here's %d\n", i);
        i++;
        e = n;
    }

    //If username doesn't match any,
    //set flag = 0
    if(i == len){
        flag = 0;
    }

    return flag;
}

//Create a new list of users
ULIST *CreateList(void)
{
    ULIST *l;

    //Allocate memory for user list
    l = malloc(sizeof(ULIST));
    //If allocation failed, print the
    //following information and abort
    //the program
    if(l == NULL){
        printf("Memory allocation for user list failed..\n");
        printf("Aborting..\n");
        exit(10);
    }

    l->Length = 0;
    l->First = NULL;
    l->Last = NULL;

    return l;
}

//Create a new list of contacts
CLIST *CreateCList(void)
{
    CLIST *cl;
    
    //Allocate memory for contact list
    cl = malloc(sizeof(CLIST));
    //If allocation failed, print the
    //following information and abort
    //the program
    if(cl == NULL){
        printf("Memory allocation for contact list failed..\n");
        printf("Aborting..\n");
        exit(10);
    }

    cl->Length = 0;
    cl->First = NULL;
    cl->Last = NULL;

    return cl;
}
//Delete a user list
void DeleteList(ULIST *l)
{
    assert(l);
    UENTRY *e = NULL, *n = NULL;
    USER *u = NULL;

    e = l->First;
    //Loop through the whole list
    //and delete all the entries
    while(e)
    {
        n = e->Next;
        u = DeleteEntry(e);
        RemoveUser(u);
        e = n;
    }
    free(l);
}

//Delete a contact list
void DeleteCList(CLIST *cl)
{
    assert(cl);
    CENTRY *ce = NULL, *cn = NULL;
    CONTACT *ct = NULL;

    ce = cl->First;
    //Loop through the whole list
    //and delete all the entries
    while(ce)
    {
        cn = ce->Next;
        ct = DeleteCEntry(ce);
        RemoveContact(ct);
        ce = cn;
    }
    free(cl);
}

//Create a new user entry
UENTRY *CreateEntry(USER *u)
{
    assert(u);
    UENTRY *e = NULL;

    e = malloc(sizeof(UENTRY));
    if(e == NULL){
        printf("Memory allocation for user entry failed..\n");
        printf("Aborting..\n");
        exit(10);
    }

    e->List = NULL;
    e->Prev = NULL;
    e->Next = NULL;
    e->user = u;

    return e;
}

//Create a new contact entry
CENTRY *CreateCEntry(CONTACT *ct)
{
    assert(ct);
    CENTRY *ce = NULL;

    ce = malloc(sizeof(CENTRY));
    if(ce == NULL){
        printf("Memory allocation for contact entry failed..\n");
        printf("Aborting..\n");
        exit(10);
    }

    ce->List = NULL;
    ce->Prev = NULL;
    ce->Next = NULL;
    ce->contact = ct;
    return ce;
}

//Delete a user entry from the list
//returns the user information of 
//type USER
USER *DeleteEntry(UENTRY *e)
{
    assert(e);
    USER *u = NULL;

    u = e->user;
    free(e);
    
    return u;
}

//Delete a contact entry from the list
//returns the user information of 
//type CONTACT
CONTACT *DeleteCEntry(CENTRY *ce)
{
    assert(ce);
    CONTACT *ct = NULL;
    
    ct = ce->contact;
    free(ce);

    return ct;
}

//Append a user entry to the list
void AppendEntry(ULIST *l, USER *u)
{
    assert(l);
    assert(u);

    UENTRY *e = NULL;

    //Create a new user entry
    e = CreateEntry(u);
    //If the list l is not empty, 
    //add the new entry to the end
    //of the list
    if(l->Last){
        e->List = l;
        e->Prev = l->Last;
        e->Next = NULL;
        l->Last->Next = e;
        l->Last = e;
    }
    //If the list l is empty, 
    //add the new entry to the
    //list and set the pointer
    //First and Last pointing to
    //the new entry
    else{
        e->List = l;
        e->Prev = NULL;
        e->Next = NULL;
        l->First = e;
        l->Last = e;
    }
    //Increment the length of the list
    l->Length++;
}

//Append a contact entry to the list
void AppendCEntry(CLIST *cl, CONTACT *ct)
{
    assert(cl);
    assert(ct);

    CENTRY *ce = NULL;

    //Create a new user entry
    ce = CreateCEntry(ct);
    //If the list l is not empty, 
    //add the new entry to the end
    //of the list
    if(cl->Last){
        ce->List = cl;
        ce->Prev = cl->Last;
        ce->Next = NULL;
        cl->Last->Next = ce;
        cl->Last = ce;
    }
    //If the list l is empty, 
    //add the new entry to the
    //list and set the pointer
    //First and Last pointing to
    //the new entry
    else{
        ce->List = cl;
        ce->Prev = NULL;
        ce->Next = NULL;
        cl->First = ce;
        cl->Last = ce;
    }
    //Increment the length of the list
    cl->Length++;
}

//Delete the first entry in the list
USER *DeleteFirst(ULIST *l)
{
    assert(l);
    UENTRY *e = NULL;
    
    if(l->First){
        e = l->First;
        l->First = e->Next;
        if(l->First){
            l->First->Prev = NULL;
        }
        else{
            assert(l->Last == e);
            l->Last = NULL;
        }
        l->Length--;
        return DeleteEntry(e);
    }
    else{
        return NULL;
    }
}

//Delete the first entry in the list
CONTACT *DeleteFirstC(CLIST *cl)
{
    assert(cl);
    CENTRY *ce = NULL;
    
    if(cl->First){
        ce = cl->First;
        cl->First = ce->Next;
        if(cl->First){
            cl->First->Prev = NULL;
        }
        else{
            assert(cl->Last == ce);
            cl->Last = NULL;
        }
        cl->Length--;
        return DeleteCEntry(ce);
    }
    else{
        return NULL;
    }
}

//Delete an arbitrary entry in the list
USER *RemoveEntry(ULIST *l, UENTRY *e)
{
    assert(l);
    assert(e);

    if(l->First == e){
        return DeleteFirst(l);
    }
    else if(l->Last == e){
        return DeleteLast(l);
    }
    else{
        e->Prev->Next = e->Next;
        e->Next->Prev = e->Prev;
        e->Next = NULL;
        e->Prev = NULL;
        l->Length--;
        return DeleteEntry(e);
    }
}

//Delete an arbitrary entry in the list
CONTACT *RemoveCEntry(CLIST *cl, CENTRY *ce)
{
    assert(cl);
    assert(ce);

    if(cl->First == ce){
        return DeleteFirstC(cl);
    }
    else if(cl->Last == ce){
        return DeleteLastC(cl);
    }
    else{
        ce->Prev->Next = ce->Next;
        ce->Next->Prev = ce->Prev;
        ce->Next = NULL;
        ce->Prev = NULL;
        cl->Length--;
        return DeleteCEntry(ce);
    }
}

//Delete the last entry in the list
USER *DeleteLast(ULIST *l)
{
    assert(l);
    UENTRY *e = NULL;

    if(l->Last){
        e = l->Last;
        l->Last = e->Prev; //l->Last now points to the 
                           //second to the last item in the list
        //If the item exists, set its Next pointer points to NULL
        if(l->Last){
            l->Last->Next = NULL;
        }
        //If the item does not exist, which means the list is now
        //empty, set the First pointer points to NULL
        else{
            assert(l->First == e);
            l->First = NULL;
        }
        l->Length--;
        return DeleteEntry(e);
    }
    else{
        return NULL;
    }
}

//Delete the last entry in the list
CONTACT *DeleteLastC(CLIST *cl)
{
    assert(cl);
    CENTRY *ce = NULL;

    if(cl->Last){
        ce = cl->Last;
        cl->Last = ce->Prev; //l->Last now points to the 
                           //second to the last item in the list
        //If the item exists, set its Next pointer points to NULL
        if(cl->Last){
            cl->Last->Next = NULL;
        }
        //If the item does not exist, which means the list is now
        //empty, set the First pointer points to NULL
        else{
            assert(cl->First == ce);
            cl->First = NULL;
        }
        cl->Length--;
        return DeleteCEntry(ce);
    }
    else{
        return NULL;
    }
}

//Print the user list
void PrintList(ULIST *l)
{
    assert(l);
    UENTRY *e = NULL, *n = NULL;
    USER *u = NULL;
    
    e = l->First;
    while(e)
    {
        n = e->Next;
        u = e->user;
        PrintUser(u);
        e = n;
    }
}

//Print the contact list
void PrintCList(CLIST *cl)
{
    assert(cl);
    CENTRY *ce = NULL, *cn = NULL;
    CONTACT *ct = NULL;
    
    ce = cl->First;
    while(ce)
    {
        cn = ce->Next;
        ct = ce->contact;
        PrintContact(ct);
        ce = cn;
    }
}
