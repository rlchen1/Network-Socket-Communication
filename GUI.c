#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "GUI.h"
//#include "Chess.h" //this causes errors??
/*char userentry[256];
char loginentry[10];
char passentry[10];
char addfriend[10];
char chatfriend[10];
*/

//void UpdateWindow(void)     /* render the window on screen */
//{
    /* this server has it's own main loop for handling client connections;
     * as such, it can't have the usual GUI main loop (gtk_main);
     * instead, we call this UpdateWindow function on regular basis
     */
//     while(gtk_events_pending())
//     {
//	     gtk_main_iteration();
//     }
//} /* end of UpdateWindow */

char friendlist[200];
//char chatlist[200];
char chatlist[2000];

//GtkWidget *Textview;	//for friends list

void emptyentry (GtkEntry *entry){
	const gchar *text = "";
	gtk_entry_set_text (entry, text);
}

void login_callback(GtkWidget *widget, Entry *e){
	menuChoice = 2;
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (e));
	sprintf(loginentry, "%s", entry_text);
	printf("You entered username: %s\n", loginentry);
}

void password_callback(GtkWidget *widget, Entry *e){
	menuChoice = 2;
//	printf("menu choice = %d\n", menuChoice);
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY(e));
	sprintf(passentry, "%s", entry_text);
	printf("You entered password: %s\n", passentry);
}

void create_login_callback(GtkWidget *widget, Entry *e){
	menuChoice = 1;
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (e));
	sprintf(loginentry, "%s", entry_text);
	printf("You entered username: %s\n", loginentry);
}

void create_password_callback(GtkWidget *widget, Entry *e){
	menuChoice = 1;
//	printf("menu choice = %d\n", menuChoice);
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY(e));
	sprintf(passentry, "%s", entry_text);
	printf("You entered password: %s\n", passentry);
}

/* This function rotates the position of the tabs */
void rotate_book( GtkButton   *button,
                         GtkNotebook *notebook )
{
    gtk_notebook_set_tab_pos (notebook, (notebook->tab_pos + 1) % 4);
}

/* Add/Remove the page tabs and the borders */
void tabsborder_book( GtkButton   *button,
                             GtkNotebook *notebook )
{
    gint tval = FALSE;
    gint bval = FALSE;
    if (notebook->show_tabs == 0)
	    tval = TRUE; 
    if (notebook->show_border == 0)
	    bval = TRUE;
    
    gtk_notebook_set_show_tabs (notebook, tval);
    gtk_notebook_set_show_border (notebook, bval);
}

/* Remove a page from the notebook */
void remove_book( GtkButton   *button,
                         GtkNotebook *notebook )
{
    gint page;
    
    page = gtk_notebook_get_current_page (notebook);
    gtk_notebook_remove_page (notebook, page);
    /* Need to refresh the widget -- 
     This forces the widget to redraw itself. */
    gtk_widget_queue_draw (GTK_WIDGET (notebook));
}

gboolean delete( GtkWidget *widget,
                        GtkWidget *event,
                        gpointer   data )
{
    gtk_main_quit ();
    return FALSE;
}

void closelogin(GtkWidget *widget, GtkWidget *widget2)
{
	gtk_widget_destroy (widget2);
}

void friends_list(GtkWidget *widget, GtkLabel *Textview){
	const gchar *friends = "";
	char fname[30];
	char frid[10];
	FILE *fd;
	//char empty[5] = "";
	GtkTextBuffer *buffer;
	GtkTextMark *mark;
	GtkTextIter iter;

	//read from text file
	strncpy(fname, loginentry, 10);
	strcat(fname, "Friends.txt");
	fd = fopen(fname, "a+");
	while(!feof(fd)){
    	if(fgets(frid, 20, fd) != NULL){
        	strcat(friendlist, frid);
    	}
	}
	fclose(fd);
	
	//write to textentry
	friends = friendlist;	

	//Textview = "";
	
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (Textview));
	mark = gtk_text_buffer_get_insert(buffer);
	gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
    //gtk_text_buffer_insert (buffer, &iter, empty, -1);
	gtk_text_buffer_insert (buffer, &iter, friends, -1);
}

