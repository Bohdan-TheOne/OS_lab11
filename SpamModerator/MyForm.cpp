#include "MyForm.h"

using namespace moderatorNew;

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm);
	return 0;
}

int moderatorNew::MyForm::receiveFaultsFromServer(SOCKET& connectSocket)
{
	int receiveResult; char inputString[256];
	receiveResult = recv(connectSocket, inputString, sizeof(inputString), NULL);
	inputString[receiveResult] = 0;
	if (receiveResult > 0)
	{
		std::cout << "Bytes received: " << receiveResult<<endl;
		string argument(inputString);
		numOfBadWords(argument);
		string usersResults = "SEND ";
		for (int i = 0; i < usersFaults.size() - 1; i++)
		{
			usersResults = usersResults + "The user " + usersNames[i] + " has " + to_string(usersFaults[i]) + " bad words to maximum!\n";
		}
		userResults = usersResults + "The user " + usersNames[usersFaults.size() - 1] + " has " + to_string(usersFaults[usersFaults.size() - 1]) + " bad words to maximum!";
		sendDataToServer(connectSocket, usersResults);
		return EXIT_SUCCESS;
	}
	else if (receiveResult == 0) {
		cout << "Connection closed" << endl;
		return EXIT_FAILURE;
	}
	else {
		cout << "recv failed with error: " << WSAGetLastError() << endl;
		return WSAGetLastError();
	}
}

int moderatorNew::MyForm::receiveDataFromServer(SOCKET& connectSocket, string& receivedData)
{
	int receiveResult; char inputString[256];
	receiveResult = recv(connectSocket, inputString, sizeof(inputString), NULL);
	inputString[receiveResult] = 0;
	do {
		if (receiveResult > 0)
		{
			std::cout << "Bytes received: " << receiveResult << endl;
			receivedData = inputString;
			return EXIT_SUCCESS;
		}
		else if (receiveResult == 0) {
			cout << "Connection closed" << endl;
			return EXIT_FAILURE;
		}
		else {
			cout << "recv failed with error: " << WSAGetLastError() << endl;
			return WSAGetLastError();
		}
	} while (receiveResult > 0);
	return 0;
}


void moderatorNew::MyForm::numOfBadWords(string message)
{
	if (message.substr(0, message.find(' ')) == "FREZ")
	{
		message.erase(0, message.find(' ')+1);
		while (message.find(' ') != string::npos)
		{
			string userName = message.substr(0, message.find(' '));
			message.erase(0, message.find(' ')+1);
			int userFaults = stoi(message.substr(0, message.find(' ')));
			message.erase(0, message.find(' ')+1);
			usersNames.push_back(userName);
			usersFaults.push_back(MAX_FAULT - userFaults);
		}
	}
} // SEND yuri 16 zumori 3 fanteak 6


int moderatorNew::MyForm::sendDataToServer(SOCKET& connectSocket, string output)
{
	int bytesSent;
	if (bytesSent = send(connectSocket, output.c_str(), output.size(), NULL) == SOCKET_ERROR)
	{
		cout << "Error while sending data to server: " << WSAGetLastError() << endl;
		return WSAGetLastError();
	}
	else
	{
		return bytesSent;
	}
}

unsigned int __stdcall receiveMessages(void* data)
{
	SOCKET connectSocket = (SOCKET)data;
	int receiveResult; char inputString[256];
	do
	{
		receiveResult = recv(connectSocket, inputString, sizeof(inputString), NULL);
		string result = inputString;
		inputString[receiveResult] = 0;
		if (receiveResult > 0)
		{
			if(result.substr(0, result.find(' '))=="MSG")
			{
				result.erase(0, result.find(' ') + 1);
				cout << result<<endl;
				Sleep(500);
			}
		}
		else if (receiveResult == 0) {
			continue;
		}
		else {
			cout << "recv failed with error: " << WSAGetLastError() << endl;
			return WSAGetLastError();
		}
	} while (receiveResult >= 0);
	return 0;
} // MSG yuri : hello world
