#include <sys/types.h>
#include <sys/socket.h> 
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "GUI.h"
#include "Chess.h"
#define SIZE 10240


void Menu();
void mainMenu(char protocol[256], char username[10]);
void bzero();

int testint = 0;
                //char tmp[256] = "";
                //tmp = "";
char tmp[256] = "";
char shmaddr[SIZE];
int main(int argc, char *argv[])
{ 
    struct hostent *server;
    int sockfd;
    int len, PORT = 0;
    struct sockaddr_in address;
    int result;
    printf("Please enter a Port number: ");
    scanf("%d",&PORT);

     argv[1] = "zuma.eecs.uci.edu"; //hard coded IP address to zuma
     server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, host not found\n");
        exit(0);
    }
        
    bzero((char*)&address, sizeof(address));    
//    memset((char*)&address, sizeof(address));

    sockfd = socket(AF_INET,SOCK_STREAM, 0); //open the socket
    if (sockfd < 0)
        perror("ERROR opening socket");

    address.sin_family = AF_INET; //assign socket IP address
    
    address.sin_addr = *(struct in_addr*)server->h_addr_list[0];
    
    address.sin_port = htons(PORT); //assign port number to the socket
    
    char buf[100]; //support messages up to 100 characters
    memset(buf,0,100);
    int i=0;
    
    int menu = 0;
    char name[10];
    char password[10];
    int login = 0;
    int logout = 0;
    char protocol[256] = "";

	GUImain(0, NULL);
    
	if(menuChoice == 1)
    {
        while(menu == 0)
        {
		sprintf(name, "%s", loginentry);
		sprintf(password, "%s", passentry);
    	        if((strlen(loginentry) < 10) && (strlen(passentry) < 10))    //breaks out of while loop if they are 9 characters or shorter
    	        {
                    strncpy(protocol,"CRT_",256);
                    strcat(protocol,name);
                    strcat(protocol,"_");
                    strcat(protocol,password);
                    strcat(protocol,"\n");
                    printf("%s",protocol);
                    //SEND TO SERVER AND CONFIRM THAT USERNAME DOES NOT EXIST
                    login = 1; 
                    menu++;
                    break;
                }
            printf("Name or Password are too long. Try Again.\n");
            GUImain(0, NULL);
        }
         
    }
    else if(menuChoice == 2)
    {
        while(menu == 0)                                      //Checks if username/pass are valid length
        {
		sprintf(name, "%s", loginentry);
		sprintf(password, "%s", passentry);
    	        if((strlen(name) < 10) && (strlen(password) < 10))    //breaks out of while loop if they are 9 characters or shorter
    	        {
                    strncpy(protocol,"LGN_",256);
                    strcat(protocol,name);
                    strcat(protocol,"_");
                    strcat(protocol,password);
                    strcat(protocol,"\n");
                    printf("%s",protocol);  
                    //SEND TO SERVER AND CONFIRM THAT USERNAME/PASSWORD DOES NOT EXIST
                    login = 1;       
                    menu++;
                    break;
                }
            printf("Name or Password are too long. Try Again.\n");
            GUImain(0,NULL);
        }
    }
    
    len = sizeof(address);
    
    result = connect(sockfd, (struct sockaddr *) &address, len); 

    if (result == -1)  
    {
      perror("Connect failed");
      return 1;
    }
    else{ 
     printf("%s Logged in:\n",name);
}
  
    pid_t pid1;
   
    pid1=fork();
    if(pid1==-1)
    {
        printf("fork failed");
    }
   
   //client side: waiting for input, input will be put into buffer array and written to shared memory
  // int sendbytes=0;
    if(pid1==0)
    {
                       
       while(1)
        {
             if(logout != 1){
		write(sockfd, protocol, 100); //this sends the protocol to the server
                //write(sockfd, buf, 100); //this sends the message to the clients
             }
                    if(login == 1 && menuChoice != 9){
                        mainMenu(protocol, name);
//			printf("Exited mainMenu. %d\n", menuChoice);
		        //if(menuChoice == 9){
			//    break;}
		    }
                memset(buf,0,100);
        } //end of while(1)    
	//printf("exited while\n"); 
    }//end of pid1 == 0

    //read from the shared memory
    if(pid1>0) {
        while(1)
        {
           read(sockfd,shmaddr,SIZE);
           if(*(shmaddr+i*100)!=0)
            {
                strncpy(protocol, "", 256);
                strncpy(loginentry, "", 10);
                strncpy(passentry, "", 10);
                strncpy(tmp, "", 256);
                strcat(tmp, (shmaddr+i*100));
                i++;
                int j = 0, k = 0;
                char cmd[5];
                while(1){
                    if(tmp[j] != '_'){
                        cmd[k] = tmp[j];
                        cmd[k+1] = 0;
                        j++;
                        k++;
                    }
                    else{
                        j++;
                        k = 0;
                        break;
                    }
                }
#ifdef DEBUG
                printf("%s", tmp);
                printf("%s\n", cmd);
#endif
                if(strcmp(cmd, "SCS") == 0){
                    char msg[256] = "";
                    char rcver[10] = "";
                    while(1){
                        if(tmp[j] != '_'){
                            rcver[k] = tmp[j];
                            rcver[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            j++;
                            k = 0;
                            break;
                        }
                    }
                    if(strcmp(rcver, name) == 0){
                        while(1){
                            if(tmp[j] != '\n'){
                                msg[k] = tmp[j];
                                msg[k+1] = 0;
                                j++;
                                k++;
                            }
                            else{
                                msg[k] = '\n';
                                break;
                            }
                        }
                        //login = 1;
                        char fname[30];
                        FILE *fp;
                        sprintf(fname, "%sFriends.txt", rcver);
                        if((fp = fopen(fname, "a+")) == NULL){
                            printf("Failed to create %s..\n", fname);
                            exit(10);
                        }
                        fclose(fp);
                        printf("%s", msg);
                    }
                }
                else if(strcmp(cmd, "LFL") == 0){//Login failed
                    char msg[256] = "";
                    char rcver[10] = "";
                    while(1){
                        if(tmp[j] != '_'){
                            rcver[k] = tmp[j];
                            rcver[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            j++;
                            k = 0;
                            break;
                        }
                    }
                    if(strcmp(rcver, name) == 0){
                        while(1){
                            if(tmp[j] != '\n'){
                                msg[k] = tmp[j];
                                msg[k+1] = 0;
                                j++;
                                k++;
                            }
                            else{
                                msg[k] = '\n';
                                break;
                            }
                        }
                        printf("%s", msg);
                        //login = 1;
                        //close(sockfd);
                        //exit(0);
                    }
                }
                else if(strcmp(cmd, "CFL") == 0){//Register failed
                    char msg[256] = "";
                    char rcver[10] = "";
                    while(1){
                        if(tmp[j] != '_'){
                            rcver[k] = tmp[j];
                            rcver[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            j++;
                            k = 0;
                            break;
                        }
                    }
                    if(strcmp(rcver, name) == 0){
                        while(1){
                            if(tmp[j] != '\n'){
                                msg[k] = tmp[j];
                                msg[k+1] = 0;
                                j++;
                                k++;
                            }
                            else{
                                msg[k] = '\n';
                                break;
                            }
                        }
                        printf("%s", msg);
                        //login = 1;
                        //close(sockfd);
                        //exit(0);
                    }
                }
                else if((strcmp(cmd, "RFL") == 0) || (strcmp(cmd, "AFL") == 0)){
                    char msg[256] = "";
                    char rcver[10] = "";
                    while(1){
                        if(tmp[j] != '_'){
                            rcver[k] = tmp[j];
                            rcver[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            j++;
                            k = 0;
                            break;
                        }
                    }
                    if(strcmp(rcver, name) == 0){
                        while(1){
                            if(tmp[j] != '\n'){
                                msg[k] = tmp[j];
                                msg[k+1] = 0;
                                j++;
                                k++;
                            }
                            else{
                                msg[k] = '\n';
                                break;
                            }
                        }
                        printf("%s", msg);
                    }
                }
                else if(strcmp(cmd, "ASC") == 0){//Add friend succeeded
                    char username1[10];
                    char username2[10];
                    char fname[30] = "";
                    FILE *fp;
                    while(1){
                        if(tmp[j] != '_'){
                            username1[k] = tmp[j];
                            username1[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            j++;
                            k = 0;
                            break;
                        }
                    }
                    while(1){
                        if(tmp[j] != '\n'){
                            username2[k] = tmp[j];
                            username2[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            break;
                        }
                    }
                    if(strcmp(username1, name) == 0){
                        strncpy(fname, username1, 10);
                        strcat(fname, "Friends.txt");
                        if((fp = fopen(fname, "a+")) == NULL){
                            printf("Failed to open %s..\n", fname);
                            printf("Aborting..");
                            exit(10);
                        }
                        fprintf(fp, username2);
                        fprintf(fp, "\n");
                        fclose(fp);
                        printf("%s is added to your friend list\n", username2);
                    }
                    else if(strcmp(username2, name) == 0){
                        strncpy(fname, username2, 10);
                        strcat(fname, "Friends.txt");
                        if((fp = fopen(fname, "a+")) == NULL){
                            printf("Failed to open %s..\n", fname);
                            printf("Aborting..");
                            exit(10);
                        }
                        fprintf(fp, username1);
                        fprintf(fp, "\n");
                        fclose(fp);
                        printf("%s is added to your friend list\n", username1);
                    }
                }
                else if(strcmp(cmd, "RSC") == 0){//Add friend succeeded
                    char username1[10];
                    char username2[10];
                    char fname1[30] = "";
                    char fname2[30] = "";
                    FILE *fp;
                    while(1){
                        if(tmp[j] != '_'){
                            username1[k] = tmp[j];
                            username1[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            j++;
                            k = 0;
                            break;
                        }
                    }
                    while(1){
                        if(tmp[j] != '\n'){
                            username2[k] = tmp[j];
                            username2[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            break;
                        }
                    }
                    if(strcmp(username1, name) == 0){
                        FILE *fn;
                        char nfname[30] = "NewFriends.txt";
                        char uid[10];
                        sprintf(fname1, "%sFriends.txt", username1);
                        if((fp = fopen(fname1, "a+")) == NULL){
                            printf("Failed to open %s..\n", fname1);
                            printf("Aborting..");
                            exit(10);
                        }
                        if((fn = fopen(nfname, "a+")) == NULL){
                            printf("Failed to open %s..\n", nfname);
                            printf("Aborting..");
                            exit(10);
                        }
                        do{
                            int len;
                            if(fgets(uid, 10, fp) != NULL){
                                len = strlen(uid);
                                uid[len-1] = 0;
                                if(strcmp(uid, username2) != 0){
                                    fprintf(fn, uid);
                                    fprintf(fn, "\n");
                                }
                            }
                        }while(!feof(fp));
                        fclose(fn);
                        fclose(fp);
                        remove(fname1);
                        rename(nfname, fname1);
                        printf("%s is removed from your friend list\n", username2);
                    }
                    else if(strcmp(username2, name) == 0){
                        FILE *fn;
                        char nfname[30] = "NewFriends.txt";
                        char uid[10];
                        sprintf(fname2, "%sFriends.txt", username2);
                        if((fp = fopen(fname2, "a+")) == NULL){
                            printf("Failed to open %s..\n", fname2);
                            printf("Aborting..");
                            exit(10);
                        }
                        if((fn = fopen(nfname, "a+")) == NULL){
                            printf("Failed to open %s..\n", nfname);
                            printf("Aborting..");
                            exit(10);
                        }
                        do{
                            int len;
                            if(fgets(uid, 10, fp) != NULL){
                                len = strlen(uid);
                                uid[len-1] = 0;
                                if(strcmp(uid, username2) != 0){
                                    fprintf(fn, uid);
                                    fprintf(fn, "\n");
                                }
                            }
                        }while(!feof(fp));
                        fclose(fn);
                        fclose(fp);
                        remove(fname2);
                        rename(nfname, fname2);
                        printf("%s is removed from your friend list\n", username1);
                    }
                }
		else if(strcmp(cmd, "GYE") == 0){ //start a chess game
		    //char msg[256] = "";
		    char txt[256] = "";
		    while(1){
			if(tmp[j] != '\n'){
			    txt[k] = tmp[j];
			    txt[k+1] = 0;
			    j++;
			    k++;
			}
			else{
			    txt[k] = '\n';
			    break;
			}
		    }
		    printf("%s", txt);
		    char mode = '2'; //start player vs AI mode
		    Chessmain(mode);
		}	    
                else if(strcmp(cmd, "MSG") == 0){
                    char sender[10] = "";
                    char rcver[10] = "";
                    char msg[256] = "";
                    char txt[256] = "";
                    while(1){
                        if(tmp[j] != '_'){
                            sender[k] = tmp[j];
                            sender[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            j++;
                            k = 0;
                            break;
                        }
                    }
                  
                    while(1){
                        if(tmp[j] != '_'){
                            rcver[k] = tmp[j];
                            rcver[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            j++;
                            k = 0;
                            break;
                        }
                    }
                 
                    if((strcmp(sender, name) == 0)||(strcmp(rcver, name) == 0)){
                        char fname[50] = "";
                        if(strcmp(sender, name) == 0){
                            strcat(fname, sender);
                            strcat(fname, "_");
                            strcat(fname, rcver);
                            strcat(fname, "_MSG.txt");
                        }
                        else if(strcmp(rcver, name) == 0){
                            strcat(fname, rcver);
                            strcat(fname, "_");
                            strcat(fname, sender);
                            strcat(fname, "_MSG.txt");
                        }
                        /*printf("This is fname: %s",fname);
                        sprintf(fnamechat,"%s",fname);
                        printf("This is fnamechat: %s",fnamechat);*/
                        while(1){
                            if(tmp[j] != '\n'){
                                msg[k] = tmp[j];
                                msg[k+1] = 0;
                                j++;
                                k++;
                            }
                            else{
                                msg[k] = '\n';
                                break;
                            }
                        }
                        strcat(txt, sender);
                        strcat(txt, " says: ");
                        strcat(txt, msg);
                        FILE *fp;
                        if((fp = fopen(fname, "a+")) == NULL){
                            printf("Failed to open %s\n", fname);
                            exit(10);
                        }
                        fprintf(fp, txt);
                        fclose(fp);
                        printf(txt);
                    }
                }
                else if(strcmp(cmd, "LGT") == 0){
                    char rcver[10] = "";
                    while(1){
                        if(tmp[j] != '\n'){
                            rcver[k] = tmp[j];
                            rcver[k+1] = 0;
                            j++;
                            k++;
                        }
                        else{
                            break;
                        }
                    }
                    if(strcmp(rcver, name) == 0){
                        printf("%s logout of the program..\n", rcver);
                        strncpy(protocol, "", 256);
                        logout = 1;
                        close(sockfd);
                        exit(0);
                    }
                }
		sprintf(teststring, "%s", tmp);
            }
            
        }
   
    }
/*
    if(menuChoice == 9){
    printf("Client program quitting...\n");
    strncpy(protocol, "LGT_", 256);
    write(sockfd, protocol, 100);}
*/
    close(sockfd); //close socket
    //printf("Client socket closed.\n");
    return 0;
}

void mainMenu(char protocol[256], char username[10])
{
    //int input=0;
    strncpy(protocol, "", 256);
    char message[200]="";
    
    //printf("\nWhat would you like to do?\n1.Add Friend\n2.Remove Friend\n3.Message a friend\n4.Play chess\n");   
    //scanf("%d *[^\n]",&input);
	
        if (testint == 0){
	    UI(0, NULL); //send message sets menuChoice to 3
	}

    if(menuChoice == 5)
    {
       //AddFriend
       strcat(protocol, "ADD_");
       strcat(protocol, username);
       strcat(protocol, "_");
       strcat(protocol, addfriend);
       strcat(protocol, "\n");
       //printf("add friend protocol: %s", protocol);
    }
    else if(menuChoice == 6)
    {
       //RemoveFriend
       strcat(protocol, "RMV_");
       strcat(protocol, username);
       strcat(protocol, "_");
       strcat(protocol, addfriend);
       strcat(protocol, "\n");
    }
    else if(menuChoice == 3)
    {
        ////chatty = 1;
        //while(chatty){
        //    chatty = 0;
            testint = 1;

#ifdef DEBUG
	    printf("tmp is: %s", teststring);
	    printf("User entry is: %s", userentry);
#endif

            chat(0, NULL);
//			printf("chat has ended");
        //}
        strcat(protocol,"MSG_");
        strcat(protocol, username);
        strcat(protocol, "_");
#ifdef DEBUG
	printf("the protocol is ready for cat\n");
#endif
	//Added
	strcat(protocol, chatfriend);
	strcat(protocol, "_");
	sprintf(message, "%s", recententry);
#ifdef DEBUG
        printf("Message is ready\n");
#endif
       //printf("What message would you like to send?\n");
        strcat(protocol,message);
#ifdef DEBUG
	printf("protocol: %s", protocol);
#endif	
    }
    else if(menuChoice == 4)
    {
        strcat(protocol, "GYE_"); //change protocol to GYE (start game of chess), sent to server
    }
    else if(menuChoice == 9)
    {
        //Do not put exit(0) here!!!!!!!!!!
        strcat(protocol, "LGT_");
        strcat(protocol, username);
        strcat(protocol, "\n");
	printf("Quitting!\n");
	printf("hi");
	//exit(0); 
	//assert(menuChoice != 9);
    }
}
