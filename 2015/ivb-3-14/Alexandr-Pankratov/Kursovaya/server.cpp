#pragma comment(lib,"Ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#define SIZE 1024
SOCKET Connect;
SOCKET* Connections;
SOCKET Listen;
int ClientCount = 0;

void
SendMessageToClient(int ID)
{
	int len;
	char* buffer = new char[SIZE];
	while (true) {
		memset(buffer, 0, sizeof(buffer));
		if ((len=recv(Connections[ID], buffer, SIZE, NULL))==SOCKET_ERROR) {
			printf("Client disconect...\n");
			delete buffer;
			return;
		} else (len) {
			printf(buffer);
			printf("\n");
			for (int i = 0; i < ClientCount; i++) {
				if(i!=ID) {
					send(Connections[i], buffer, SIZE, NULL);
				}
			}
		}
	}
}

int 
main()
{
	setlocale(0, "russian");
	WSAData data;
	WORD version = MAKEWORD(2, 2);
	int res = WSAStartup(version, &data);
	if (res != 0) {
		return 0;
	}

	struct addrinfo hints;
	struct addrinfo * result;



	Connections = (SOCKET*)calloc(64, sizeof(SOCKET));
	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	getaddrinfo(NULL, "7770", &hints, &result);
	Listen = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	bind(Listen, result->ai_addr, result->ai_addrlen);
	listen(Listen, SOMAXCONN);

	freeaddrinfo(result);

	printf("Start server...\n");
	while (true) {
		if (Connect = accept(Listen, NULL, NULL)) {
			printf("Client Connect...\n");
			Connections[ClientCount] = Connect;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)SendMessageToClient, (LPVOID)(ClientCount), NULL, NULL);
			ClientCount++;
		}
	}
	return 1;
}
