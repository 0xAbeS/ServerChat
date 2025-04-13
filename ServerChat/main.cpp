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


template<typename... Args>
int okay(const string& msg, Args&&... args) { cout << GREEN << "[+] " << format(msg, forward<Args>(args)...) << RESET << '\n'; return 0; }

template<typename... Args>
void info(const string& msg, Args&&... args) { cout << BLUE << "[*] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }

template<typename... Args>
int warn(const string& msg, Args&&... args) { cout << RED << "[-] " << format(msg, forward<Args>(args)...) << RESET << '\n'; return 1; }

template<typename... Args>
void msg(const string& msg, Args&&... args) { cout << YELLOW << "[#] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }


int main()
{
	WSADATA wsaData;
	SOCKET serverSock = INVALID_SOCKET;
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	const char* IP = "127.0.0.1", * PORT = "2000"; // or server address

	sockaddr_in hint;

	int iResult;

	// Initalize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
		return warn("WSAStartup failed! Result: ", iResult);


	okay("WSAStartup successfull!");

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve server address and port
	iResult = getaddrinfo(NULL, PORT, &hints, &result);

	if ( iResult != 0)
		return warn("Getaddrinfo failed. WSAError: {0}", WSAGetLastError());


	serverSock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (serverSock == INVALID_SOCKET)
		return warn("Error at soocket(). WSAError: {0}", WSAGetLastError());

	// Setup the listening socket
	iResult = bind(serverSock, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		warn("bind failed with error: {0}", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(serverSock);
		WSACleanup();
		return 1;
	}


	// Wait for a connection

	// Close listening socket

	// While loop: accept and echo message back to client

	// Close the sock

	// Shutdown winsock

	return 0;
}