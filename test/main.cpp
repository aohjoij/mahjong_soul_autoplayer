#include<iostream>
#include<Windows.h>

using namespace std;

int main(void) {
	string url;
	int hh, mm;
	cout << "URLを入力してね！" << endl <<"URL = ";
	cin >> url;
	while (1) {
		char c;
		cout << "\"" << url << "\"でいいですか〜？(y/n)：";
		cin >> c;
		if (c == 'y' || c == 'Y') {
			break;
		}
		else if (c == 'n' || c == 'N') {
			cout << "URLを入力してね！" << endl << "URL = ";
			cin >> url;
			continue;
		}
		else continue;
	}
	while (1) {
		cout << "何時何分に設定(access)しますか？(hh時 mm分)" << endl;
		while (1) {
			cout << "hh(0〜23) = ";
			cin >> hh;
			if (hh < 24 && hh >= 0)break;
		}
		while (1) {
			cout << "mm(0〜59) = ";
			cin >> mm;
			if (mm < 60 && mm >= 0)break;
		}
		char c;
		cout << hh << "時" << mm << "分でいいですか〜？(y/n)：";
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