void chat_update(GtkWidget *widget, GtkWidget *textview){
	const gchar *chatty = "";
	//char fname[30];
	char fline[256];
	FILE *fd;
	//char empty[5] = "";
	GtkTextBuffer *buffer;
	GtkTextMark *mark;
	GtkTextIter iter;
printf("update chat is called");
	//read from text file
	//strcat(fname, "MSG.txt");
	fd = fopen("MSG.txt", "r");
	while(!feof(fd)){
    	if(fgets(fline, 256, fd) != NULL){
        	strcat(chatlist, fline);
        chatty = chatlist;	
printf("chatlist to chatty");	
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
	mark = gtk_text_buffer_get_insert(buffer);
	gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
    //gtk_text_buffer_insert (buffer, &iter, empty, -1);
	gtk_text_buffer_insert (buffer, &iter, chatty, -1);
	
       }
	}
	fclose(fd);
	
	//write to textentry
	        /*FILE *fp;
        char fline[256] = "";
        char msg[1000] = "";
        printf("Before do while");
        if((fp = fopen("MSG.txt", "r"))==NULL)
        {
            printf("Failed to open MSG.txt\n");
            exit(10);
        }
        do{
            printf("Beg of do while");
            if(fgets(fline,256,fp) != NULL)
            {
                printf("%s",fline);
                //entry_text = fline;
                strcat(chatlist,fline);
               
            }
        }while(!feof(fp));
        printf("End of do while");
        fclose(fp);
        entry_text = chatlist;
*/
}

void callback (GtkWidget *widget, GtkWidget *entry){
	const gchar *entry_text = "";
	entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
	//sprintf(userentry + strlen(userentry), "You: %s\n", entry_text);
	//sprintf(userentry, "%s\n", entry_text);
	sprintf(recententry, "%s\n", entry_text);
	//printf("You entered: %s\n", userentry);

	/*const gchar *chatty = "";
	char fname[30];
	char frid[10];
	FILE *fd;
	memset(chatlist, 0, sizeof(memset));
	fd = fopen("MSG.txt", "a+");
	while(!feof(fd)){
	if(fgets(frid, 20, fd) != NULL){
		strcat(chatlist, frid);
		chatty = chatlist;
	}
	//chatty = frid;
	
	}
	fclose(fd);
	//chatty = chatlist;
	sprintf(userentry, "%s", chatty);*/
}
//........
void insert_text (GtkWidget *widget, GtkWidget *textview){
	GtkTextBuffer *buffer;
	GtkTextMark *mark;
	GtkTextIter iter;
        //const gchar *text;
	
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));

	mark = gtk_text_buffer_get_insert(buffer);
	gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
	gtk_text_buffer_insert (buffer, &iter, userentry, -1);
}

void currentPage (GtkWidget *widget, GtkNotebook *notebook){
	int page;
	page = gtk_notebook_get_current_page(notebook);
//	printf("Current page is %d\n", page);
}
void insert_page (GtkButton *button, GtkNotebook *notebook){
	/*GtkWidget *frame;
	GtkWidget *label;
	frame = gtk_frame_new ("Test");
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);

	label = gtk_label_new ("Test");
	gtk_container_add (GTK_CONTAINER(frame), label);
	gtk_widget_show(label);

	label = gtk_label_new("Friend 2");*/
	GtkWidget *label;
	GtkWidget *textview;
	GtkTextBuffer *buffer;
	GtkWidget *scroll;
	GtkTextIter iter;
	textview = gtk_text_view_new();
    	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    	gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
   	 gtk_text_buffer_insert(buffer, &iter, userentry, -1);
   	 scroll = gtk_scrolled_window_new (NULL, NULL);
   	 gtk_container_add (GTK_CONTAINER (scroll), textview);
   	 gtk_widget_show_all(scroll);
   	 //entry = gtk_entry_new();
   	 //gtk_widget_show (entry);
   
   	 label = gtk_label_new ("Test");

	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), scroll, label);
	gtk_widget_queue_draw (GTK_WIDGET (notebook));
}

int chess(int argc, char *argv[]){
	menuChoice = 4; //calls chess main	
	return 0;
}

int openchat(int argc, char *argv[]){
	menuChoice = 3; //calls chat
	return 0;
}

int quitprogram(int argc, char *argv[]){
	menuChoice = 9;
	return 0;
}

int setUI(int argc, char *argv[]){
	testint = 0;
	return 0;
}

int resetUI(int argc, char *argv[]){
	menuChoice = 7;
	return 0;
}
	
