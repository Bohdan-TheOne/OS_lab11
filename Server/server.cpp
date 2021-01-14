#include "resourses.h"

using namespace std;

unsigned int __stdcall ClientTread(void* threadParam) {
	SOCKET client = (SOCKET)threadParam;

	char buff[512];
	int msgSize;
	string cmd, params;
	bool auth = false;

	strcpy(buff, "#Server Ready.\r\n");
	send(client, buff, strlen(buff), 0);
	while (true) {
		msgSize = recv(client, buff, 512, 0);
		if (msgSize == SOCKET_ERROR)
			break;
		buff[msgSize] = 0;
		if (parseCMD(buff, cmd, params)) {
			if (cmd == "QUIT")
				break;
			if (cmd == "AUTH") {
				if (auth) {
					strcpy(buff, "#You are already logged in.\r\n");
				} else {
					int success = CreateUser(params);
					if (success < 0) {
						strcpy(buff, "#Can`t recognise command.\r\n");
					}
					else if (success > 0) {
						strcpy(buff, "#This username is taken.\r\n");
					}
					else {
						strcpy(buff, "#User account created successfuly.\r\n");
						auth = true;
					}
				}
				send(client, buff, strlen(buff), 0);
			}
			if (cmd == "LOGIN") {
				if (auth) {
					strcpy(buff, "#You are already logged in.\r\n");
				} else {
					int success = LogInUser(params);
					if (success < 0) {
						strcpy(buff, "#Can`t recognise command.\r\n");
					}
					else if (success == 1) {
						strcpy(buff, "!Wrong password.\r\n");
					}
					else if (success == 2) {
						strcpy(buff, "!No such username.\r\n");
					}
					else {
						strcpy(buff, "#Logged in successfuly.\r\n");
						auth = true;
					}
				}
				send(client, buff, strlen(buff), 0);
			}
			if (cmd == "SEND") {
				if (auth) {
					
				}
				else {
					strcpy(buff, "!You are not logged in.\r\n");
					send(client, buff, strlen(buff), 0);
				}
			}
		}
		else {
			strcpy(buff, "!Invalid command.\r\n");
			send(client, buff, strlen(buff), 0);
		}
	}
	closesocket(client);
}

string trim(const string& str) {
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first) {
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

bool parseCMD(char* str, std::string& cmd, std::string& params) {
	int n;
	string tmp = str;
	tmp = trim(tmp);
	std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
	if ((n = tmp.find(' ')) == -1) {
		if (tmp != "QUIT")
			return false;
		cmd = tmp;
		return true;
	}
	cmd = tmp.substr(0, n);
	params = tmp.substr(n + 1, tmp.length());
	cmd = trim(cmd);
	params = trim(params);
	if ((cmd != "AUTH") && (cmd != "FILE") && (cmd != "LOGIN"))
		return false;
	return true;
	return false;
}

bool UserId(string str, string& login, string& passwd) {
	int n;
	if ((n = str.find(' ')) == -1) {
		return false;
	}
	login = str.substr(0, n);
	passwd = str.substr(n + 1, str.length());
	login = trim(login);
	passwd = trim(passwd);
	std::transform(login.begin(), login.end(), login.begin(), ::tolower);
	return true;
}

int CreateUser(string str) {
	string login, password;
	if (!UserId(str, login, password)) {
		return -1;
	}
	cout << "|" << login << "|" << password << "|" << endl;
	Json::Value userList;
	ifstream fin;
	fin.open("users.json");
	fin >> userList;
	fin.close();
	cout << userList << endl;
	int n = userList.get("number", 0).asInt();
	for (int i = 0; i < n; ++i) {
		if (login == userList.get("idList", 0)[i]["login"].asString()) {
			return 1;
		}
	}
	userList["number"] = n + 1;
	userList["idList"][n]["login"] = login;
	userList["idList"][n]["passw"] = password;
	userList["idList"][n]["fault"] = 0;
	userList["idList"][n]["admin"] = false;
	ofstream fout;
	fout.open("users.json");
	fout << userList;
	fout.close();
	return 0;
}

int LogInUser(string str) {
	string login, password;
	if (!UserId(str, login, password)) {
		return -1;
	}
	cout << "|" << login << "|" << password << "|" << endl;
	Json::Value userList;
	ifstream fin;
	fin.open("users.json");
	fin >> userList;
	fin.close();
	cout << userList << endl;
	int n = userList.get("number", 0).asInt();
	for (int i = 0; i < n; ++i) {
		if (login == userList.get("idList", 0)[i]["login"].asString()) {
			if (password == userList.get("idList", 0)[i]["passw"].asString()) {
				return 0;
			}
			else {
				return 1;
			}
		}
	}
	return 2;
}