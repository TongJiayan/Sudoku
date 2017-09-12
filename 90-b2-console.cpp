/*1551445 ͯ���� �������ѧ�뼼��1��*/
#include"90-b2.h"
#include"cmd_console_tools.h"
int gameInConsole()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setconsoleborder(hout,100, 40, 40);//�ں�����

	int sumOfFile = 0, isInvalid = 0,x,y;
	char fileName[30];
	struct Sudoku sudoku[N][N];

	char(*file)[30] = (char(*)[30])malloc(20 * 30 * sizeof(char));
	string path = "E:\\������ҵ\\����\\����";
	dir(path, file, &sumOfFile);
	fileMenu(file,sumOfFile);
	int fileOrder=chooseAction(file, sumOfFile);
	strcpy_s(fileName, file[fileOrder]);

	//bug,�϶�����������ʾ����ֱ䶯��
	if (getValueFromFile(sudoku, fileName,1) == -1)
		return -1;
	if (isRight(sudoku) == -1)
	{
		cout << "�ļ����ݴ���" << endl;
		return -1;
	}
	init(sudoku);
	if (printConsoleAllFrame(sudoku, &isInvalid))//����ַ�����
	{
		cout << "�����г�ͻ" << endl;
		return -1;
	}
	getxy(hout, x, y);
	stepStore(sudoku, 1, x, y);
	return 0;
}

int gameAuto()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setconsoleborder(hout, 100, 40, 40);//�ں�����

	int sumOfFile = 0, isInvalid = 0, x, y;
	char fileName[30];
	struct Sudoku sudoku[N][N];
	Place points[81];

	char(*file)[30] = (char(*)[30])malloc(20 * 30 * sizeof(char));
	string path = "E:\\������ҵ\\����\\����";
	dir(path, file, &sumOfFile);
	fileMenu(file, sumOfFile);
	int fileOrder = chooseAction(file, sumOfFile);
	strcpy_s(fileName, file[fileOrder]);

	//bug,�϶�����������ʾ����ֱ䶯��
	if (getValueFromFile(sudoku, fileName, 1) == -1)
		return -1;
	if (isRight(sudoku) == -1)
	{
		cout << "�ļ����ݴ���" << endl;
		return -1;
	}
	init(sudoku);
	if (printConsoleAllFrame(sudoku, &isInvalid))
	{
		cout << "�����г�ͻ" << endl;
		return -1;
	}
	getxy(hout, x, y);

	int rowStore[N][N], colStore[N][N], blockStore[3][3][N];
	for(int i=0;i<N;i++)
		for (int j = 1; j <=N; j++)
		{
			rowStore[i][j] = 0;
			colStore[i][j] = 0;
		}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 1; k <= N; k++)
				blockStore[i][j][k] = 0;

	int num = allocateEmptyPoints(points, sudoku,rowStore,colStore,blockStore);
	int flag = 0,paceNum = 0;
	DFS(num, points, sudoku,&flag,rowStore,colStore,blockStore,&paceNum);
	cout << endl;
	return 0;
}