int chat( int argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button2;
    GtkWidget *table;
    GtkWidget *notebook;
    //GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *textview;
    GtkWidget *scroll;
    GtkWidget *sendbutton;
    GtkTextBuffer *buffer;
    GtkTextMark *mark;
    GtkTextIter iter;
    /*char empty[5] = "";
	const gchar *chatty = "";
	char fname[30];
	char frid[10];
	FILE *fd;*/

   // int i;
   // char bufferf[32];
   // char bufferl[32];
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title(GTK_WINDOW(window), "Chatty Chess");
    g_signal_connect (window, "delete-event",
	              G_CALLBACK (delete), NULL);
    
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    table = gtk_table_new (3, 6, FALSE);
    gtk_container_add (GTK_CONTAINER (window), table);
    
    /* Create a new notebook, place the position of the tabs */
    notebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
    gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 6, 0, 1);
    gtk_widget_show (notebook);
    
    /* Let's append a bunch of pages to the notebook */
    /*for (i = 0; i < 5; i++) {
	sprintf(bufferf, "Testing  %d", i + 1);
	sprintf(bufferl, "Friend  %d", i + 1);
	
	frame = gtk_frame_new (bufferf);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new (bufferf);
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new (bufferl);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);
    }*/
      	//strcat(fname, "MSG.txt");
      	
	/*fd = fopen("MSG.txt", "a+");
	while(!feof(fd)){
    	if(fgets(frid, 20, fd) != NULL){
        	strcat(chatlist, frid);
    	}
	}
	fclose(fd);
	chatty = chatlist;*/
	//write to textentry
    /* Now let's add a page to a specific spot */
	/*const gchar *chatty = "";
	char fname[30];
	char frid[10];
	FILE *fd;
	memset(chatlist, 0, sizeof(memset));
	fd = fopen("MSG.txt", "a+");
	while(!feof(fd)){
	if(fgets(frid, 20, fd) != NULL){
		strcat(chatlist, frid);
		chatty = chatlist;
	}
	//chatty = frid;
	
	}
	fclose(fd);
	//chatty = chatlist;
	sprintf(userentry, "%s", chatty);*/
    textview = gtk_text_view_new();
//    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
//    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    //gtk_text_buffer_insert(buffer, &iter, empty, -1);
    //chat_update(notebook, textview);
    //gtk_text_buffer_insert(buffer, &iter, userentry, -1);
//	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
	//mark = gtk_text_buffer_get_insert(buffer);
	//gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
        //gtk_text_buffer_insert (buffer, &iter, empty, -1);
//	gtk_text_buffer_insert (buffer, &iter, chatlist, -1);

    scroll = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_add (GTK_CONTAINER (scroll), textview);
    gtk_widget_show_all(scroll);
    //entry = gtk_entry_new();
    //gtk_widget_show (entry);
   
    label = gtk_label_new ("Chat");
    gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), scroll, label, 1);

//UPDATE CHAT

	const gchar *chatty = "";
	//char fname[30];
	char fline[256];
	FILE *fd;
        FILE *ftest;
	//char empty[5] = "";
//	GtkTextBuffer *buffer;
//	GtkTextMark *mark;
//	GtkTextIter iter;
        strncpy(chatlist, "",1000);	
	//read from text file
	//strcat(fname, "MSG.txt");
	//fd = fopen("MSG.txt", "r+");
	char fname[50] = "";
        strcat(fname,loginentry);
        strcat(fname,"_");
        strcat(fname,chatfriend);
        strcat(fname,"_");
        strcat(fname,"MSG.txt");
        //printf("%s",fnamechat);
        
        if((ftest = fopen(fname,"a+")) == NULL){
            printf("Failed to open message file\n");
            exit(10);
        }
        fclose(ftest);
        
	if((fd = fopen(fname, "a+")) == NULL){
            printf("Failed to open %s\n", fname);
            exit(10);
        }
	while(!feof(fd)){
    	    if(fgets(fline, 256, fd) != NULL){
        	strcat(chatlist, fline);
	//	chatty = chatlist;
	//printf(userentry, "UPDATED\n%s", chatty);	
		
	       // buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
	        //mark = gtk_text_buffer_get_insert(buffer);
	        //gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
                //gtk_text_buffer_insert (buffer, &iter, empty, -1);
	       // gtk_text_buffer_insert (buffer, &iter, chatty, -1);
           }
           else{
               //printf("There's nothing here\n");
           }
	}
	fclose(fd);
	//Added
	chatty = chatlist;
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (textview));
	mark = gtk_text_buffer_get_insert(buffer);
	gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
	gtk_text_buffer_insert (buffer, &iter, chatty, -1);

