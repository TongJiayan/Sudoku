/*1551445 ͯ���� �������ѧ�뼼��1��*/
#include"90-b2.h"
#include"cmd_console_tools.h"

int gameInChar()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int x, y;
	int leap = 0,sumOfFile=0;
	char fileName[30];
	char(*file)[30] = (char(*)[30])malloc(20 * 30 * sizeof(char));//��С����Ҫ��������������û���ڴ��˷�
	Sudoku sudoku[N][N];
	
	//int baseX = 0, baseY = 0;//��Ϸ��������Ҫ���г�ͻ�жϣ�����г�ͻ��Ҫ�в�ͬ���������¼�������꣬���ڶ�λ
	system("cls");

	cout << "��ǰĿ¼�·����������ļ��У�\n";
	string path = "E:\\������ҵ\\����\\����";
	dir(path,file,&sumOfFile);//�ҳ�Ŀ¼�����з����������ļ��������
	for (int i = 0; i < sumOfFile; i++)
		cout << file[i] << endl;
	free(file);

	if (getValueFromFile(sudoku,fileName)==-1)
		return -1;
	if (isRight(sudoku) == -1)
	{
		cout << "�ļ����ݴ���" << endl;
		return -1;
	}
	init(sudoku);
	if (printCharBegin(sudoku,&leap))//����ַ�����
	{
		cout << "�����г�ͻ" << endl;
		return -1;
	}
	getxy(hout, x, y);

	stepStore(sudoku, 0, x, y);
	return 0;
}