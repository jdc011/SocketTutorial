/*=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
                                  client.c
--------------------------------------------------------------------------------
Author:  Jeremy Cruz

Date:    30, August 2018

Purpose: This is a client for the purpose of demonstrating Socket programming.
         This program connects to a server on port 3000 from local host. It 
         sends a string message to the server.
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

Parameters: Default: argc - Number of strings in message
                     argv - Array of individual strings composing a message

Return:     Exit code 0 for success 1 for failure.

Purpose:    This client program utilizes sockets to connect to servers. It takes
            user input from the command line as an argument. The argument is a
            user defined message that the client will send to the server.
------------------------------------------------------------------------------*/
int main(int argc, char * argv[])
{
   int clnt_sock;                 // Client socket descriptor
   struct sockaddr_in clnt_add;   // Client socket address
   const int SIZE = 1024;         // Message buffer size
   char buffer[SIZE];             // Message buffer
   const char * IP = "127.0.0.1"; // IP address to connect to
   const int PORT = 3000;         // Port number to attach to
   
   /* Prompt showing client is online */
   printf("Client: Hello world.\n");
 
   /* Create client socket */
   if((clnt_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
   {
      /* Socket failure */
      printf("Client: ERROR failed to create socket.\n");
      return 1;
   }
   else
   {
      /* Socket success */
      printf("Client: SUCCESS Socket created.\n");
   }

   /* Initialize the fields of the socket address for the client socket */
   memset(&clnt_add, 0, sizeof(clnt_add));   // Allocate memory for address
   clnt_add.sin_family = AF_INET;            // Protocol family
   clnt_add.sin_addr.s_addr = inet_addr(IP); // IP address
   clnt_add.sin_port = htons(PORT);          // Port number

   /* Connect client socket to given address */
   if((connect(clnt_sock, (struct sockaddr *) &clnt_add, sizeof(clnt_add))) < 0)
   {
      /* Connect failure */
      printf("Client: ERROR failed to connect to server.\n");
      return 1;
   }
   else
   {
      /* Connect success */
      printf("Client: SUCCESS connected to server.\n");
   }

   /* Place command line argument message in buffer */
   int i = 0;

   for(int j = 1; j < argc; j++)
   {
      int k = 0;

      while(argv[j][k] != '\0')
      {
         buffer[i++] = argv[j][k++];
      }

      buffer[i++] = ' ';
   }

   /* Prompt message sending */
   printf("Client: Sending message --> %s to the server\n", buffer);

   /* Send socket to server */
   if((send(clnt_sock, buffer, strlen(buffer), 0)) < 0) 
   {
      /* Send failure */
      printf("Client: ERROR failed to send message to server");
      return 1;
   }
   else
   {
      /* Socket was sent successfully */
      printf("Client: SUCCESS message sent to server.\n");
   }

   /* Prompt showing normal client termination */
   printf("Client: Closing sockets, no errors.\n");

   /* Close socket */
   close(clnt_sock);

   return 0;
}
