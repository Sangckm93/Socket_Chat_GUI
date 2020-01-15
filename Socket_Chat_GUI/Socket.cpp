#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Socket.h"
#include "stdio.h"
#include <iostream>
Socket::Socket(char* ip_server, int port)
{
	printf("\r\nInitialising Winsock...\r\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf(" Failed.Error Code : % d \r\n", WSAGetLastError());
	}
	printf("Initialised.\r\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : % d\r\n", WSAGetLastError());
	}
	printf("Socket created.\r\n ");
	server.sin_addr.s_addr = inet_addr(ip_server);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//Connect to remote server
	if (connect(s, (struct sockaddr*) & server, sizeof(server)), 0)
	{
		printf("connect error\r\n");
	}

	printf("Connected\r\n");
}
Socket::Socket(int port)
{
	printf("\r\nInitialising Winsock...\r\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed.Error Code : % d\r\n", WSAGetLastError());
	}
	printf(" Initialised.\n ");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : % d\r\n", WSAGetLastError());
	}
	printf("Socket created.\r\n ");

	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	bind(s, (struct sockaddr*) & server, sizeof(struct sockaddr));

	listen(s, 5);
}

int Socket::Send(char* data, uint16_t size)
{
	return send(s, data, size, 0);
}

int Socket::Recv(char* src, uint16_t size)
{
	return recv(s, src, size, 0);
}

void Socket::ServerTask()
{
	SOCKET clientSocket = INVALID_SOCKET;
	sockaddr_in client;
	int lenClient = sizeof(client);
	clientSocket = accept(s, (sockaddr*)&client, &lenClient);
	printf("Client: \r\n");
	printf("\tAddr: %s\r\n", inet_ntoa(client.sin_addr));
	printf("\tPort: %d\r\n", client.sin_port);
	int temp = 0;
	char buff[1024];
	memset(buff, 0, sizeof(buff));
	int timeout = 0;
	while (temp == 0)
	{
		temp = recv(clientSocket, buff, sizeof(buff), NULL);
		Sleep(100);
		if (timeout++ > 100)
			break;
	}
	char* msg = NULL;
	if (temp > 0) {
		msg = (char*)"server: da nhan thanh cong data\r\n";
		printf("data from client: %s\r\n", buff);
		SOCKET dstSocket = INVALID_SOCKET;
		struct sockaddr_in dstAddr;

		dstAddr.sin_addr.s_addr = inet_addr(GetDirAddr(buff));
		dstAddr.sin_family = AF_INET;
		dstAddr.sin_port = htons(2222);
		//Create a socket
		if ((dstSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
		{
			printf("Could not create socket : % d\r\n", WSAGetLastError());
		}
		//Connect to remote server
		if (connect(dstSocket, (struct sockaddr*) & dstAddr, sizeof(dstAddr)), 0)
		{
			printf("connect error\r\n");
		}
		else
		{
			printf("connection success\r\n");
		}
		send(dstSocket, GetData(buff), strlen(GetData(buff)), NULL);
		closesocket(dstSocket);
	}
	else {
		msg = (char*)"server: timeout\r\n";
	}
	send(clientSocket, (const char*)msg, strlen(msg), NULL);
	closesocket(clientSocket);
}

char* Socket::GetDirAddr(char* buff)
{
	memset(dstAddr, 0, sizeof(dstAddr));
	char* key = (char*)"\"Dst\"";
	char* startAddr = strstr(buff, key) + strlen(key);
	int index = (int)(startAddr - buff);
	char temp = 0;
	char step = 0;
	while (step < 2)
	{
		switch (step)
		{
		case 0:
			if (buff[index] == '"') {
				step = 1;
			}
			break;
		case 1:
			if (buff[index] != '"') {
				memcpy(dstAddr + temp++, buff + index, 1);
			}
			else {
				step = 2;
			}
			break;
		}
		index++;
	}
	dstAddr[temp] = 0x00;
	return dstAddr;
}

char* Socket::GetData(char* buff)
{
	memset(data2Send, 0, sizeof(data2Send));
	char* key = (char*)"\"Data\"";
	char* startAddr = strstr(buff, key) + strlen(key);
	int index = (int)(startAddr - buff);
	char temp = 0;
	char step = 0;
	while (step < 2)
	{
		switch (step)
		{
		case 0:
			if (buff[index] == '"') {
				step = 1;
			}
			break;
		case 1:
			if (buff[index] != '"') {
				memcpy(data2Send + temp++, buff + index, 1);
			}
			else {
				step = 2;
			}
			break;
		}
		index++;
	}
	data2Send[temp] = 0x00;
	return data2Send;
}