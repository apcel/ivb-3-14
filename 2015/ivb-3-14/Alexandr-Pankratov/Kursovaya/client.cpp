#pragma comment(lib,"Ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#define SIZE 1024
using std::string;
using std::cin;
using std::cout;
using std::endl;

SOCKADDR_IN anAddr;
SOCKET* Connections;
SOCKET s;

void
Recive(SOCKET soket)
{
	while (true) {
		char data[SIZE];
		recv(soket,data,sizeof(data),0);
		cout <<"\n>" << data << endl;
	}
}

int
main()
{
	WSAData h;
	WORD version = MAKEWORD(2, 2);
	int res = WSAStartup(version, &h);
	setlocale(0, "russian");
	anAddr.sin_family = AF_INET;
	anAddr.sin_port = htons(7770);
	anAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	int g = connect(s, (struct sockaddr *)&anAddr, sizeof(struct sockaddr));
	if (g==SOCKET_ERROR) {
		cout << "error";
		return 1;
	}

	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Recive, (LPVOID)(s), NULL, NULL);
	while(1) {
		string t;
		std::getline(cin, t);
		send(s, t.c_str(), SIZE, 0);
	}

	return 0;
}
