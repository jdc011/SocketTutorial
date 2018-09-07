/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
                                  server.c
--------------------------------------------------------------------------------
Author:  Jeremy Cruz

Date:    30, August 2018

Purpose: This is a server for the purpose of demonstrating Socket programming.
         This program listens for clients on port 3000 from local host. It will
         expect the client to send it a message and print the message to stdout.
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~*/

/* Basic libraries needed for socket programming */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------
Function:   main

Parameters: Default, not used.

Return:     Exit code 0 for success 1 for failure.

Purpose:    This server program utilizes sockets to listen for clients. It is
            expected to receive messages from the client. This program simply
            prints that message to stdout.
------------------------------------------------------------------------------*/
int main(int argc, char * argv[])
{
   int serv_sock, clnt_sock;            // Socket descriptors server + client 
   const int PORT = 3000;               // Port socket will attach to 
   struct sockaddr_in serv_add;         // Server socket address 
   int serv_add_len = sizeof(serv_add); // Size of socket address for accept 
   const int SIZE = 1024;               // Message buffer size 
   char buffer[SIZE];                   // Message buffer 

   /* Prompt showing server is online */
   printf("Server: Hello world.\n");

   /* Create server socket */
   if((serv_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      /* Socket failure */
      printf("Server: ERROR failed to create socket.\n");
      return 1;
   }
   else
   {
      /* Socket success */
      printf("Server: SUCCESS Socket created.\n");
   }

   /* Initialize the fields of the socket address for the server socket */
   memset(&serv_add, 0, sizeof(serv_add));       // Allocate memory for address
   serv_add.sin_family = AF_INET;                // Protocol family
   serv_add.sin_addr.s_addr = htonl(INADDR_ANY); // IP address
   serv_add.sin_port = htons(PORT);              // Port number

   /* Attach server socket to socket address */
   if((bind(serv_sock, (struct sockaddr *) &serv_add, sizeof(serv_add))) < 0)
   {
      /* Bind failure */
      printf("Server: ERROR failed to bind socket to address.\n");
      return 1;
   }
   else
   {
      /* Bind success */
      printf("Server: SUCCESS Socket binded to address.\n");
   }

   /* Listen for clients attempting to contact server via socket */
   if((listen(serv_sock, 1)) < 0)
   {
      /* Listen failure */
      printf("Server: ERROR unable to receive messages.\n");
      return 1;
   }
   else
   {
      /* Listen success */
      printf("Server: SUCCESS Actively listening for clients.\n");
   }

   /* Accept incoming messages from client */
   if((clnt_sock = accept(serv_sock, (struct sockaddr *) 
      &serv_add, &serv_add_len)) < 0)
   {
      /* Accept failure */
      printf("Server: ERROR failed to accept incoming message.\n");
      return 1;
   }
   else
   {
      /* Actively listening for client sockets */
      printf("Server: SUCCESS accepted a message from client.\n");
   }

   /* Receive the socket from the client */
   if((recv(clnt_sock, buffer, SIZE, 0)) < 0)
   {
      /* Receive failure */
      printf("Server: ERROR failed to receive incoming message.\n");
      return 1;
   }
   else
   {
      /* Message has been received */
      printf("Server: SUCCESS received message from client.\n");
   }

   /* Print message in buffer from client */
   printf("Server: Message is --> %s\n", buffer);

   /* Prompt showing normal server termination */
   printf("Server: Closing sockets, no errors.\n");

   /* Close the sockets */
   close(serv_sock);
   close(clnt_sock);

   return 0;
}
