#pragma once
/*1551445 童佳燕 计算机科学与技术1班*/
#include<iostream>
#include<string>
#include<io.h>
#include<fstream>
#include<cstring>
#include<Windows.h>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#define N 9
using namespace std;

struct Step
{
	struct Step *before;
	char index[4];
	int preValue;
	struct Step *next;
};
/*使用结构体将值与标记封装起来，便于输出冲突冲突*/
struct Sudoku
{
	int value;
	struct Place;//在数组中的i,j
	bool isErr;
	bool fixed;
};

struct Place
{
	int x;
	int y;
 };
void printMenu();
void init(Sudoku(*sudoku)[N]);
void getChoice(int *choice, int x, int y);
int getValueFromFile(Sudoku(*value)[N], char fileName[30], int isFromKey=0);
int isRight(Sudoku(*value)[N]);
void signIsErr(Sudoku(*sudoku)[N], int *leap);
void setPrintColor(Sudoku(*sudoku)[N], int i, int j);
int printCharBegin(Sudoku(*value)[N],int *leap);
int isRowDifferent(Sudoku(*value)[N], int row);
int isColDifferent(Sudoku(*value)[N], int col);
int isBlockDifferent(Sudoku(*value)[N], int row, int col);

void getCheckInput(Sudoku(*sudoku)[N], char index[4]);
int isGameOver(Sudoku(*sudoku)[N], int leap);
void stepStore(Sudoku(*sudoku)[N], int isConsole, int x, int y);
void release(Step *head);
int gameInChar();
void dir(string path,char file[][30],int *sum);
int allocateEmptyPoints(Place points[81], Sudoku(*sudoku)[N], int rowStore[][N], int colStore[][N], int blockStore[][3][N]);
void DFS(int n, Place points[81], Sudoku(*sudoku)[N], int *flag, int rowStore[][N], int colStore[][N], int blockStore[][3][N],int *paceNum);
void showSearchAction(int x, int y, Sudoku(*sudoku)[N]);
void fileMenu(char(*file)[30],int numOfFile);
int chooseAction(char(*file)[30], int numOfFile);
void printConsoleOneFrame(int baseX, int baseY);
int printConsoleAllFrame(Sudoku(*sudoku)[N], int *isInvalid);
int gameInConsole();
int gameAuto();