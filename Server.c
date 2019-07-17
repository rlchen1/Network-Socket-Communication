#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <stdio.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h> 
#include <time.h>

//test
#include "UserInfo.h"
#include "User.h"
#include "UserList.h"


//#include "Chess.h"

/*
#include "Constants.h"
#include "CheckMovement.h"
#include "CheckDestination.h"
#include "AIStrategies.h"
*/

//#define PORT    7557
//#define KEY 77776

#define SIZE    10240
//char currentusrmsg[256] = "";
/*
struct PIECE{
	int pts;
	char type;
	char color;
	char col;
	char row;
};

struct MV{
	int* movement;
	int n;
};
 
int Chessmain();
*/
void bzero();
int run = 0;
int recmsg = 0;
int protrcv = 0;
int cmdrcv = 0;
int quit = 0;
char cmd[5] = ""; 
int main()
{  
//    Chessmain();
    ULIST *l;
    FILE *fp;
    int acceptpass;
    int usercount=1;
    int i=0;
    int login = 1;
    char buf[100]; //supports messages up to 100 char
    memset(buf,0,100);
    int s_sockfd,c_sockfd;   //server socket and client socket
    socklen_t server_len, client_len; //define length using socklen_t variable, not int
    int KEY = 0, PORT = 0; //used in shared memory functionality

    srand((unsigned)time(NULL)), KEY = (rand() %100)+ 8362; //CHANGE THE KEY ALGORITHM PERIODICALLY OR SEG FAULT UPON RUNNING SERVER 

   // printf("DEBUG: (server.c 40) Random key generated: %d\n", KEY);
 
/*  printf("Please enter a key number (any 5 digit number): ");
    scanf("%d", &KEY);
*/    char protocol[256];
    //char flag[256];
    printf("Please enter a port number (7000-7999): ");
    scanf("%d", &PORT);
    if((fp = fopen("UserData.txt", "a+")) == NULL){
        printf("Failed to open the data file..\n");
        exit(10);
    }
    
    l = RetrieveData(fp);
    fclose(fp);
#ifdef DEBUG
    PrintList(l);
#endif

    struct sockaddr_in s_sockaddr,c_sockaddr;
    bzero((char *) & s_sockaddr, sizeof( s_sockaddr));
   
    s_sockfd = socket(AF_INET,SOCK_STREAM, 0); //create the server socket
    s_sockaddr.sin_family=AF_INET; //set the IP address for the server socket
    s_sockaddr.sin_port=htons(PORT); //assign a port number to the server socket
    s_sockaddr.sin_addr.s_addr=INADDR_ANY; //incoming IP address

    server_len=sizeof(s_sockaddr);
    //int j=1;
   // setsockopt(server_sockfd,SOL_SOCKET,SO_REUSEADDR,&j,sizeof(j));
if(bind(s_sockfd,(struct sockaddr *)&s_sockaddr,server_len)==-1) //bind socket to server
    {
        perror("bind:");
/*        while(bind(s_sockfd,(struct sockaddr *)&s_sockaddr, server_len) == -1){
		PORT = (rand() % 100) + 7000;
		printf("New port no: %d\n", PORT);
	}
*/      exit(1);
    }
   
   
    if(listen(s_sockfd,5)==-1) //listen on this socket
    {
        perror("listen:");
        exit(1);   
    }
    printf("Listening... %d \n", PORT);
   
//   client_len=sizeof(client_sockaddr);
//   client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_sockaddr,&client_len);
//    pid_t ppid,pid;
  

    int shm;
    char *shmaddr;
//    char shmem[256];
     shm = shmget(KEY,SIZE, IPC_CREAT | 0600);
      if(shm==-1)
    {
        printf("allocate share memory error \n");
    }



    shmaddr= (char *) shmat(shm, 0, 0);//attach shm to shmaddr 
//  shmem[256] = (char *) shmat(shm, 0, 0);


    memset(shmaddr,0,SIZE);//set everything in my share memory to zero
//    memset(shmem, 0, SIZE);
 
   while(1)
   { 
     if(login == 1){
      acceptpass = c_sockfd = accept(s_sockfd,(struct sockaddr *)&c_sockaddr,&client_len);
     }
        if(acceptpass==-1)
        {
             perror("error in accept function:");
             exit(1);
        }

      printf("User %d connected to server\n",usercount);
      usercount++;
   
     // printf("I am parent process,my id: %d\n",getpid());
 
      pid_t pid1,pid2;   
      pid1=fork();
   
      if(pid1==-1)
      {
          printf("fork 1 failed:");
      }
      if(pid1==0) 
      {
          pid2=fork();
          if(pid2==-1)
          {
              printf("fork 2 failed:");
              exit(1);
          }
    
          if(pid2==0) //server receive message
          {  
       //       printf("i am the child2 process, my id: %d\n",getpid());
	      while(1)
              {
                  strncpy(protocol,"",256);
                  recv(c_sockfd,buf,100,0);
                  strncpy(protocol,buf,256);
	          printf("I received your protocol: %s\n",protocol);	
	 //         printf("DEBUG (server.c 149) protocol:%s\n",protocol);	
                  char message[256] = "";
		  int i = 0;
                  int j = 0;
		  while(1){ //Retrieves only the command part of protocol
			if(protocol[i] != '_'){
                            cmd[j] = protocol[i];
                            cmd[j+1] = 0;
                            i++;
                            j++;
                        }
                        else{
                            i++;
                            j=0;
                            break;
                        }
	          }
#ifdef DEBUG  
		printf("%s\n",cmd);
#endif
                //End third nested inner while 
		//Need to change this to only check command part
		//switch protocol to whatver first parsed string is
			if(strcmp(cmd, "LGN") == 0)
                        {
				char username[11];
				char password[11];
       		  		while(1){ //Retrieves username part of protocol
					if(protocol[i] != '_'){
                            		    username[j] = protocol[i];
                                            username[j+1] = 0;
                            		    i++;
                            		    j++;
                        		}
                        		else{
                            		    i++;
                            		    j = 0;
                            		    break;
                        		}
	          		} 
                                printf("User %s is trying to sign in\n", username);
		  		while(1){ //Retrieves password part of protocol
					if(protocol[i] != '\n'){
                            		    password[j] = protocol[i];
                                            password[j+1] = 0;
                            		    i++;
                            		    j++;
                        		}
                        		else{
                            		    i++;
                            		    j = 0;
                            		    break;
                        		}
	          		}
#ifdef DEBUG
                             printf("%s\n%s\n",username,password);
#endif
                             //Check if username/password match textfile 
                             login = LoginCheck(l, username,password); //if 1 flag = "SCS_logged in" also User->status = 1;, if 0 "FAL_pass doesn't match", if -1 flag = "FAL_username not found"
                             if(login == 1){
                                 printf("User %s signed in\n", username);
                                 strncpy(message, "SCS_", 256);
                                 strcat(message, username);
                                 strcat(message, "_");
                                 strcat(message, "You have successfully signed in\n");
                                 UENTRY *e = NULL, *n = NULL;
                                 e = l->First;
                                 while(e){
                                     n = e->Next;
                                     if(strcmp(username, e->user->UserName) == 0){
                                         e->user->Status = 1;
                                         break;
                                     }
                                     e = n;
                                 }
                             }
                             else if(login == 0){
                                 printf("Password for user %s doesn't match\n", username);
                                 strncpy(message, "LFL_", 256);
                                 strcat(message, username);
                                 strcat(message, "_");
                                 strcat(message, "Password doesn't match with the username\n");
                             }
                             else if(login == -1){
                                 printf("This user doesn't exist\n");
                                 strncpy(message, "LFL_", 256);
                                 strcat(message, username);
                                 strcat(message, "_");
                                 strcat(message, "Username doesn't exist\n");
                             }                 
                        }
			else if(strcmp(cmd, "CRT") == 0)
	                {
                            int regflag;
                            char username[11];
                            char password[11];
                            while(1){ //Retrieves username part of protocol
					if(protocol[i] != '_'){
                            		    username[j] = protocol[i];
                                            username[j+1] = 0;
                            		    i++;
                            		    j++;
                        		}
                        		else{
                            		    i++;
                            		    j = 0;
                            		    break;
                        		}
	          		}
                            printf("User %s is trying to register\n", username);
                            while(1){ //Retrieves password part of protocol
					if(protocol[i] != '\n'){
                            		    password[j] = protocol[i];
                                            password[j+1] = 0;
                            		    i++;
                            		    j++;
                        		}
                        		else{
                            		    i++;
                            		    j = 0;
                            		    break;
                        		}
	          		}
                            regflag = RegisterCheck(l,username); 
                            //if 1 flag = "SCS_you are now registered" if 0 flag = "FAL_Username exists."
                            if(regflag == 1){ 
                                 USER *u = NewUser(username,password);
                                 AppendEntry(l,u);
                                 if((fp = fopen("UserData.txt", "a+"))==NULL){
                                     printf("Failed to open data file while registering..\n");
                                     printf("Shutting down the server..\n");
                                     exit(10);
                                 }
                                 fprintf(fp, username);
                                 fprintf(fp, "\n");
                                 fprintf(fp, password);
                                 fprintf(fp, "\n");
                                 fclose(fp);
                                 //Connect them to server and User->status = 1;
                                 UENTRY *e = NULL, *n = NULL;
                                 e = l->First;
                                 while(e){
                                     n = e->Next;
                                     if(strcmp(username, e->user->UserName) == 0){
                                         e->user->Status = 1;
                                         break;
                                     }
                                     e = n;
                                 }
                                 strncpy(message, "SCS_", 256);
                                 strcat(message, username);
                                 strcat(message, "_");
                                 strcat(message, "You have sucessfully registered\n");
                            }
                            else{
                                printf("User already existed\n");
                                strncpy(message, "CFL_", 256);
                                strcat(message, username);
                                strcat(message, "_");
                                strcat(message, "Username already exists in the system\n");
                            }
                        }  
			else if(strcmp(cmd, "ADD") == 0)
			{
                            int Ucheck;
                            char username1[11];
                            char username2[11];
                            while(1){ //Retrieves username1 part of protocol
					if(protocol[i] != '_'){
                            		    username1[j] = protocol[i];
                                            username1[j+1] = 0;
                            		    i++;
                            		    j++;
                        		}
                        		else{
                            		    i++;
                            		    j = 0;
                            		    break;
                        		}
	          		}
                            while(1){ //Retrieves username2 part of protocol
					if(protocol[i] != '\n'){
                            		    username2[j] = protocol[i];
                                            username2[j+1] = 0;
                            		    i++;
                            		    j++;
                        		}
                        		else{
                            		    i++;
                            		    j = 0;
                            		    break;
                        		}
	          		}
                            if(strcmp(username1, username2) != 0){
                                Ucheck = RegisterCheck(l,username2);
                                //printf("Ucheck = %d\n", Ucheck);
                                PrintList(l);
                                if(Ucheck == 0){
                                    printf("User %s is trying to add user %s as friend\n", username1, username2);
                                    int flag1 = 0, flag2 = 0;
                                    UENTRY *e = NULL, *n = NULL;
                                    e = l->First;
                                    while(e){
                                        char fname[40] = "";
                                        //int cCheck;
                                        n = e->Next;
                                        if(strcmp(username1, e->user->UserName) == 0){
                                            //The code inside the following if block only runs when
                                            //the given username doesn't exist in the contact list
                                            int Check;
                                            Check = ContactCheck(e->user->Friends,username2);
                                            //printf("Check1: %d\n", Check);
                                            if(Check == 0){
                                                CONTACT *ct1 = NULL;
                                                ct1 = NewContact(username2);//Create a new contact info
                                                AppendCEntry(e->user->Friends, ct1);//Append the info into the friend list
                                                strncpy(fname, "S-", 30);
                                                strcat(fname, username1);    //Create the name of file
                                                strcat(fname, "Friends.txt");//which holds the contact info of a user
                                                if((fp = fopen(fname, "a+")) == NULL){
                                                    printf("Failed to open %s..\n", fname);
                                                    printf("Shutting down the server..\n");
                                                    exit(10);
                                                }
                                                fprintf(fp, username2);//Print the given username to the file
                                                fprintf(fp, "\n");
                                                fclose(fp);//Close the file
                                                flag1 = 1;
                                                printf("%s is added to %s's friend list\n", username2, username1);
                                            }
                                            else{
                                                printf("%s already exists in %s's friend list\n", username2, username1);
                                            }
                                        }
                                        else if(strcmp(username2, e->user->UserName) == 0){
                                            int Check;
                                            Check = ContactCheck(e->user->Friends, username1);
                                            //printf("Check2: %d\n", Check);
                                            if(Check == 0){
                                                CONTACT *ct2 = NULL;
                                                ct2 = NewContact(username1);
                                                AppendCEntry(e->user->Friends, ct2);
                                                strncpy(fname, "S-", 30);
                                                strcat(fname, username2);
                                                strcat(fname, "Friends.txt");
                                                if((fp = fopen(fname, "a+")) == NULL){
                                                    printf("Failed to open %s..\n", fname);
                                                    printf("Shutting down the server..\n");
                                                    exit(10);
                                                }
                                                fprintf(fp, username1);
                                                fprintf(fp, "\n");
                                                fclose(fp);
                                                flag2 = 1;
                                                printf("%s is added to %s's friend list\n", username1, username2);
                                            }
                                            else{
                                                printf("%s already exists in %s's friend list\n", username1, username2);
                                            }
                                        }
                                        e = n;
                                    }
                                    //printf("flag1: %d, flag2: %d\n", flag1, flag2);
                                    if((flag1 == 1) && (flag2 == 1)){
                                        strncpy(message, "ASC_", 256);
                                        strcat(message, username1);
                                        strcat(message, "_");
                                        strcat(message, username2);
                                        strcat(message, "\n");
                                    }
                                    else{
                                        printf("%s already exist in%s's firend list\n", username2, username1);
                                        sprintf(message, "AFL_%s_%s already exists in your friend list\n", username1, username2);
                                    }
                                }
                                else{
                                    printf("User %s doesn't exist\n", username2);
                                    sprintf(message, "AFL_%s_%s doesn't exist\n", username1, username2);
                                }
                            }
                            else{
                                printf("%s attempted to add himself to his contact list\n", username1);
                                sprintf(message, "AFL_%s_You cannot add yourself to your friend list\n", username1);
                            }
                            //Send REQ_user1_user2
                            //Receive another string with "YES_user2_user1" or "NO!_user2_user1"
                            
                        }                            	
	                else if(strcmp(protocol,"FYE") == 0) //yes friend request
                        {
                            //CONTACT *c1 = NewContact(username2);
                            //CONTACT *c2 = NewContact(username1);
                            //AppendCEntry(username1->Friends, c1);
                            //AppendCEntry(username2->Friends, c2);
                            //add user2 to user1Friends.txt  
                            //add user1 to user1Friends.txt
                            
   
                        }
                        else if(strcmp(protocol, "FNO") == 0) //no friend request
                        {
                             //go through program like normal as if nothing happened
                        }
                        else if(strcmp(cmd, "GYE") == 0)//yes game request
                        {
                            //run chess
                            //message[256] = "Starting a game of chess.";
                            //strcpy(shmaddr+i*100, "Starting a game of chess."); 
			    //write(c_sockfd, "Starting a game of chess.", 100);
			    printf("User wants to start a game of chess.\n");
			    strncpy(message, "GYE_", 256);
			    strcat(message, "Starting chess...\n");
                        }
                        else if(strcmp(protocol, "GNO") == 0) //no game request
                        {
                            //Tell user 1 "FAL_GAME DENIED"
                        }
			else if(strcmp(cmd, "RMV") == 0)
			{
                            int uCheck;
                            char username1[10];
                            char username2[10];
                            while(1){ //Retrieves username1 part of protocol
					if(protocol[i] != '_'){
                            		    username1[j] = protocol[i];
                                            username1[j+1] = 0;
                            		    i++;
                            		    j++;
                        		}
                        		else{
                            		    i++;
                            		    j = 0;
                            		    break;
                        		}
	          		}
                            while(1){ //Retrieves username2 part of protocol
					if(protocol[i] != '\n'){
                            		    username2[j] = protocol[i];
                                            username2[j+1] = 0;
                            		    i++;
                            		    j++;
                        		}
                        		else{
                            		    break;
                        		}
	          		}
                            if(strcmp(username1, username2) != 0){
                                uCheck = RegisterCheck(l, username2);
                                if(uCheck == 0){
                                    int flag1 = 0, flag2 = 0;
                                    UENTRY *e = NULL, *n = NULL;
                                    e = l->First;
                                    while(e){
                                        n = e->Next;
                                        if(strcmp(username1, e->user->UserName) == 0){//Look for username1 in the struct
                                            int cCheck1;
                                            cCheck1 = ContactCheck(e->user->Friends, username2);
                                            if(cCheck1 == 1){//Check if username2 exists in username1's contact list
                                                CENTRY *ce1 = NULL, *cn1 = NULL;
                                                ce1 = e->user->Friends->First;
                                                while(ce1){
                                                    cn1 = ce1->Next;
                                                    if(strcmp(username2, ce1->contact->UserName) == 0){//Look for username2
                                                        CONTACT *ct1 = NULL;
                                                        ct1 = RemoveCEntry(e->user->Friends, ce1);//Remove the entry correspond
                                                                                                  //to username2
                                                        RemoveContact(ct1);//Remove the contact info
                                                        char fname1[40];
                                                        sprintf(fname1, "S-%sFriends.txt", username1);
                                                        remove(fname1);    //Delete the corresponding file
                                                        FILE *fp;
                                                        fp = fopen(fname1, "a+"); //Recreate the file
                                                        CENTRY *de1 = NULL, *dn1 = NULL;
                                                        de1 = e->user->Friends->First;
                                                        while(de1){
                                                            dn1 = de1->Next;
                                                            fprintf(fp, de1->contact->UserName);
                                                            fprintf(fp, "\n");
                                                            de1 = dn1;
                                                        }
                                                        fclose(fp);
                                                        flag1 = 1;
                                                        printf("%s is deleted from %s's contact list\n", username2, username1);
                                                        break;
                                                    }
                                                    ce1 = cn1;
                                                }
                                            }
                                        }
                                        else if(strcmp(username2, e->user->UserName) == 0){//Look for username2 in the struct
                                            int cCheck;
                                            cCheck = ContactCheck(e->user->Friends, username1);
                                            if(cCheck == 1){//Check if username1 exists in
                                                                                               //username2's contact list
                                                CENTRY *ce2 = NULL, *cn2 = NULL;
                                                ce2 = e->user->Friends->First;
                                                while(ce2){
                                                    cn2 = ce2->Next;
                                                    if(strcmp(username1, ce2->contact->UserName) == 0){//Look for username1
                                                        CONTACT *ct2 = NULL;
                                                        ct2 = RemoveCEntry(e->user->Friends, ce2);//Remove the entry correspond
                                                                                                  //to username1
                                                        RemoveContact(ct2);//Remove the contact info
                                                        char fname2[40];
                                                        sprintf(fname2, "S-%sFriends.txt", username2);
                                                        remove(fname2); //Delete the corresponding file
                                                        FILE *fp;
                                                        fp = fopen(fname2, "a+"); //Recreate the file
                                                        CENTRY *de = NULL, *dn = NULL;
                                                        de = e->user->Friends->First;
                                                        while(de){
                                                            dn = de->Next;
                                                            fprintf(fp, de->contact->UserName);
                                                            fprintf(fp, "\n");
                                                            de = dn;
                                                        }
                                                        fclose(fp);
                                                        flag2 = 1;
                                                        printf("%s is deleted from %s's contact list\n", username1, username2);
                                                        break;
                                                    }
                                                    ce2 = cn2;
                                                }
                                            }
                                        }
                                        e = n;
                                    }
                                    if((flag1 == 1) && (flag2 == 1)){
                                        strncpy(message, "RSC_", 256);
                                        strcat(message, username1);
                                        strcat(message, "_");
                                        strcat(message, username2);
                                        strcat(message, "\n");
                                    }
                                    else{
                                        printf("%s has been deleted from %s's friend list\n", username2, username1);
                                        sprintf(message, "RFL_%s_%s has been deleted from your friend list\n", username1, username2);
                                    }
                                }
                                else{
                                    printf("%s doesn't exist\n", username2);
                                    sprintf(message, "RFL_%s_%s doesn't exist\n", username1, username2);
                                }
                            }
                            else{
                                printf("%s is attempting to delete himself from his friend list\n", username1);
                                sprintf(message, "RFL_%s_You cannot remove yourself from your friend list\n", username1);
                            }
                        }	
			else if(strcmp(cmd, "MSG") == 0)
			{
                            printf("I have received your message: %s",protocol);
                            strncpy(message, protocol, 256);
                        }
			else if(strcmp(cmd, "GRQ") == 0)
			{
                             //Send to other person
                             //parse in client and handle there
                        }                         
			else if(strcmp(cmd, "LGT") == 0)
			{
                             //disconnect client
                             //set User->status = 0;
                             char username[10];
                             while(1){
                                 if(protocol[i] != '\n'){
                                     username[j] = protocol[i];
                                     username[j+1] = 0;
                                     i++;
                                     j++;
                                 }
                                 else{
                                     break;
                                 }
                             }
                             printf("%s is trying to logout\n", username);
                             if(RegisterCheck(l, username) == 0){
                                 UENTRY *e = NULL, *n = NULL;
                                 e = l->First;
                                 while(e){
                                     n = e->Next;
                                     if(strcmp(username, e->user->UserName) == 0){
                                         if(e->user->Status == 1){
                                             printf("Closing client connection.\n");
                                             strncpy(message, "LGT_", 256);
                                             strcat(message, username);
                                             strcat(message, "\n");
                                             e->user->Status = 0;
                                             printf("%s logged out\n", username);
                                             close(c_sockfd);
                                             strncpy(protocol,"", 256); 
			                     break;
                                         }
                                         else{
                                             printf("%s already signed out\n", username);
                                             close(c_sockfd);
                                             strncpy(protocol,"", 256); 
                                             break;
                                         }
                                     }
                                     e = n;
                                 }
                             }
			//break;
                        }
			
              
               for(i=0;i<SIZE;i++)
                 {
               if(*(shmaddr+i*100)==0){
                  strcpy(shmaddr+i*100,message);
		  break;
                 } //end if
                } //end for

     } //END 2ND NESTED INNER WHILE         
               

            } //end if pid(2 == 0)

//still currently nested in pid1 == 0) 

    if(pid2>0) //writing 
    {
//	  printf("i am the child1 process, my id: %d\n",getpid());
          while(1)
            {
                if(*(shmaddr+i*100)!=0){
                   write(c_sockfd,shmaddr,SIZE);
             //  {write(c_sockfd,shmaddr+i*100, SIZE);
		 i++;
                  // memset(shmaddr,0,SIZE);
                   }   //end if      
                   
                            
            } //end while(1)
     }    //end if (pid2 > 0)      
    } //end if pid1 == 0
    
//    } //comment out for error?
   
//no more nested here 
//
    if(pid1>0)  //close the client socket
    {
        close(c_sockfd);
    } //end pid1 > 0
       
} //end first while
//return 0;
}
