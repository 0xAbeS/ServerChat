#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// Server Includes
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

// Utility Includes
#include <format>
#include <iostream>

//Not safe but ... whatever ¯\_(ツ)_/¯ 
using namespace std;


#pragma comment(lib, "Ws2_32.lib")


//Standard Console Colors

#define GREEN "\033[32m"
#define BLUE  "\033[34m"
#define RED   "\033[31m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

// Standard Macro Functions for Logging

template<typename... Args>
void okay(const string& msg, Args&&... args) { cout << GREEN << "[+] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }

template<typename... Args>
void info(const string& msg, Args&&... args) { cout << BLUE << "[*] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }

template<typename... Args>
void warn(const string& msg, Args&&... args) { cout << RED << "[-] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }

template<typename... Args>
void msg(const string& msg, Args&&... args) { cout << YELLOW << "[#] " << format(msg, forward<Args>(args)...) << RESET << '\n'; }

void main()
{
	// Initalize Winsock

	// Create a socket

	// Bind the socket to an ip address and port

	// Tell Winsock the socket is for listening

	// Wait for a connection

	// Close listening socket

	// While loop: accept and echo message back to client

	// Close the sock

	// Shutdown winsock
}