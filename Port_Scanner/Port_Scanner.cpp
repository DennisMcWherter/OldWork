/**
 * Port Scanner by Dennis J. McWherter, Jr.
 *
 * (C) 2010 DENNIS J. MCWHERTER, JR. ALL RIGHTS RESERVED.
 */

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <WinSock2.h>
#pragma comment(lib,"wsock32.lib")
#endif

#include <iostream>
#include <stdio.h>

int main()
{
	char IP[20];
	SOCKET sock;
	int start, end, temp;
	SOCKADDR_IN info;
	WSADATA wsData;

	if(WSAStartup(MAKEWORD(2,2),&wsData) != 0)
	{
		printf("An error was encountered when trying to initialize WinSock! Failing...\r\n");
		return 0;
	}

	printf("Target IP: ");
	std::cin >> IP;
	printf("\r\nStarting Port: ");
	std::cin >> start;
	printf("\r\nEnding Port: ");
	std::cin >> end;

	hostent *ServerAddr = gethostbyname(IP);

	temp = start;
	while(temp <= end)
	{
		sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
		info.sin_family = AF_INET;
		info.sin_port   = htons(temp);
		info.sin_addr.s_addr = *((unsigned long*)ServerAddr->h_addr_list[0]);
		memset(info.sin_zero,0,sizeof(info.sin_zero));
		if(connect(sock,(sockaddr*)&info,sizeof(sockaddr)) != SOCKET_ERROR)
			printf("Open Port: %d\r\n",temp);
		temp++;
		closesocket(sock);
	}
	printf("\r\nDone!\r\n");
	system("pause");
	return 0;
}
