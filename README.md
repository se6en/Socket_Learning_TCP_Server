# Socket_Learning_TCP_Server
# 5/13/2021
Create TCP socket communication server.

## Sample project files
---
### Socket_Learning_TCP_Server(.h and .cpp)
---
We need take following steps to create socket server for TCP communication:
1. Start up socket with function WSAStartup() to find the usable Windowsock DLL. We use Winsock 2.2 dll in this sample as the sample in MSDN.
2. Create socket server with the socket constructor. Parameter SOCK_STREAM was used for TCP protocol.
3. Transfer the server ip adress from string to in_addr.
4. Bind the socket server created in Step.2 with the address. AF_INET was the family used for TCP protocol. Port number also needed to be specific in this step.
5. Use listen function to define the maximum length of the queue of pending connections and put the socket server into listen state.
6. Waiting for the client information. Accept function will block the message until server get any information from client. 
7. After got information from client, the communication will be established. Use recv to got the real information.
8. WSACleanup was used to clean all the information and finished the use of Winsock dll.