#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#include <format>
#include <iostream>

using namespace std;


#pragma comment(lib, "Ws2_32.lib")


//Standard Macro Functions

#define GREEN "\033[32m"
#define BLUE  "\033[34m"
#define RED   "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

//https://devdocs.io/cpp/language/template_parameters
//https://stackoverflow.com/questions/72795189/how-can-i-wrap-stdformat-with-my-own-template-function
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2022/p2508r1.html
// Basically template parameters to get args and wrapped std format
template<typename... Args>
int okay(format_string<Args...> msg, Args&&... args) { cout << GREEN << "[+] " << format(msg, forward<Args>(args)...) << RESET << '\n'; return 0; }

template<typename... Args>
void info(format_string<Args...> msg, Args&&... args) { cout << BLUE << "[*] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }

template<typename... Args>
int warn(format_string<Args...> msg, Args&&... args) { cout << RED << "[-] " << format(msg, forward<Args>(args)...) << RESET << '\n'; return 1; }

template<typename... Args>
void msg(format_string<Args...> msg, Args&&... args) { cout << YELLOW << "[#] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }


/*TO DO:
 *Put everything in classes to make updating easy
 *Handle send failing better

 *GET A WAY TO SEND MESSAGES BETWEEN TO CHATS
 *	Figure out wether to use Select or Threading
 *Select
 *	Pros: Works on Single Thread,
		  Allows for app to exit cleanly
		  Good for using with many connection
 *	Cons: Idfk how it works, confusing asl
 *		  Non blocking IO is annoying
 *		  Still more confusion
 *Threading: 
 *	Pros: Ik it, apparently its the standard
 *	Cons: Annoying when theres things like message logging/accessing same data
 *	      Each thread can apparently block on recv, so gotta handle that
 *		  Wrecks memory cpu
 *		  Might just have to still do this with Select
 *			
 
 * "Normally a server application would be designed to listen for connections from multiple clients. For high-performance servers, multiple threads are commonly used to handle the multiple client connections."
*/

int main()
{
	WSADATA wsaData;
	SOCKET serverSock = INVALID_SOCKET;
	SOCKET clientSock = INVALID_SOCKET;
	struct addrinfo *result = NULL, *ptr = NULL, hints;

	const char* IP = "127.0.0.1", * PORT = "2000"; // or server address
	const int RECVBUFLEN = 512;


	char recvBuf[RECVBUFLEN];

	int iResult;
	int iSend;

	// Initalize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
		return warn("WSAStartup failed! Result: ", iResult);


	okay("WSAStartup successfull");

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve server address and port
	iResult = getaddrinfo(NULL, PORT, &hints, &result);

	if ( iResult != 0)
		return warn("Getaddrinfo failed. WSAError: {0}", WSAGetLastError());

	okay("Passed getaddrinfo()");

	serverSock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (serverSock == INVALID_SOCKET)
		return warn("Error at soocket(). WSAError: {0}", WSAGetLastError());

	// Associates ip with port
	iResult = bind(serverSock, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		warn("bind failed with error: {0}", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(serverSock);
		WSACleanup();
		return 1;
	}

	okay("Binded bind()");
	
	// Just listening ngl, waiting around
	iResult = listen(serverSock, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		warn("Listen failed with error: {0}", WSAGetLastError());
		closesocket(serverSock);
		WSACleanup();
		return 1;
	}

	okay("Started listen()");

	// Accept a client socket
	clientSock = accept(serverSock, NULL, NULL);
	if (clientSock == INVALID_SOCKET) {
		warn("accept failed: {0}", WSAGetLastError());
		closesocket(serverSock);
		WSACleanup();
		return 1;
	}

	okay("Accepted connection");

	// Load of yap, basically
	// Copy pasta from docs, gotta make my own handling
	do {

		iResult = recv(clientSock, recvBuf, RECVBUFLEN, 0);
		if (iResult > 0) {
			okay("Bytes received: {0}", iResult);

			// Return what was sent
			iSend = send(clientSock, recvBuf, iResult, 0);
			if (iSend == SOCKET_ERROR) {
				warn("send() failed, error: {0}", WSAGetLastError());
				closesocket(clientSock);
				WSACleanup();
				return 1;
			}
			okay("Bytes sent: {0}", iSend);
		}
		else if (iResult == 0)
			info("Connection closing...");
		else {
			warn("recv() failed, error: {0}", WSAGetLastError());
			closesocket(clientSock);
			WSACleanup();
			return 1;
		}
	} while (iResult > 0);

	// Close the sock
	iResult = shutdown(clientSock, SD_BOTH);
	if (iResult == SOCKET_ERROR) {
		warn("shutdown() failed, error: {0}", WSAGetLastError());
		closesocket(clientSock);
		WSACleanup();
		return 1;
	}

	closesocket(clientSock);
	WSACleanup();

	return 0;
}