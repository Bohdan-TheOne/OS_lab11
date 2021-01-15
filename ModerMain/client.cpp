#include "func.h"

int __cdecl main()
{
	SOCKET ConnectSocket = INVALID_SOCKET;
	
	if (ConnectToServer(ConnectSocket) != 0)
	{
		cout << "Unable to connect to server!\n";
		WSACleanup();
		return 1;
	}

	HANDLE inHandle, outHandle;
	inHandle = (HANDLE)_beginthreadex(0, 0, GetMsg, (LPVOID)ConnectSocket, 0, 0);
	outHandle = (HANDLE)_beginthreadex(0, 0, OutMsg, (LPVOID)ConnectSocket, 0, 0);

	// cleanup
	CloseConnect(ConnectSocket, inHandle, outHandle);

	return 0;
}