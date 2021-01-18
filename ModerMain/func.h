#pragma once
#ifndef FUNC_H
#define FUNC_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <process.h>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

static HANDLE muthandle;

// Part of boyer moore
void otherArrayFunc(string str, int otherArray[256]);

// Boyer moore algoritm
int BMSearch(string main, string find, vector<int>& result);

// Connection to server
int ConnectToServer(SOCKET& ConnectSocket);

// Sent message from console
unsigned int WINAPI OutMsg(LPVOID Socket);

// Send an initial buffer
int SentMsg(SOCKET& ConnectSocket, string msg);

// Receive until the peer closes the connection
unsigned int WINAPI GetMsg(LPVOID ConnectSocket);

// Switch what to do
int SwitchDo(SOCKET& ConnectSocket, string text);

// Parse text
string ParseText(string msg);

// Find bad word and delete change them to*
string FindBW(string msg, fstream& fs);

// Get time
string GetTime();

// Cleanup
void CloseConnect(SOCKET& ConnectSocket, HANDLE& in, HANDLE& out);

#endif