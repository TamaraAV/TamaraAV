/*
	UDP Client routine
*/

#include "Crypt-Algorithms.h"

#include <stdio.h>
#pragma warning(disable : 4996)
#ifndef _WIN32
	using SOCKET = int
	#define WSAGetLastError() 1
#else
	#include <winsock2.h>
	#pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 	1024		//Max length of buffer
#define PORT 8888			//The port on which to listen for incoming data



//int RowColumn(char* input, char* output);

int main(int argc, char* argv[])
{
	SOCKET s;
	struct sockaddr_in si_other;
	int slen = sizeof(si_other);

	char buf[BUFLEN];
	char dec_buf[BUFLEN];
	char message[BUFLEN];
	char enc_msg[BUFLEN];

	unsigned short srv_port = 0;
	char srv_ip_addr[40];
	memset(srv_ip_addr, 0, 40);

#ifdef WIN32
	WSADATA wsa;

	//Initialize winsock
	printf("\nInitializing Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");
#endif //WIN32

	//create socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	//setup address structure
	memset((char*)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;

	//si_other.sin_port = htons(PORT);
	//si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	if (1 == argc)
	{
		si_other.sin_port = htons(PORT);
		si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);
		//printf("1: Server - addr=%s , port=%d\n", SERVER, PORT);
	}
	else if (2 == argc)
	{
		si_other.sin_port = htons(PORT);
		si_other.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		//printf("2: Server - addr=%s , port=%d\n", argv[1], PORT);
	}
	else
	{
		si_other.sin_port = htons( atoi(argv[2]) );
		si_other.sin_addr.S_un.S_addr = inet_addr(argv[1]);
		//printf("3: Server - addr=%s , port=%d\n", argv[1], atoi(argv[2]));
	}

	//start communication  lifecircle
	while (1)
	{
		printf("\nEnter message : ");
		gets_s(message, BUFLEN);

		//send the message
		RowColumn(message, enc_msg);
		printf("\nEncoded message\n%s",enc_msg);
		if (sendto(s, enc_msg, (int)strlen(enc_msg), 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		RowColumn(buf, dec_buf);
		puts(dec_buf);
		printf("\nReceived text \n%s", buf);
		printf("\nDecoded \n%s", dec_buf);
	}

#ifndef _WIN32
	closesocket(s);
	WSACleanup();
#endif //_WIN32
	return 0;
}