//END of UPDATE CHAT
	
	//write to textentry
	        //FILE *fp;
        //char fline[256] = "";
 
 	//GtkWidget *label;
    /* Now finally let's prepend pages to the notebook */
    /*for (i = 0; i < 5; i++) {
	sprintf (bufferf, "Prepend Frame %d", i + 1);
	sprintf (bufferl, "PPage %d", i + 1);
	
	frame = gtk_frame_new (bufferf);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new (bufferf);
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new (bufferl);
	gtk_notebook_prepend_page (GTK_NOTEBOOK (notebook), frame, label);
    }*/
    
    /* Set what page to start at (page 4) */
    gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 0);

    /* Create a bunch of buttons */
   /* button = gtk_button_new_with_label ("close");
    g_signal_connect (button, "clicked",
			      G_CALLBACK (delete), NULL);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, 1, 2);
    gtk_widget_show (button);
    
    button = gtk_button_new_with_label ("next page");
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_notebook_next_page),
			      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 1, 2);
    gtk_widget_show (button);
    
    button = gtk_button_new_with_label ("prev page");
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_notebook_prev_page),
			      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 2, 3, 1, 2);
    gtk_widget_show (button);
    */
    button = gtk_button_new_with_label ("Refresh");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (rotate_book),
	              notebook);
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), window);
    g_signal_connect (button, "clicked", G_CALLBACK (gtk_widget_hide_all), window);
    g_signal_connect_swapped (button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, 1, 2);
    gtk_widget_show (button);
    
    /*button = gtk_button_new_with_label ("tabs/border on/off");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (tabsborder_book),
                      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 4, 5, 1, 2);
    gtk_widget_show (button);*/
    
    button2 = gtk_button_new_with_label ("Main Menu");
    g_signal_connect (button2, "clicked", G_CALLBACK (setUI), NULL);
    g_signal_connect (button2, "clicked", G_CALLBACK (gtk_main_quit), window);
    g_signal_connect(button2, "clicked", G_CALLBACK (gtk_widget_hide_all), window);
    g_signal_connect_swapped (button2, "clicked", G_CALLBACK(gtk_widget_destroy), window);
    gtk_table_attach_defaults (GTK_TABLE (table), button2, 1, 2, 1, 2);
    gtk_widget_show (button2);
    
    entry = gtk_entry_new();
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (callback), entry);
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (currentPage), notebook);
    //gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (insert_text), textview);
    //gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (chat_update), textview);
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (gtk_main_quit), window);
    g_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (gtk_widget_hide_all), window);
    g_signal_connect_swapped (GTK_OBJECT(entry), "activate", G_CALLBACK (gtk_widget_destroy), window); //closes window on button click
    g_signal_connect (GTK_OBJECT(entry), "activate", G_CALLBACK (openchat), NULL);	
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK(emptyentry), entry);
	////g_signal_connect_swapped (GTK_OBJECT(entry), "activate", G_CALLBACK (gtk_widget_destroy), window); //closes window on button click
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 2, 3, 1, 2);
    gtk_widget_show (entry);

    sendbutton  = gtk_button_new_with_label ("Send");
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (callback), entry);
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (currentPage), notebook);
    //g_signal_connect (sendbutton, "clicked", G_CALLBACK (chat_update), textview);
    //g_signal_connect (sendbutton, "clicked", G_CALLBACK (insert_text), textview);
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (emptyentry), entry);
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (gtk_main_quit), window);
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (gtk_widget_hide_all), window);
    g_signal_connect_swapped (sendbutton, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (openchat), NULL);
	//g_signal_connect_swapped (sendbutton, "clicked", G_CALLBACK (gtk_widget_destroy), window); //closes window on button click
    gtk_table_attach_defaults (GTK_TABLE (table), sendbutton, 3, 4, 1, 2);
    gtk_widget_show (sendbutton);
	////g_signal_connect_swapped (sendbutton, "clicked", G_CALLBACK (gtk_widget_destroy), window); //closes window on button click

    gtk_widget_show (table);
    gtk_widget_show (window);
   
    gtk_main(); 
    //UpdateWindow(); 
    return 0;
}

int chat2( int argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *notebook;
    //GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *textview;
    GtkWidget *scroll;
    GtkWidget *sendbutton;
    GtkTextBuffer *buffer;
    GtkTextIter iter;
    //int i;
    //char bufferf[32];
    //char bufferl[32];
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title(GTK_WINDOW(window), "Chatty Chess");
    g_signal_connect (window, "delete-event",
	              G_CALLBACK (delete), NULL);
    
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    table = gtk_table_new (3, 6, FALSE);
    gtk_container_add (GTK_CONTAINER (window), table);
    
    /* Create a new notebook, place the position of the tabs */
    notebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
    gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 6, 0, 1);
    gtk_widget_show (notebook);
    
    /* Let's append a bunch of pages to the notebook */
    /*for (i = 0; i < 5; i++) {
	sprintf(bufferf, "Testing  %d", i + 1);
	sprintf(bufferl, "Friend  %d", i + 1);
	
	frame = gtk_frame_new (bufferf);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new (bufferf);
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new (bufferl);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);
    }*/
      
    /* Now let's add a page to a specific spot */
    textview = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    gtk_text_buffer_insert(buffer, &iter, userentry, -1);
    scroll = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_add (GTK_CONTAINER (scroll), textview);
    gtk_widget_show_all(scroll);
    entry = gtk_entry_new();
    gtk_widget_show (entry);
   
    label = gtk_label_new ("Chat");
    gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), scroll, label, 1);
 
 	//GtkWidget *label;
    /* Now finally let's prepend pages to the notebook */
    /*for (i = 0; i < 5; i++) {
	sprintf (bufferf, "Prepend Frame %d", i + 1);
	sprintf (bufferl, "PPage %d", i + 1);
	
	frame = gtk_frame_new (bufferf);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new (bufferf);
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new (bufferl);
	gtk_notebook_prepend_page (GTK_NOTEBOOK (notebook), frame, label);
    }*/
    
    /* Set what page to start at (page 4) */
    gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 0);

    /* Create a bunch of buttons */
   /* button = gtk_button_new_with_label ("close");
    g_signal_connect (button, "clicked",
			      G_CALLBACK (delete), NULL);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, 1, 2);
    gtk_widget_show (button);
    
    button = gtk_button_new_with_label ("next page");
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_notebook_next_page),
			      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 1, 2);
    gtk_widget_show (button);
    
    button = gtk_button_new_with_label ("prev page");
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_notebook_prev_page),
			      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 2, 3, 1, 2);
    gtk_widget_show (button);
    */
    button = gtk_button_new_with_label ("tab position");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (rotate_book),
	              notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, 1, 2);
    gtk_widget_show (button);
    
    /*button = gtk_button_new_with_label ("tabs/border on/off");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (tabsborder_book),
                      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 4, 5, 1, 2);
    gtk_widget_show (button);*/
    
    button = gtk_button_new_with_label ("Chess");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (exit),
                      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 1, 2);
    gtk_widget_show (button);
    
    entry = gtk_entry_new();
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (callback), entry);
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (currentPage), notebook);
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (insert_text), textview);
	
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK(emptyentry), entry);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 2, 3, 1, 2);
    gtk_widget_show (entry);

    sendbutton  = gtk_button_new_with_label ("Send");
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (callback), entry);
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (insert_text), textview);
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (emptyentry), entry);
    gtk_table_attach_defaults (GTK_TABLE (table), sendbutton, 3, 4, 1, 2);
    gtk_widget_show (sendbutton);

    gtk_widget_show (table);
    gtk_widget_show (window);
   
    gtk_main(); 
    return 0;
}

