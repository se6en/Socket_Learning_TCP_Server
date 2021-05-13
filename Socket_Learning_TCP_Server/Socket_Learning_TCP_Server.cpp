// Socket_Learning_TCP_Server.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

int main()
{
   WORD wVersionRequested;
   WSADATA wsaData;
   int err;

   /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
   wVersionRequested = MAKEWORD(2, 2);

   err = WSAStartup(wVersionRequested, &wsaData);
   if (err != 0) {
      /* Tell the user that we could not find a usable */
      /* Winsock DLL.                                  */
      printf("WSAStartup failed with error: %d\n", err);
      return 1;
   }

   /* Confirm that the WinSock DLL supports 2.2.*/
   /* Note that if the DLL supports versions greater    */
   /* than 2.2 in addition to 2.2, it will still return */
   /* 2.2 in wVersion since that is the version we      */
   /* requested.                                        */

   if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
      /* Tell the user that we could not find a usable */
      /* WinSock DLL.                                  */
      printf("Could not find a usable version of Winsock.dll\n");
      WSACleanup();
      return 1;
   }
   else
      printf("The Winsock 2.2 dll was found okay\n");


   /* The Winsock DLL is acceptable. Proceed to use it. */

   /* Add network programming using Winsock here */
   SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   in_addr addrserver;
   if (!inet_pton(AF_INET, "192.168.0.107", (void*)&addrserver))
   {
      printf("Error while transferring server address\n");
      WSACleanup();
      return 1;
   }

   sockaddr_in serveraddr;
   serveraddr.sin_family = AF_INET;
   serveraddr.sin_port = htons(80);
   serveraddr.sin_addr = addrserver;

   bind(server, (sockaddr*)&serveraddr, sizeof(serveraddr));

   listen(server, 5);

   sockaddr_in clientaddr;
   int length = sizeof(clientaddr);

   SOCKET client = accept(server, (sockaddr*)&clientaddr, &length);

   char recvdata[1024] = { 0 };
   recv(client, recvdata, 1023, 0);

   /* then call WSACleanup when done using the Winsock dll */

   WSACleanup();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
