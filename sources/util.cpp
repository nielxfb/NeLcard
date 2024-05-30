#ifndef UTIL_CPP
#define UTIL_CPP

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

namespace Util {
	
	int scanInt() {
		char s[255];
		scanf("%[^\n]", s);
		getchar();
		int a = atoi(s);
		return a;
	}
	
	void printDelay(const char* str) {
		int len = strlen(str);
		for (int i = 0; i < len; i++) {
			printf("%c", str[i]);
			Sleep(1);
		}
	}
	
	void cls() {
		system("cls");
	}
	
	void enterToContinue() {
		printDelay("Press ENTER to continue..");
		getchar();
	}
	
}

#endif