int chat3( int argc,
          char *argv[] )
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *notebook;
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *textview;
    GtkWidget *scroll;
    GtkWidget *sendbutton;
    GtkTextBuffer *buffer;
    GtkTextIter iter;
    //int i;
    //char bufferf[32];
    //char bufferl[32];
    gtk_init (&argc, &argv);
    
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    gtk_window_set_title(GTK_WINDOW(window), "Chatty Chess");
    g_signal_connect (window, "delete-event",
	              G_CALLBACK (delete), NULL);
    
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    table = gtk_table_new (3, 6, FALSE);
    gtk_container_add (GTK_CONTAINER (window), table);
    
    /* Create a new notebook, place the position of the tabs */
    notebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
    gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 6, 0, 1);
    gtk_widget_show (notebook);
    
    /* Let's append a bunch of pages to the notebook */
    /*for (i = 0; i < 5; i++) {
	sprintf(bufferf, "Testing  %d", i + 1);
	sprintf(bufferl, "Friend  %d", i + 1);
	
	frame = gtk_frame_new (bufferf);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new (bufferf);
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new (bufferl);
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);
    }*/
      
    /* Now let's add a page to a specific spot */
    textview = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textview));
    gtk_text_buffer_get_iter_at_offset(buffer, &iter, 0);
    gtk_text_buffer_insert(buffer, &iter, userentry, -1);
    scroll = gtk_scrolled_window_new (NULL, NULL);
    gtk_container_add (GTK_CONTAINER (scroll), textview);
    gtk_widget_show_all(scroll);
    entry = gtk_entry_new();
    gtk_widget_show (entry);
   
    label = gtk_label_new ("Chat");
    gtk_notebook_insert_page (GTK_NOTEBOOK (notebook), scroll, label, 1);
 
 	//GtkWidget *label;
    /* Now finally let's prepend pages to the notebook */
    /*for (i = 0; i < 5; i++) {
	sprintf (bufferf, "Prepend Frame %d", i + 1);
	sprintf (bufferl, "PPage %d", i + 1);
	
	frame = gtk_frame_new (bufferf);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new (bufferf);
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new (bufferl);
	gtk_notebook_prepend_page (GTK_NOTEBOOK (notebook), frame, label);
    }*/
    
    /* Set what page to start at (page 4) */
    gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 0);

    /* Create a bunch of buttons */
   /* button = gtk_button_new_with_label ("close");
    g_signal_connect (button, "clicked",
			      G_CALLBACK (delete), NULL);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, 1, 2);
    gtk_widget_show (button);
    
    button = gtk_button_new_with_label ("next page");
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_notebook_next_page),
			      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 1, 2);
    gtk_widget_show (button);
    
    button = gtk_button_new_with_label ("prev page");
    g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_notebook_prev_page),
			      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 2, 3, 1, 2);
    gtk_widget_show (button);
    */
    button = gtk_button_new_with_label ("tab position");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (rotate_book),
	              notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, 1, 2);
    gtk_widget_show (button);
    
    /*button = gtk_button_new_with_label ("tabs/border on/off");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (tabsborder_book),
                      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 4, 5, 1, 2);
    gtk_widget_show (button);*/
    
    button = gtk_button_new_with_label ("Chess");
    g_signal_connect (button, "clicked",
                      G_CALLBACK (exit),
                      notebook);
    gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 1, 2);
    gtk_widget_show (button);
    
    entry = gtk_entry_new();
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (callback), entry);
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (currentPage), notebook);
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK (insert_text), textview);
	
    gtk_signal_connect(GTK_OBJECT (entry), "activate", G_CALLBACK(emptyentry), entry);
    gtk_table_attach_defaults (GTK_TABLE (table), entry, 2, 3, 1, 2);
    gtk_widget_show (entry);

    sendbutton  = gtk_button_new_with_label ("Send");
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (callback), entry);
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (insert_text), textview);
    g_signal_connect (sendbutton, "clicked", G_CALLBACK (emptyentry), entry);
    gtk_table_attach_defaults (GTK_TABLE (table), sendbutton, 3, 4, 1, 2);
    gtk_widget_show (sendbutton);

    gtk_widget_show (table);
    gtk_widget_show (window);
   
    gtk_main(); 
    return 0;
}

