/*1551445 童佳燕 计算机科学与技术1班*/
#include"90-b2.h"
#include"cmd_console_tools.h"

int main()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int x, y, choice;

	printMenu();
	getxy(hout, x, y);
	getChoice(&choice, x, y);
	switch (choice)
	{
	    case 1:
			if (gameInChar() == -1)
				return -1;
		    break;
	    case 2:
			if (gameInConsole() == -1)
				return -1;
		    break;
	    case 3:
			if (gameAuto()== -1)
				return-1;
		    break;
	    default:
		    return 0;
	}
	return 0;
}