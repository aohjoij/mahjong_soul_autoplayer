#include<iostream>
#include<Windows.h>

using namespace std;

int main(void) {
	string url;
	int hh, mm;
	cout << "URL����͂��ĂˁI" << endl <<"URL = ";
	cin >> url;
	while (1) {
		char c;
		cout << "\"" << url << "\"�ł����ł����`�H(y/n)�F";
		cin >> c;
		if (c == 'y' || c == 'Y') {
			break;
		}
		else if (c == 'n' || c == 'N') {
			cout << "URL����͂��ĂˁI" << endl << "URL = ";
			cin >> url;
			continue;
		}
		else continue;
	}
	while (1) {
		cout << "���������ɐݒ�(access)���܂����H(hh�� mm��)" << endl;
		while (1) {
			cout << "hh(0�`23) = ";
			cin >> hh;
			if (hh < 24 && hh >= 0)break;
		}
		while (1) {
			cout << "mm(0�`59) = ";
			cin >> mm;
			if (mm < 60 && mm >= 0)break;
		}
		char c;
		cout << hh << "��" << mm << "���ł����ł����`�H(y/n)�F";
		cin >> c;
		if (c == 'y' || c == 'Y') {
			break;
		}
		else if (c == 'n' || c == 'N') {
			continue;
		}
	}
	url = "start " + url;
	while (1) {
		SYSTEMTIME starttime;
		GetLocalTime(&starttime);
		if (starttime.wHour == hh && starttime.wMinute == mm) {
			system(url.c_str());
			break;
		}
		Sleep(10 * 1000);
	}
	return 0;
}