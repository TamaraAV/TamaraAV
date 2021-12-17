/*
	UDP Server
*/
#pragma warning(disable : 4996)
#include <stdio.h>
#ifndef _WIN32
using SOCKET = int
#define WSAGetLastError() 1
#else
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif

//#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 	1024		    //Max length of buffer
#define PORT    8888			//The port on which to listen for incoming data


#include "Crypt-Algorithms.h"

//int RowColumn(char* input, char* output);


int main(int argc, char* argv[])
{
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;


	char buf[BUFLEN];
	char dec_buf[BUFLEN];
	char msg[BUFLEN];
	char enc_msg[BUFLEN];

	
#ifdef WIN32
	WSADATA wsa;

	slen = sizeof(si_other);

	//Initialise winsock
	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("  Initialized.\n");
#endif //WIN32

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
//	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (1 == argc)
	{
		server.sin_port = htons(PORT);
		printf("1: Listen port=%d\n", PORT);
	}
	else
	{
		server.sin_port = htons(atoi(argv[1]));
		printf("2: Listen port=%d\n", atoi(argv[1]));
	}

	//Bind
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
//	puts("Bind done");

	//keep listening for data
	while (1)
	{
		printf("Waiting for data...   ");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//print details of the client/peer and the data received
		printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		RowColumn(buf, dec_buf);
		printf("Received packet: \n%s", buf);
		printf("Data: %s\n", dec_buf);

		printf("\nAnswer : ");
		gets_s(msg, BUFLEN);
		RowColumn(msg, enc_msg);
		printf("\nEncoded \n%s",enc_msg);
		//now reply the client with the same data
		if (sendto(s, enc_msg, (int)strlen(enc_msg), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

#ifdef _WIN32
	closesocket(s);
	WSACleanup();
#endif //_WIN32
	return 0;
}

/**
int RowColumn(char* input, char* output)
{
	int i, j;
	while (strlen(input) % 9 != 0) {
		strcat(input," ");
	}
	*(input + strlen(input) - 1) = '\0';
	while (*input)
	{
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				*output = *(input + j * 3);
				output++;
			}
			input++;
		}
		input += 6;
	}
	return 0;
}
**/
