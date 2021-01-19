#pragma once
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#pragma comment(lib, "ws2_32.lib")
#include <cassert>
#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <process.h>

using namespace std;

const int MAX_FAULT = 20;
vector<string> usersNames;
vector<int> usersFaults;
SOCKET clientSocket;
HANDLE receiveThread;
string userLogin;
string userPassword;

unsigned int __stdcall receiveMessages(void* data);

namespace moderatorNew {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		int receiveFaultsFromServer(SOCKET& connectSocket);
		int receiveDataFromServer(SOCKET& connectSocket, string& receivedData);
		void numOfBadWords(string message);
		int sendDataToServer(SOCKET& connectSocket, string output);
		MyForm(void)
		{
			InitializeComponent();
			this->timer1->Interval = 30000;
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::TextBox^ login;
	private: System::Windows::Forms::TextBox^ password;
	

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ connectButton;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;
	private: System::Windows::Forms::TextBox^ message;
	private: System::Windows::Forms::Button^ sendMessage;
	private: System::Windows::Forms::Button^ exit;
	public:

	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->login = (gcnew System::Windows::Forms::TextBox());
			this->password = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->connectButton = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->message = (gcnew System::Windows::Forms::TextBox());
			this->sendMessage = (gcnew System::Windows::Forms::Button());
			this->exit = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// login
			// 
			this->login->Font = (gcnew System::Drawing::Font(L"Arial", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->login->Location = System::Drawing::Point(735, 100);
			this->login->Multiline = true;
			this->login->Name = L"login";
			this->login->Size = System::Drawing::Size(200, 40);
			this->login->TabIndex = 0;
			// 
			// password
			// 
			this->password->Font = (gcnew System::Drawing::Font(L"Arial", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->password->Location = System::Drawing::Point(735, 178);
			this->password->Multiline = true;
			this->password->Name = L"password";
			this->password->Size = System::Drawing::Size(200, 40);
			this->password->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(729, 65);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(100, 32);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Login:";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(729, 143);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(158, 32);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Password:";
			// 
			// connectButton
			// 
			this->connectButton->Font = (gcnew System::Drawing::Font(L"Arial", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->connectButton->Location = System::Drawing::Point(735, 233);
			this->connectButton->Name = L"connectButton";
			this->connectButton->Size = System::Drawing::Size(200, 73);
			this->connectButton->TabIndex = 4;
			this->connectButton->Text = L"Connect to server";
			this->connectButton->UseVisualStyleBackColor = true;
			this->connectButton->Click += gcnew System::EventHandler(this, &MyForm::connectButton_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->Font = (gcnew System::Drawing::Font(L"Arial", 19.8F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->richTextBox1->Location = System::Drawing::Point(-2, 0);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->Size = System::Drawing::Size(707, 477);
			this->richTextBox1->TabIndex = 5;
			this->richTextBox1->Text = L"";
			// 
			// message
			// 
			this->message->Font = (gcnew System::Drawing::Font(L"Arial", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->message->Location = System::Drawing::Point(735, 418);
			this->message->Multiline = true;
			this->message->Name = L"message";
			this->message->Size = System::Drawing::Size(200, 40);
			this->message->TabIndex = 6;
			this->message->TextChanged += gcnew System::EventHandler(this, &MyForm::message_TextChanged);
			// 
			// sendMessage
			// 
			this->sendMessage->Font = (gcnew System::Drawing::Font(L"Arial", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->sendMessage->Location = System::Drawing::Point(735, 327);
			this->sendMessage->Name = L"sendMessage";
			this->sendMessage->Size = System::Drawing::Size(200, 85);
			this->sendMessage->TabIndex = 7;
			this->sendMessage->Text = L"Send message";
			this->sendMessage->UseVisualStyleBackColor = true;
			this->sendMessage->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// exit
			// 
			this->exit->Font = (gcnew System::Drawing::Font(L"Arial", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->exit->Location = System::Drawing::Point(860, 12);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(75, 39);
			this->exit->TabIndex = 8;
			this->exit->Text = L"Exit";
			this->exit->UseVisualStyleBackColor = true;
			this->exit->Click += gcnew System::EventHandler(this, &MyForm::exit_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(965, 475);
			this->Controls->Add(this->exit);
			this->Controls->Add(this->sendMessage);
			this->Controls->Add(this->message);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->connectButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->password);
			this->Controls->Add(this->login);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		WSADATA wsaData;
		WORD DllVers = MAKEWORD(2, 2);
		if (WSAStartup(DllVers, &wsaData)) {
			cout << " The error while loading the WinSocket library: " << WSAGetLastError() << endl;
			ExitProcess(EXIT_FAILURE);
		}
		else
		{
			cout << "The WinSocket library was loaded..." << endl;
		}

		SOCKADDR_IN socketInfo;
		ZeroMemory(&socketInfo, sizeof(socketInfo));
		socketInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
		socketInfo.sin_port = htons(27015);
		socketInfo.sin_family = AF_INET;

		SOCKET mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (connect(mainSocket, (SOCKADDR*)&socketInfo, sizeof(socketInfo)) == SOCKET_ERROR)
		{
			cout << "Error while connecting to server: " << WSAGetLastError() << endl;
			ExitProcess(EXIT_FAILURE);
		}
		else
		{
			cout << "Client was connected to server successfully..." << endl;
		}

		sendDataToServer(mainSocket, "LOGIN " + userLogin + " " + userPassword);
		Sleep(500);

		string serverAnswer;
		receiveDataFromServer(mainSocket, serverAnswer);
		Sleep(500);
		if (serverAnswer.substr(0, serverAnswer.find(' ')) == "ERR")
		{
			MessageBox::Show("Invalid login or password as a moderator, try again", "Error while signing in", MessageBoxButtons::OK);
			return;
		}
		else {

			string messageToServer = "FAULT";
			sendDataToServer(mainSocket, messageToServer);
			Sleep(400);
			receiveFaultsFromServer(mainSocket);
		}
		string quitMessage = "QUIT";
		sendDataToServer(mainSocket, quitMessage);
		closesocket(mainSocket);
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}

		
private: System::Void connectButton_Click(System::Object^ sender, System::EventArgs^ e) {
	WSADATA wsaData;
	WORD DllVers = MAKEWORD(2, 2);
	if (WSAStartup(DllVers, &wsaData)) {
		cout << " The error while loading the WinSocket library: " << WSAGetLastError() << endl;
		ExitProcess(EXIT_FAILURE);
	}
	else
	{
		cout << "The WinSocket library was loaded..." << endl;
	}

	SOCKADDR_IN socketInfo;
	ZeroMemory(&socketInfo, sizeof(socketInfo));
	socketInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
	socketInfo.sin_port = htons(27015);
	socketInfo.sin_family = AF_INET;

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(clientSocket, (SOCKADDR*)&socketInfo, sizeof(socketInfo)) == SOCKET_ERROR)
	{
		cout << "Error while connecting to server: " << WSAGetLastError() << endl;
		ExitProcess(EXIT_FAILURE);
	}
	else
	{
		cout << "Client was connected to server successfully..." << endl;
	}

	if(this->login->Text=="" && this->password->Text=="")
	{
		MessageBox::Show("Enter the login and password!", "Connection error", MessageBoxButtons::OK);
	}
	else
	{
		string login = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->login->Text).ToPointer());
		string password = (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->password->Text).ToPointer());
		sendDataToServer(clientSocket, "LOGIN " + login + " " + password);
		Sleep(500);
		
		string serverAnswer;
		receiveDataFromServer(clientSocket, serverAnswer);
		Sleep(500);

		if(serverAnswer.substr(0, serverAnswer.find(' '))=="ERR")
		{
			MessageBox::Show("Invalid login or password, try again", "Error while signing in", MessageBoxButtons::OK);
			return;
		}
		else
		{
			userLogin = login;
			userPassword = password;
			this->timer1->Start();
			receiveThread = (HANDLE)_beginthreadex(0, 0, &receiveMessages, (void*)clientSocket, NULL, 0);
		}
	}
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	if(this->message->Text!="")
	{
		string messageToSend = "SEND ";
		messageToSend += (const char*)(Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->message->Text).ToPointer());
		sendDataToServer(clientSocket, messageToSend);
	}
}
private: System::Void message_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void exit_Click(System::Object^ sender, System::EventArgs^ e) {
	string quitMessage = "QUIT";
	sendDataToServer(clientSocket, quitMessage);
	CloseHandle(receiveThread);
	closesocket(clientSocket);
}
};
}