void add_friend_callback(GtkWidget *widget, GtkWidget *entry){
	menuChoice = 5; //add a friend
	//flag = 1; //for friends list
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
	sprintf(addfriend, "%s", entry_text);
	printf("Added friend: %s\n", addfriend);

}

void delete_friend_callback(GtkWidget *widget, GtkWidget *entry){
	menuChoice = 6; //delete a friend in client
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
	sprintf(addfriend, "%s", entry_text);
	printf("Deleted friend: %s\n", addfriend);
}

void chat_callback(GtkWidget *widget, GtkWidget *entry){
	const gchar *entry_text;
	entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
	sprintf(chatfriend, "%s", entry_text);
	printf("You want to message: %s\n", chatfriend);
	/*if (strcmp(chatfriend, "user1") == 0){
		menuChoice = 3; //this is for client to message
		chat(0, NULL);
	}
	if (strcmp(chatfriend, "user2") == 0){
		chat2(0, NULL);
	}
	if (strcmp(chatfriend, "user3") == 0){
		chat3(0, NULL);
	}*/
}

void addFriend(int argc, char *argv[]){
	gtk_init(&argc, &argv);
	GtkWidget *Window;
	GtkWidget *Entry;
	GtkWidget *frame;
	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(Window), "Add a Friend");
	g_signal_connect (Window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	frame = gtk_frame_new("Enter username");
	gtk_container_add(GTK_CONTAINER(Window), frame);
	
	Entry = gtk_entry_new();
	gtk_signal_connect (GTK_OBJECT (Entry), "activate", G_CALLBACK (add_friend_callback), Entry);
	gtk_signal_connect (GTK_OBJECT (Entry), "activate", G_CALLBACK (emptyentry), Entry);
	g_signal_connect (Window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (GTK_OBJECT(Entry), "activate", G_CALLBACK (gtk_widget_destroy), Window); //closes window on button click
	gtk_container_add(GTK_CONTAINER(frame), Entry);
	gtk_widget_show_all(Window);
	gtk_main();

}

void deleteFriend(int argc, char *argv[]){
	gtk_init(&argc, &argv);
	GtkWidget *Window;
	GtkWidget *Entry;
	GtkWidget *frame;
	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(Window), "Remove a Friend");
	g_signal_connect (Window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	frame = gtk_frame_new("Enter username");
	gtk_container_add(GTK_CONTAINER(Window), frame);
	
	Entry = gtk_entry_new();
	gtk_signal_connect (GTK_OBJECT (Entry), "activate", G_CALLBACK (delete_friend_callback), Entry);
	gtk_signal_connect (GTK_OBJECT (Entry), "activate", G_CALLBACK (emptyentry), Entry);
	g_signal_connect (Window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (GTK_OBJECT(Entry), "activate", G_CALLBACK (gtk_widget_destroy), Window);
	gtk_container_add(GTK_CONTAINER(frame), Entry);
	gtk_widget_show_all(Window);
	gtk_main();

}

void chatFriend(int argc, char *argv[]){
	gtk_init(&argc, &argv);
	GtkWidget *Window;
	GtkWidget *Entry;
	GtkWidget *frame;
	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(Window), "Chat with a Friend");
	g_signal_connect (Window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	frame = gtk_frame_new("Enter username");
	gtk_container_add(GTK_CONTAINER(Window), frame);

	
	Entry = gtk_entry_new();
	gtk_signal_connect (GTK_OBJECT (Entry), "activate", G_CALLBACK (chat_callback), Entry);
	gtk_signal_connect (GTK_OBJECT (Entry), "activate", G_CALLBACK (emptyentry), Entry);
	//g_signal_connect (Window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (GTK_OBJECT(Entry), "activate", G_CALLBACK (gtk_widget_destroy), Window);
	gtk_container_add(GTK_CONTAINER(frame), Entry);
	gtk_widget_show_all(Window);
	//g_signal_connect_swapped (GTK_OBJECT(Entry), "activate", G_CALLBACK (gtk_widget_destroy), Window); //closes window on button click
	gtk_main();

}

int UI(int argc, char *argv[]){
	GtkWidget *window;
	GtkWidget *Vbox;
	GtkWidget *Button1;
	GtkWidget *Button2;
	GtkWidget *Button3;
	GtkWidget *Button4;
	GtkWidget *Button5;
	GtkWidget *Button6;
	GtkWidget *Frame;
	GtkWidget *Textview;	
	GtkWidget *Scroll;	

	gtk_init(&argc, &argv);


	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title(GTK_WINDOW(window), "Chatty Chess");

	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);	

	gtk_window_set_default_size(GTK_WINDOW(window), 300, 600);
	gtk_container_set_border_width(GTK_CONTAINER(window), 10);
	g_signal_connect (window, "destroy",G_CALLBACK (gtk_main_quit), NULL);
	Vbox = gtk_vbox_new(TRUE, 15);
	gtk_container_add(GTK_CONTAINER(window), Vbox);

	Frame = gtk_frame_new("Friends List");
	gtk_container_add(GTK_CONTAINER(Vbox), Frame);

	Textview = gtk_text_view_new();
	Scroll = gtk_scrolled_window_new (NULL, NULL);
   	gtk_container_add (GTK_CONTAINER (Scroll), Textview);
	gtk_container_add(GTK_CONTAINER(Frame), Scroll);
	gtk_text_view_set_editable (GTK_TEXT_VIEW(Textview), FALSE);

// friends list
	const gchar *friends;
	char fname[30];
	char frid[10];
	FILE *fd;
    strncpy(friendlist, "", 200);
	strncpy(fname, loginentry, 10);
	strcat(fname, "Friends.txt");
	fd = fopen(fname, "a+");
	while(!feof(fd)){
    	if(fgets(frid, 10, fd) != NULL){
        	strcat(friendlist, frid);
    	}
	}
	fclose(fd);
	
	friends = friendlist;	
	
	//write to textentry
	GtkTextBuffer *buffer;
	GtkTextMark *mark;
	GtkTextIter iter;
	
	buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (Textview));

	mark = gtk_text_buffer_get_insert(buffer);
	gtk_text_buffer_get_iter_at_mark (buffer, &iter, mark);
	gtk_text_buffer_insert (buffer, &iter, friends, -1);

// end of friends list

	Button1 = gtk_button_new_with_label("Add a Friend");
	gtk_container_add(GTK_CONTAINER(Vbox), Button1);	
//	g_signal_connect(Button1, "clicked", G_CALLBACK(friends_list), Textview);
	g_signal_connect(Button1, "clicked", G_CALLBACK(addFriend), window);
    g_signal_connect(Button1, "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect_swapped (Button1, "clicked", G_CALLBACK (gtk_widget_destroy), window); //closes window on button click

	Button2 = gtk_button_new_with_label("Play Chess");
	gtk_container_add(GTK_CONTAINER(Vbox), Button2);
	g_signal_connect(Button2, "clicked", G_CALLBACK(chess), window);
	g_signal_connect(Button2, "clicked", G_CALLBACK(gtk_main_quit), NULL);
        g_signal_connect_swapped (Button2, "clicked", G_CALLBACK (gtk_widget_destroy), window);
		
	Button3 = gtk_button_new_with_label("Send Message");
	gtk_container_add(GTK_CONTAINER(Vbox), Button3);
	g_signal_connect(Button3, "clicked", G_CALLBACK(chatFriend), window);
	g_signal_connect(Button3, "clicked", G_CALLBACK(openchat), window);
    g_signal_connect(Button3, "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect_swapped (Button3, "clicked", G_CALLBACK (gtk_widget_destroy), window);

	Button5 = gtk_button_new_with_label("Remove a Friend");
	gtk_container_add(GTK_CONTAINER(Vbox), Button5);
	g_signal_connect(Button5, "clicked", G_CALLBACK(deleteFriend), window);
    g_signal_connect(Button5, "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect_swapped (Button5, "clicked", G_CALLBACK (gtk_widget_destroy), window);
	
	Button4 = gtk_button_new_with_label("Log Out");
	gtk_container_add(GTK_CONTAINER(Vbox), Button4);
	g_signal_connect(Button4, "clicked", G_CALLBACK(quitprogram), window);
	g_signal_connect(Button4, "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect_swapped (Button4, "clicked", G_CALLBACK (gtk_widget_destroy), window);

	Button6 = gtk_button_new_with_label("Refresh");
	gtk_container_add(GTK_CONTAINER(Vbox), Button6);
	g_signal_connect(Button6, "clicked", G_CALLBACK(resetUI), NULL);
	g_signal_connect(Button6, "clicked", G_CALLBACK(gtk_main_quit), NULL);
	g_signal_connect_swapped (Button6, "clicked", G_CALLBACK (gtk_widget_destroy), window);
//	VBox = gtk_vbox_new(TRUE, 10);
//	gtk_container_add(GTK_Container(window), VBox);

	gtk_widget_show_all(window);
	gtk_main();
	//UpdateWindow();
	//gtk_main_iteration();

	return 0;
}
	
int GUImain(int argc, char *argv[]){
	GtkWidget *Window;
	GtkWidget *hbox;
	GtkWidget *hbox1;
	GtkWidget *vbox;
	GtkWidget *vbox1;
	GtkWidget *vbox2;
	GtkWidget *label;
	GtkWidget *label1;
	GtkWidget *label2;
	GtkWidget *button1;
	GtkWidget *button2;
	//GtkWidget *entry1;
	//GtkWidget *entry2;

	Entry *e = g_slice_new (Entry);
		
	gtk_init(&argc, &argv);

	/* create a new window */
	Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(Window), "Chatty Chess");
	gtk_window_set_position(GTK_WINDOW(Window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(Window), 600, 300);
	gtk_container_set_border_width(GTK_CONTAINER(Window), 10);
	g_signal_connect (Window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

	/* add boxes */
	vbox = gtk_vbox_new(TRUE, 15);
	gtk_container_add(GTK_CONTAINER(Window), vbox);
	
	label = gtk_label_new("Welcome to Chatty Chess!");
    gtk_box_pack_start (GTK_BOX (vbox), label, TRUE, TRUE, 0);
	
	hbox = gtk_hbox_new(TRUE, 15);
	gtk_container_add(GTK_CONTAINER(vbox), hbox);
	
    hbox1 = gtk_hbox_new (TRUE, 15);
    gtk_container_add (GTK_CONTAINER (vbox), hbox1); //adds vbox within hbox
	
    vbox1 = gtk_vbox_new (TRUE, 15);
    gtk_container_add (GTK_CONTAINER (hbox), vbox1); //adds vbox within hbox
	
	vbox2 = gtk_vbox_new(TRUE, 15);
	gtk_container_add(GTK_CONTAINER(hbox), vbox2);

	/* add labels */
	label1 = gtk_label_new("Username: ");
    gtk_box_pack_start (GTK_BOX (vbox1), label1, TRUE, TRUE, 0);

	label2 = gtk_label_new("Password: ");
    gtk_box_pack_start (GTK_BOX (vbox1), label2, TRUE, TRUE, 0);

	/* add text entries */
    e->entry1 = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (e->entry1), 9);
	gtk_signal_connect(GTK_OBJECT (e->entry1), "activate", G_CALLBACK (login_callback), e->entry1);
    gtk_box_pack_start (GTK_BOX (vbox2), e->entry1, TRUE, TRUE, 0);

    e->entry2 = gtk_entry_new();
    gtk_entry_set_max_length (GTK_ENTRY (e->entry2), 9);
	gtk_signal_connect(GTK_OBJECT (e->entry2), "activate", G_CALLBACK (password_callback), e->entry2);
  	gtk_entry_set_visibility (GTK_ENTRY (e->entry2), FALSE);
    gtk_box_pack_start (GTK_BOX (vbox2), e->entry2, TRUE, TRUE, 0);

	/* add buttons */
	button1 = gtk_button_new_with_label("Login");
    gtk_box_pack_start (GTK_BOX (hbox1), button1, TRUE, TRUE, 0);
    g_signal_connect (button1, "clicked", G_CALLBACK (login_callback), e->entry1);
    g_signal_connect (button1, "clicked", G_CALLBACK (password_callback), e->entry2);
	//g_signal_connect (button1, "clicked", G_CALLBACK(friends_list), Textview); // prints friendlist
	g_signal_connect (button1, "clicked", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (button1, "clicked", G_CALLBACK (gtk_widget_destroy), Window); //closes window on button click
	//g_signal_connect (button1, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    //g_signal_connect (button1, "clicked", G_CALLBACK (gtk_widget_destroy), Window); //this deletes a button
	//g_signal_connect (button1, "clicked", G_CALLBACK (UI), NULL);

	button2 = gtk_button_new_with_label("Register");
    gtk_box_pack_start (GTK_BOX (hbox1), button2, TRUE, TRUE, 0);
    g_signal_connect (button2, "clicked", G_CALLBACK (create_login_callback), e->entry1);
    g_signal_connect (button2, "clicked", G_CALLBACK (create_password_callback), e->entry2);
	//g_signal_connect (button2, "clicked", G_CALLBACK (UI), NULL); 	
	g_signal_connect (button2, "clicked", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect_swapped (button2, "clicked", G_CALLBACK (gtk_widget_destroy), Window); //closes window on button click
	/* show widgets */
	gtk_widget_show_all(Window);

	gtk_main();

return 0;
}
