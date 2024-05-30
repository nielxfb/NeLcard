#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "../headers/util.h"

namespace Game {
	
	const short WIDTH = 4;
	const short HEIGHT = 4;
	
	const short HEART = 3;
	const short DIAMOND = 4;
	const short CLUB = 5;
	const short SPADE = 6;
	
	const char symbols[] = { HEART, DIAMOND, CLUB, SPADE };
	
	char cards[HEIGHT+1][WIDTH+1] = {};
	char blankCards[HEIGHT+1][WIDTH+1] = {};
	
	void init() {
		int totalCards = HEIGHT * WIDTH;
		int countSymbols = sizeof(symbols) / sizeof(symbols[0]);
		int countEachSymbol = totalCards / countSymbols;
		
		int symbolCount[countSymbols];
		for (int i = 0; i < countSymbols; i++) {
			symbolCount[i] = 0;
		}
		
		srand(time(NULL));
		
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				int symbolIdx;
				do {
					symbolIdx = rand() % countSymbols;
				} while (symbolCount[symbolIdx] >= countEachSymbol);
				
				cards[i][j] = symbols[symbolIdx];
				blankCards[i][j] = ' ';
				
				symbolCount[symbolIdx]++;
			}
		}
		
	}
	
	void setBlank(char cards[][WIDTH+1]) {
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				cards[i][j] = ' ';
			}
		}
	}
	
	void printTopTable() {
		printf("%c %c", 24, 201);
		for(int i = 0; i < WIDTH * 2 - 1; i++) {
			if (i % 2 == 0) for (int i = 0; i < 3; i++) printf("%c", 205);
			else printf("%c", 203);
		}
		printf("%c\n", 187);
	}
	
	void printMidTable() {
		printf("  %c", 204);
		for (int i = 0; i < WIDTH * 2 - 1; i++) {
			if (i % 2 == 0) for (int i = 0; i < 3; i++) printf("%c", 205);
			else printf("%c", 206);
		}
		printf("%c\n", 185);
	}
	
	void printBotTable() {
		printf("  %c", 200);
		for(int i = 0; i < WIDTH * 2 - 1; i++) {
			if (i % 2 == 0) for (int i = 0; i < 3; i++) printf("%c", 205);
			else printf("%c", 202);
		}
		printf("%c\n", 188);
	}
	
	void printXArrow() {
		int x = 1;
		printf("   ");
		for (int i = 0; i < WIDTH * 2 - 1; i++) {
			if (i % 2 == 0) printf(" %d ", x++);
			else printf(" ");
		}
		printf("%c X\n\n", 26);
	}
	
	void printCards(char cards[][WIDTH+1]) {
		puts("Y");
		printTopTable();
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (j == 0) printf("%d ", 4-i);
				printf("%c", 186);
				printf(" %c ", cards[i][j]);
			}
			printf("%c\n", 186);
			if (i != HEIGHT-1) printMidTable();
		}
		printBotTable();
		printXArrow();
	}
	
	void printCardDelay() {
		puts("Y");
		printTopTable();
		Sleep(1);
		for (int i = 0; i < HEIGHT; i++) {
			for (int j = 0; j < WIDTH; j++) {
				if (j == 0) printf("%d ", 4-i);
				printf("%c", 186);
				printf(" %c ", cards[i][j]);
			}
			printf("%c\n", 186);
			Sleep(1);
			if (i != HEIGHT-1) {
				printMidTable();
				Sleep(1);
			}
		}
		printBotTable();
		Sleep(1);
		printXArrow();
		Sleep(1);
	}
	
	void printDetails(int lifePoint) {
		Util::cls();
		printCards(blankCards);
		
		printf("Lifepoint: %d\n\n", lifePoint);
	}
	
	char retrieveChar(int yIdx, int xIdx) {
		return cards[4-yIdx][xIdx-1];
	}
	
	void replaceBlankChar(int yIdx, int xIdx, char symb) {
		blankCards[4-yIdx][xIdx-1] = symb;
	}
	
	void markMatched(int yIdx, int xIdx) {
		cards[4-yIdx][xIdx-1] = 'x';
		blankCards[4-yIdx][xIdx-1] = 'x';
	}
	
	void startGame() {
		Util::cls();
		init();
		printCardDelay();
		Util::printDelay("Press ENTER to start playing..");
		getchar();
		int lifePoint = 3;
		int matchCount = 0;
		while (lifePoint > 0 && matchCount < 8) {

			int xFirst, yFirst, xSecond, ySecond;
			
			while (true) {
				printDetails(lifePoint);
				Util::printDelay("Input the x coordinate of first card: ");
				xFirst = Util::scanInt();
				if (xFirst >= 1 && xFirst <= 4) break;
				puts("Please enter a valid coordinate!");
				Util::enterToContinue();
			}
			
			while (true) {
				printDetails(lifePoint);
				Util::printDelay("Input the y coordinate of first card: ");
				yFirst = Util::scanInt();
				if (yFirst >= 1 && yFirst <= 4) break;
				puts("Please enter a valid coordinate!");
				Util::enterToContinue();
			}
			
			if (retrieveChar(yFirst, xFirst) == 'x') {
				Util::printDelay("The card has been matched! Please choose another card..\n");
				Util::enterToContinue();
				continue;
			}
			
			replaceBlankChar(yFirst, xFirst, retrieveChar(yFirst, xFirst));
			
			while (true) {
				printDetails(lifePoint);
				Util::printDelay("Input the x coordinate of second card: ");
				xSecond = Util::scanInt();
				if (xSecond >= 1 && xSecond <= 4) break;
				puts("Please enter a valid coordinate!");
				Util::enterToContinue();
			}
			
			while (true) {
				printDetails(lifePoint);
				Util::printDelay("Input the y coordinate of second card: ");
				ySecond = Util::scanInt();
				if (ySecond >= 1 && ySecond <= 4) break;
				puts("Please enter a valid coordinate!");
				Util::enterToContinue();
			}
			
			if (retrieveChar(ySecond, xSecond) == 'x') {
				Util::printDelay("The card has been matched! Please choose another card..\n");
				Util::enterToContinue();
				replaceBlankChar(yFirst, xFirst, ' ');
				continue;
			}
			
			if (yFirst == ySecond && xFirst == xSecond) {
				Util::printDelay("Please choose different cards!\n");
				Util::enterToContinue();
				replaceBlankChar(yFirst, xFirst, ' ');
				continue;
			}
			
			replaceBlankChar(ySecond, xSecond, retrieveChar(ySecond, xSecond));
			
			if (retrieveChar(yFirst, xFirst) == retrieveChar(ySecond, xSecond)) {
				matchCount++;
				printDetails(lifePoint);
				Util::printDelay("Cards are matched! ");
				Util::enterToContinue();

				markMatched(yFirst, xFirst);
				markMatched(ySecond, xSecond);
			} else {
				lifePoint--;
				printDetails(lifePoint);
				Util::printDelay("Cards are not matched! Lifepoint -1..\n");
				Util::enterToContinue();
				
				replaceBlankChar(yFirst, xFirst, ' ');
				replaceBlankChar(ySecond, xSecond, ' ');
			}
		}
		
		Util::cls();
		if (lifePoint == 0) Util::printDelay("Game Over\n");
		else if (matchCount == 8) Util::printDelay("You win!\n");
		Util::enterToContinue();
	}

	
}

#endif
