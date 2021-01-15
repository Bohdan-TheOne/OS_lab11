#include "func.h"

// Part of boyer moore
void otherArrayFunc(string str, int otherArray[256])
{
	for (int i = 0; i < 256; i++)
	{
		otherArray[i] = -1;
	}

	for (int i = 0; i < str.size(); i++)
	{
		otherArray[(int)str[i]] = i;
	}
}

// Boyer moore algoritm
int BMSearch(string main, string find, vector<int>& result)
{
	int otherArray[256];

	otherArrayFunc(find, otherArray);
	int count = 0;
	int index = 0;
	while (index <= (main.size() - find.size()))
	{
		int i = find.size() - 1;

		while (i >= 0 && find[i] == main[index + i])
		{
			i--;
		}

		if (i < 0)
		{
			for (int j = 0; j < find.size(); j++)
			{
				result.push_back(index + j);
			}
			count++;
			index += (index + find.size() < main.size()) ? find.size() - otherArray[main[index + find.size()]] : 1;
		}
		else
		{
			index += (i - otherArray[main[index + i]]);
		}
	}
	return count;
}

//connection to server
int ConnectToServer(SOCKET& ConnectSocket)
{
	WSADATA wsaData;
	struct addrinfo hints, * result = NULL, * ptr = NULL;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		cout << "WSAStartup failed with error: " << iResult << endl;
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) 
	{
		cout << "Getaddrinfo failed with error: " << iResult << endl;
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL;ptr = ptr->ai_next) 
	{

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) 
		{
			cout << "Socket failed with error: " << WSAGetLastError() << endl;
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) 
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET)
	{
		cout << "Unable to connect to server!\n";
		WSACleanup();
		return 1;
	}

	muthandle = CreateMutex(0, FALSE, 0);

	return 0;
}

// Sent message from console
unsigned int WINAPI OutMsg(LPVOID Socket)
{
	SOCKET ConnectSocket = (SOCKET)Socket;
	string msg;

	while (_getch() != 27)
	{
		cout << "Enter command:\n";
		getline(cin, msg);
		int first = msg.find_first_of(' ');
		string temp = msg.substr(0, first);

		if (temp == "AUTH" || temp == "LOGIN" || temp == "QUIT" || temp == "SEND" || temp == "SET")
		{
			SentMsg(ConnectSocket, msg);
		}
		else
		{
			cout << "Check command whitch you want to send\n";
		}
	}
	return 0;
}

// Send an initial buffer
int SentMsg(SOCKET& ConnectSocket, string msg)
{
	WaitForSingleObject(muthandle, INFINITE);

	int iResult = send(ConnectSocket, msg.c_str(), msg.size(), 0);

	if (iResult == SOCKET_ERROR) 
	{
		cout << "Send failed with error: " << WSAGetLastError() << endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	cout << "Bytes Sent: " << iResult << endl;

	ReleaseMutex(muthandle);

	return 0;
}

// Receive until the peer closes the connection
unsigned int WINAPI GetMsg(LPVOID Socket)
{
	int iResult;
	string text;
	char recvbuf[DEFAULT_BUFLEN];

	SOCKET ConnectSocket = (SOCKET)Socket;
	while (true)
	{
		iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);
		if (iResult > 0)
		{
			cout << "Bytes received: " << iResult << endl;
			text = recvbuf;
			if (SwitchDo(ConnectSocket, text) != 0)
			{
				cout << "Wrong message from server\n";
			}
		}
		else
		{
			if (iResult == 0)
			{
				cout << "Connection closed\n";
			}
			else
			{
				cout << "Receive failed with error:" << WSAGetLastError() << endl;
				break;
			}
		}
	}
	return 0;
}

// Switch what to do
int SwitchDo(SOCKET& ConnectSocket, string text)
{
	int first = text.find_first_of(' ');
	string temp = text.substr(0, first);
	string msg = text.substr(first + 1, text.size());

	if (temp == "MSG")
	{
		cout << msg;
		return 0;
	}
	if (temp == "EDI")
	{
		SentMsg(ConnectSocket, ParseText(msg));
		return 0;
	}
	if (temp == "ERR")
	{
		cout << msg;
		return 0;
	}
	if (temp == "INF")
	{
		cout << msg;
		return 0;
	}

	return 1;
}

// Parse text   
//<M> fanteak : let`s play csgo        SET <M> fanteak : let`s play csgo
//yuri : let`s play csgo        SET yuri 1 let`s play ****
string ParseText(string msg)
{
	int first = msg.find_first_of(' ');
	string temp = msg.substr(0, first);
	if (temp == "<M>")
	{
		return ("SET " + msg);
	}
	else
	{
		fstream fs;
		fs.open("LogFile.txt", fstream::out | fstream::app);
		fs << GetTime() << temp << " ";
		temp = "SET " + temp + " " + FindBW(msg.substr(first + 3, msg.size()), fs);
		fs.close();
		return temp;	
	}
}

// Find bad word and delete change them to
string FindBW(string msg, fstream& fs)
{
	const int SIZE = 7;
	string badArray[] =
	{
		"csgo",
		"windows",
		"linux",
		"thread",
		"process",
		"sync",
		"network"
	};

	int count = 0;
	vector<int> result;
	for (int i = 0; i < SIZE; i++)
	{
		int temp = BMSearch(msg, badArray[i], result);
		if (temp > 0)
		{
			count += temp;
			fs << badArray[i] << " " << temp << endl;
		}
	}

	for (int i = 0; i < result.size(); i++)
	{
		msg[result[i]] = '*';
	}

	return (to_string(count) + " " + msg);
}

// Get time
string GetTime()
{
	time_t now = time(0);
	tm* gmtm = gmtime(&now);
	string result = "[";
	result += to_string(gmtm->tm_mday) + "-";
	result += to_string(gmtm->tm_mon) + "-";
	result += to_string(gmtm->tm_year) + " ";
	result += to_string(gmtm->tm_hour) + ":";
	result += to_string(gmtm->tm_min) + ":";
	result += to_string(gmtm->tm_sec) + "]: ";
	return result;
}

// Cleanup
void CloseConnect(SOCKET& ConnectSocket, HANDLE& in, HANDLE& out)
{
	WaitForSingleObject(in, INFINITE);
	WaitForSingleObject(out, INFINITE);

	CloseHandle(in);
	CloseHandle(out);
	CloseHandle(muthandle);

	closesocket(ConnectSocket);
	WSACleanup();
} 