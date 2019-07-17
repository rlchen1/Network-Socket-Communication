#ifndef GUI_H
#define GUI_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//global variables
char userentry[256];
char loginentry[10];
char passentry[10];
char addfriend[10];
char chatfriend[10];
char recententry[256];
//char chatlist[1000];
int menuChoice;
int testint;
//char tmp[256];
char teststring[256];
char fnamechat[50];
//Structs
typedef struct Entry {
	GtkWidget *entry1, *entry2;
} Entry;

//empty entry
void emptyentry (GtkEntry *entry);

//saves username
void login_callback (GtkWidget *widget, Entry *e);

//saves password
void password_callback (GtkWidget *widget, Entry *e);

//creates username
void create_login_callback (GtkWidget *widget, Entry *e);

//creates password
void create_password_callback(GtkWidget *widget, Entry *e);

//rotates the position of the tabs
void rotate_book (GtkButton *button, GtkNotebook *notebook);

//adds/Removes page tabs and borders
void tabsborder_book (GtkButton *button, GtkNotebook *notebook);

//removes a page from the notebook
void remove_book (GtkButton *button, GtkNotebook *notebook);

//delete event
gboolean delete (GtkWidget *widget, GtkWidget *event, gpointer data);

//closes login window
void closelogin (GtkWidget *widget, GtkWidget *widget2);

//callback function
void callback (GtkWidget *widget, GtkWidget *entry);

//inserts text into textview
void insert_text (GtkWidget *widget, GtkWidget *textview);

//current page for debugging !!!REMOVE
void currentPage (GtkWidget *widget, GtkNotebook *notebook);

//inserts page in notebook
void insert_page (GtkButton *button, GtkNotebook *notebook);

//chat gui
int chat(int argc, char *argv[]);

int chat2(int argc, char *argv[]);

int chat3(int argc, char *argv[]);

//returns entry text
void add_friend_callback (GtkWidget *widget, GtkWidget *entry);

//send a message
void chat_callback (GtkWidget *widget, GtkWidget *entry);

//adds contact
void addFriend (int argc, char *argv[]);

//chat friend
void chatFriend (int argc, char *argv[]);

//menu ui
int UI (int argc, char *argv[]);

int GUImain (int argc, char *argv[]);


#endif
