#include<iostream>
#include<Windows.h>

using namespace std;

int main(void) {
	string url;
	int hh, mm;
	cout << "URL‚ð“ü—Í‚µ‚Ä‚ËI" << endl <<"URL = ";
	cin >> url;
	while (1) {
		char c;
		cout << "\"" << url << "\"‚Å‚¢‚¢‚Å‚·‚©`H(y/n)F";
		cin >> c;
		if (c == 'y' || c == 'Y') {
			break;
		}
		else if (c == 'n' || c == 'N') {
			cout << "URL‚ð“ü—Í‚µ‚Ä‚ËI" << endl << "URL = ";
			cin >> url;
			continue;
		}
		else continue;
	}
	while (1) {
		cout << "‰½Žž‰½•ª‚ÉÝ’è(access)‚µ‚Ü‚·‚©H(hhŽž mm•ª)" << endl;
		while (1) {
			cout << "hh(0`23) = ";
			cin >> hh;
			if (hh < 24 && hh >= 0)break;
		}
		while (1) {
			cout << "mm(0`59) = ";
			cin >> mm;
			if (mm < 60 && mm >= 0)break;
		}
		char c;
		cout << hh << "Žž" << mm << "•ª‚Å‚¢‚¢‚Å‚·‚©`H(y/n)F";
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