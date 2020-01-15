//#pragma once
//ref class Socket
//{
//};

#pragma once
#include "Winsock2.h";
#include "Ws2tcpip.h"
#include <stdint.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

class Socket
{
public:
	Socket(char* ip_server, int port); //with 2 argument, we set socket as client
	Socket(int port);				   //with 1 argument, we set socket as server
	int Send(char* data, uint16_t size);
	int Recv(char* src, uint16_t size);
	void ServerTask();
	char* GetDirAddr(char* buff);
	char* GetData(char* buff);

private:
	struct sockaddr_in server;
	WSADATA wsa;
	SOCKET s;
	char dstAddr[14];
	char data2Send[1024];
};

