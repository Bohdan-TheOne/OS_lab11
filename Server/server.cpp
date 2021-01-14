#include "resourses.h"

using namespace std;

unsigned int __stdcall ClientTread(void* threadParam) {
	SOCKET client = (SOCKET)threadParam;

	char buff[512];
	int msgSize;
	string cmd, params;

	bool auth = false;
	string username = "anon";
	bool admin = false;

	NewLog(vector<string>{ "SERVER", "Client connected" });
	strcpy(buff, "#Server Ready.\r\n");
	send(client, buff, strlen(buff), 0);
	while (true) {
		msgSize = recv(client, buff, 512, 0);
		if (msgSize == SOCKET_ERROR)
			break;
		buff[msgSize] = 0;
		NewLog(vector<string>{ "SERVER", "Message recieved" });
		if (parseCMD(buff, cmd, params)) {
			if (cmd == "QUIT")
				NewLog(vector<string>{ cmd, username });
				break;
			if (cmd == "AUTH") {
				if (auth) {
					NewLog(vector<string>{ cmd, username, "Already logined" });
					strcpy(buff, "#You are already logged in.\r\n");
				} else {
					int success = CreateUser(params, username);
					if (success < 0) {
						NewLog(vector<string>{ cmd, username, "Invalid command" });
						strcpy(buff, "#Can`t recognise command.\r\n");
					}
					else if (success > 0) {
						NewLog(vector<string>{ cmd, username, "Username taken" });
						strcpy(buff, "#This username is taken.\r\n");
					}
					else {
						NewLog(vector<string>{ cmd, username, "Account created" });
						strcpy(buff, "#User account created successfuly.\r\n");
						auth = true;
					}
				}
				send(client, buff, strlen(buff), 0);
			}
			if (cmd == "LOGIN") {
				if (auth) {
					NewLog(vector<string>{ cmd, username, "Already logined" });
					strcpy(buff, "#You are already logged in.\r\n");
				} else {
					int success = LogInUser(params, username, admin);
					if (success < 0) {
						NewLog(vector<string>{ cmd, username, "Invalid command" });
						strcpy(buff, "#Can`t recognise command.\r\n");
					}
					else if (success == 1) {
						NewLog(vector<string>{ cmd, username, "Wrong password" });
						strcpy(buff, "!Wrong password.\r\n");
					}
					else if (success == 2) {
						NewLog(vector<string>{ cmd, username, "Wrong username" });
						strcpy(buff, "!No such username.\r\n");
					}
					else {
						NewLog(vector<string>{ cmd, username, "User authorised" });
						strcpy(buff, "#Logged in successfuly.\r\n");
						auth = true;
					}
				}
				send(client, buff, strlen(buff), 0);
			}
			if (cmd == "SEND") {
				if (auth) {
					GetMsg(params, username, admin);
					NewLog(vector<string>{ cmd, username, "Message recieved" });
				}
				else {
					NewLog(vector<string>{ cmd, username, "User not logged" });
					strcpy(buff, "!You are not logged in.\r\n");
					send(client, buff, strlen(buff), 0);
				}
			}
		}
		else {
			NewLog(vector<string>{ cmd, username, "Invalid command" });
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

int CreateUser(string str, std::string& user) {
	string login, password;
	if (!UserId(str, login, password)) {
		return -1;
	}
	Json::Value userList;
	ifstream fin;
	fin.open("users.json");
	fin >> userList;
	fin.close();
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
	user = login;
	return 0;
}

int LogInUser(string str, string& user, bool& admin) {
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
				user = login;
				if (userList.get("idList", 0)[i]["admin"].asBool()) {
					admin = true;
				}
				return 0;
			}
			else {
				return 1;
			}
		}
	}
	return 2;
}

bool GetMsg(string str, string& user, bool admin) {
	ofstream fout;
	fout.open("chatLog.txt", fstream::in | fstream::out | fstream::app);
	if (admin) {
		fout << "<M> ";
	}
	fout << user << " : " << str << endl;
	fout.close();
	return true;
}

string nowTime() {
	time_t now = time(0);
	tm* gmtm = gmtime(&now);
	stringstream out;
	out << gmtm->tm_mday << "-";
	out << 1 + gmtm->tm_mon << "-";
	out << 1900 + gmtm->tm_year << " ";
	out << gmtm->tm_hour << ":";
	out << gmtm->tm_min << ":";
	out << gmtm->tm_sec;
	return out.str();
}

void NewLog(std::vector<std::string> logParam) {
	ofstream fout;
	stringstream ss;
	ss << "[" << nowTime() << "]: ";
	for (int i = 0; i < logParam.size() - 1; ++i) {
		ss << logParam[i] << " | ";
	}
	ss << logParam[logParam.size() - 1];
	ss << endl;
	fout.open("serverLog.txt", fstream::in | fstream::out | fstream::app);
	cout << ss.str();
	fout << ss.str();
	fout.close();
}