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
void okay(const string& msg, Args&&... args) { cout << GREEN << "[+] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }

template<typename... Args>
void info(const string& msg, Args&&... args) { cout << BLUE << "[*] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }

template<typename... Args>
void warn(const string& msg, Args&&... args) { cout << RED << "[-] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }

template<typename... Args>
void msg(const string& msg, Args&&... args) { cout << YELLOW << "[#] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }


int main()
{
	WSADATA wsaData;
	SOCKET serverSock = INVALID_SOCKET;
	sockaddr_in serverAddr;
	const char* IP = "127.0.0.1"; // or server address
	const int PORT = 2000;

	sockaddr_in hint;

	int iResult;

	// Initalize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		warn("WSAStartup failed! Result: ", iResult);
		return 1;
	}

	okay("WSAStartup successfull!");

	// Create a socket
	
	if (serverSock == INVALID_SOCKET)
	{
		warn("WSAError: {0}", WSAGetLastError());
		return 1;
	}


	// Bind the socket to an ip address and port
	sockaddr_in* result = NULL,
		* ptr = NULL,
		hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.sin_family = AF_UNSPEC;
	hints.sin_port = htons(PORT);
	hints = IPPROTO_TCP;
	// Tell Winsock the socket is for listening

	// Wait for a connection

	// Close listening socket

	// While loop: accept and echo message back to client

	// Close the sock

	// Shutdown winsock

	return 0;
}