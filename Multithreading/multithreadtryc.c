#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h> 
#include<pthread.h>
void * cientThread(void *arg)

{
  pthread_detach(pthread_self());
  printf("In thread\n");
  char message[1000];
  char buffer[1024];
  int clientSocket;
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  // Create the socket. 
  clientSocket = socket(PF_INET, SOCK_STREAM, 0);
  //Configure settings of the server address
 // Address family is Internet 
  serverAddr.sin_family = AF_INET;
  //Set port number, using htons function 
  serverAddr.sin_port = htons(7799);
 //Set IP address to localhost
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1 ");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
    //Connect the socket to the server using the address
    addr_size = sizeof serverAddr;
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size)==-1)
    	{
    	 printf("Error in connection");
    	 exit(1);	
    	};
   //while(1)
   while(1)
   {//strcpy(message,"Hello");
    
    //Read the message from the server into the buffer
    if(recv(clientSocket, buffer, 1024, 0) < 0)
    {
       printf("Receive failed\n");
    }
    //Print the received message
    printf("Data received: %s\n",buffer);
    printf("Enter Data");
    //fflush(stdin);
	 fscanf(stdin,"%s",message);
   if( send(clientSocket , message , strlen(message)+1, 0) < 0)
    {
            printf("Send failed\n");
    }
    if (strcmp(message,"end")==0)
      break;
    bzero(buffer,sizeof(buffer));
    bzero(message,sizeof(message));
    }
    close(clientSocket);
    pthread_exit(NULL);
}
int main(){
  int i = 0;
  pthread_t tid[51];
    if( pthread_create(&tid[i], NULL, cientThread, NULL) != 0 )
           printf("Failed to create thread\n");
  sleep(20);
     pthread_join(tid[i++],NULL);
     printf("%d:\n",i); 
  return 0;
}
