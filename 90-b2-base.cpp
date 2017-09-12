/*1551445 童佳燕 计算机科学与技术1班*/
#include"90-b2.h"
#include"cmd_console_tools.h"

int gameInChar()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int x, y;
	int leap = 0,sumOfFile=0;
	char fileName[30];
	char(*file)[30] = (char(*)[30])malloc(20 * 30 * sizeof(char));//大小还需要修整！尽量做到没有内存浪费
	Sudoku sudoku[N][N];
	
	//int baseX = 0, baseY = 0;//游戏进行中需要进行冲突判断，如果有冲突需要有不同的输出，记录基点坐标，便于定位
	system("cls");

	cout << "当前目录下符合条件的文件有：\n";
	string path = "E:\\程设作业\\数独\\数独";
	dir(path,file,&sumOfFile);//找出目录下所有符合条件的文件，并输出
	for (int i = 0; i < sumOfFile; i++)
		cout << file[i] << endl;
	free(file);

	if (getValueFromFile(sudoku,fileName)==-1)
		return -1;
	if (isRight(sudoku) == -1)
	{
		cout << "文件数据错误" << endl;
		return -1;
	}
	init(sudoku);
	if (printCharBegin(sudoku,&leap))//输出字符数组
	{
		cout << "数据有冲突" << endl;
		return -1;
	}
	getxy(hout, x, y);

	stepStore(sudoku, 0, x, y);
	return 0;
}