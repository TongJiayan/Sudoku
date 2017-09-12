/*1551445 ͯ���� �������ѧ�뼼��1��*/
#include"90-b2.h"
#include"cmd_console_tools.h"

void printMenu()
{
	cout << "--------------------------------------" << endl;
	cout << "1.�ַ�������Ϸ�������˹��ܣ�" << endl;
	cout << "2.ͼ�ν��湦�ܣ������˹��ܣ�" << endl;
	cout << "3.ͼ�ν����Զ���⣨��ʾ���̲�����ʱ��" << endl;
	cout << "0.�˳�" << endl;
	cout << "--------------------------------------" << endl;
	cout << "����ѡ��0-3��";
}

/*����choice���ж������Ƿ���ȷ�����ƹ���λ�ã��ṩ���õ�ʹ������*/
void getChoice(int *choice, int x, int y)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	while (1)
	{
		cin >> *choice;
		if (*choice >= 0 && *choice <= 3)
		{
			gotoxy(hout, 0, y + 1);
			cout << "                                 ";
			gotoxy(hout, 0, y + 1);
			break;
		}
		else
		{
			gotoxy(hout, 0, y + 1);
			cout << "input error,please again" << endl;
			gotoxy(hout, x, y);
			cout << "  ";
			gotoxy(hout, x, y);
		}
	}
}

void init(Sudoku(*sudoku)[N])
{
	for(int i=0;i<N;i++)
		for (int j = 0; j < N; j++)
		{
			if (sudoku[i][j].value == 0)//����ԭ����ʼֵ���б�ǣ����ɲ���
				sudoku[i][j].fixed = 0;
			else
				sudoku[i][j].fixed =1;
			sudoku[i][j].isErr = 0;
		}
}
/*������ӦĿ¼������txt�ļ�*/
void dir(string path,char file[][30],int *sum)
{
	long hFile = 0;
	struct _finddata_t fileInfo;
	string pathName, exdName;
	if ((hFile = _findfirst(pathName.assign(path).append("\\*.txt").c_str(), &fileInfo)) == -1)
		return;
	strcpy_s(file[*sum], fileInfo.name);
	while (_findnext(hFile, &fileInfo) == 0)
	{
		(*sum)++;
		strcpy_s(file[*sum], fileInfo.name);
	}
	_findclose(hFile);
	return;
}

/*error��Ĭ��Ϊsudoku.txt��δ���*/
int getValueFromFile(Sudoku(*value)[N],char fileName[30],int isFromKey)
{
	ifstream fin;
	//char fileName[30];
	if (isFromKey == 0)
	{
		cout << "������������Ŀ�ļ������س���ʾĬ��sudoku.txt��:";
		//if (_getch() == '\r')
			//strcat_s(fileName ,"sudoku.txt");
		//else
		cin >> fileName;
	}
	fin.open(fileName, ios::in);
	if (!fin.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
		return -1;
	}
	Sudoku(*p)[N] = value;
	for (; p - value < N; p++)
		for (int i = 0; i < N; i++)
			fin >> (*p + i)->value;
	return 0;
}

int isRight(Sudoku(*value)[N])//�жϳ�ʼ�ļ��Ƿ�Ϸ���0-9��
{
	Sudoku(*p)[N] = value;
	for (; p - value < N; p++)
		for (int j = 0; j < N; j++)
			if ((*p + j)->value <= 9 && (*p + j)->value >= 0)
				;
			else
				return -1;
	return 0;
}

int printCharBegin(Sudoku(*sudoku)[N],int *leap)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "���������Ϊ" << endl;
	for (int i = 0; i < N; i++)
	{
		if (i % 3 == 0)
			cout << "-+";
		cout << "-" << (char)('a' + i);
	}
	cout << "-";
	cout << endl;

	/*���жϺ����ĵ��ý��м�֦�������ظ��жϺ͵��ã�ԭ������·�ע�ͣ���Ȼ����򵥣��������й�������*/
	signIsErr(sudoku, leap);
	/*for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			leap = (isRowDifferent(value, i) == -1) || (isColDifferent(value, j) == -1)|| (isBlockDifferent(value, i, j) == -1);
*/
		for (int i = 0; i < N; i++)
	{
		cout << i + 1;
		for (int j = 0; j < N; j++)
		{
			if (j % 3 == 0)
				cout << "| ";
			setPrintColor(sudoku, i, j);//���ݹ���ֵ���㣬���㣬��ͻ����������������ɫ
			cout << sudoku[i][j].value << " ";
			sudoku[i][j].isErr = 0;//��ԭ
			setcolor(hout, COLOR_BLACK, COLOR_WHITE);
		}

		if (i % 3 == 2)
		{
			cout << endl;
			for (int k = 0; k < N; k++)
			{
				if (k % 3 == 0)
					cout << "-+";
				cout << "--";
			}
			cout << "-";
		}
		cout << endl;
	}
	return *leap;
}

void signIsErr(Sudoku(*sudoku)[N],int *leap)//����ÿ��Ԫ�أ��ж��Ƿ�������Ԫ���г�ͻ�������漰һϵ���������ε����⣬ʵ�鱨����ϸ����
{
	for (int i = 0; i < N; i++)
	{
		if (isRowDifferent(sudoku, i) == -1)
			continue;
		for (int j = 0; j < N; j++)
			if (sudoku[i][j].isErr == 1)
			{
				*leap = 1;
				continue;
			}
			else if (isColDifferent(sudoku, j) == -1)
				continue;
			else if (isBlockDifferent(sudoku, i, j) == -1)
				continue;
	}
}

void setPrintColor(Sudoku(*sudoku)[N], int i, int j)//���������ɫ
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (sudoku[i][j].isErr == 1)//��ͬ����ɫ���
	{
		if (sudoku[i][j].fixed == 1)
			setcolor(hout, COLOR_HWHITE, COLOR_HBLUE);//�̶�����������ɫǰ��ɫ��ʾ
		else if (sudoku[i][j].value == 0)
			setcolor(hout, COLOR_HWHITE, COLOR_HYELLOW);
		else
			setcolor(hout, COLOR_HWHITE, COLOR_HRED);
	}
	else if (sudoku[i][j].value == 0)
		setcolor(hout, COLOR_BLACK, COLOR_HYELLOW);
	else
		if (sudoku[i][j].fixed == 1)
			setcolor(hout, COLOR_BLACK, COLOR_HBLUE);
		else
			setcolor(hout, COLOR_BLACK, COLOR_HBLUE);

}

int isRowDifferent(Sudoku(*value)[N], int row)//�����ж��Ƿ����ظ���,������ظ��ģ����� -1,ͬʱ�����е�����ֵ��isErr��ֵΪ1
{
	for (int j = 0; j < N; j++)
		if (value[row][j].value == 0)
			continue;
		else
			for (int k = j + 1; k < N; k++)
				if (value[row][k].value == value[row][j].value)
				{
					for (int m = 0; m < N; m++)
						value[row][m].isErr = 1;
					return -1;
				}
	return 0;
}

int isColDifferent(Sudoku(*value)[N], int col)//�����ж��Ƿ����ظ���
{
	for (int i = 0; i < N; i++)
		if (value[i][col].value == 0)
			continue;
		else
			for (int k = i + 1; k < N; k++)
				if (value[i][col].value == value[k][col].value)
				{
					for (int m = 0; m < N; m++)
						value[m][col].isErr = 1;//��Ϊ��ǣ������ʹ��
					return -1;
				}
	return 0;
}

int isBlockDifferent(Sudoku(*value)[N], int row, int col)//3*3�������ж��Ƿ����ظ���
{
	int Y = row / 3 * 3, X = col / 3 * 3;//Ѱ��ÿ��3*3С����ġ�ͷ��
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (value[Y + i][X + j].value == 0)//����0�ǲ���Ҫ�����ͬ��
				continue;
			else
				for (int k = i; k < 3; k++)
					for (int h = 0; h < 3; h++)
						if (value[Y + k][X + h].value == value[Y + i][X + j].value && (k!=i||h!=j))//����֮����int h=j  ��������֣�ȱ��k!=i||h!=j  �����ҵ��ض��ҵ���ͬ��ֵ��Ҳ��������
						{
							for (int m = 0; m < 3; m++)
								for (int n = 0; n < 3; n++)
									value[Y + m][X + n].isErr = 1;//���ڱ�����Ƿ��ͻ�����б����еģ����б�ǣ��������
							return -1;
						}
	return 0;
}


void getCheckInput(Sudoku (*sudoku)[N], char index[4])//��������Ƿ���ȷ��ͬʱ��index��ֵ
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int x, y;
	cout << "�밴��\\��\\ֵ�ķ�ʽ����(���磺5c6=�����е�c��Ϊ6)������bk��ʾ����һ��";
	getxy(hout, x, y);
	while (1)
	{
		gotoxy(hout, x, y);
		cout << "           ";
		gotoxy(hout, x, y);
		cin >> index;
		if (cin.fail())
		{
			gotoxy(hout, 0, y + 1);
			cout << "�����������������" << endl;
			continue;
		}
		if (index[0] == 'b'&&index[1] == 'k')
			break;
		gotoxy(hout, 0, y + 1);
		cout << "                  ";
		gotoxy(hout, 0, y + 1);
		if (index[0] > '9' || index[0] < '1')
		{
			cout << "��" << index[0] << "�в��ǡ�0-9��������������";
			continue;
		}
		if (index[1] > 'i' || index[1] < 'a')
		{
			cout << "��" << index[1] << "�в��ǡ�a-i��������������";
			continue;
		}
		if (index[2] > '9' || index[2] < '1')
		{
			cout << "�����ֵ" << index[2] << "���ǡ�1-9��,����������";
			continue;
		}
		if (sudoku[index[0] - '1'][index[1] - 'a'].fixed ==1)//��ʼ����ֵ�ǲ����Ը��ĵ�
		{
			cout << "��λ�ò���������" << endl;
			continue;
		}
		break;
	}
}

void stepStore(Sudoku(*sudoku)[N], int isConsole, int x, int y)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int isInvalid=0;
	struct Step *q = NULL, *p = NULL, *head = NULL;
	while (!isGameOver(sudoku, isInvalid))
	{
		isInvalid = 0;
		int isBack = 0;//��Ϊ�ж��Ƿ���˵ı��
		if (p != NULL)
			q = p;
		p = (struct Step *)malloc(sizeof(Step));
		if (p == NULL)//ͬ��
			return ;
		if (q == NULL)//�����һ�������˻�֮�󣬸���p��nullptr�����Ա���
		{
			head = p;
			head->before = NULL;
		}
		else
		{
			q->next = p;
			p->before = q;//����˫������
		}
		gotoxy(hout, x, y + 1);
		getCheckInput(sudoku, p->index);//��¼����
		if (!strcmp(p->index, "bk"))
		{
			/*����Ե�һ���ͻ��˵��жϣ����ԣ�ֻ�˵��ڶ�������ʵ�ϵ�һ�����ǿ��Ա��˵���*/
			if (p == head)
			{
				cout << "���ǵ�һ�������ܻ���" << endl;
				free(head);
				p = NULL;
				continue;
			}

			free(p);//�ͷ�������Ŀռ�
			q->next = NULL;
			p = q;//Ϊ����Ӧqǰp�󣬶�p,q������λ
			q = q->before;
			isBack = 1;
		}
		int row = (p->index)[0] - '1';
		int col = (p->index)[1] - 'a';
		if (isBack)
		{
			sudoku[row][col].value = p->preValue;
			free(p);//�������,pָ��Ŀռ��¼�Ĳ����ǲ���Ҫ�ģ���˿����ͷ�
			if (q != NULL)
				q->next = NULL;
			p = q;//careful����Ȼ�ͻز�ȥ��
		}
		else
		{
			p->preValue = sudoku[row][col].value;//��¼����֮ǰ��ֵ
			sudoku[row][col].value = ((p->index)[2] - '0');
			p->next = NULL;
		}
		if (isConsole == 1)
		{
			if (printConsoleAllFrame(sudoku, &isInvalid))
				cout << "�����г�ͻ";
		}
		else
			if (printCharBegin(sudoku, &isInvalid))
				cout << "�����г�ͻ";
		isGameOver(sudoku, isInvalid);
	}
	release(head);
}

int isGameOver(Sudoku(*sudoku)[N], int leap)//�ж��Ƿ���Ϸ����
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (sudoku[i][j].value == 0)
				return 0;
	if (leap == 1)
	{
		cout << "Game Over" << endl;
		return -1;
	}
	else
	{
		cout << "You Win" << endl;
		return 1;
	}
}

void release(Step *head)//�ͷŶ�̬�ռ�
{
	Step *p = head, *q = head;
	while (q != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
}

void fileMenu(char (*file)[30],int numOfFile)
{
	const int baseX = 60, baseY = 2,height=9,weight=23;
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hout,baseX,baseY);
	cout << "���������ļ�";
	gotoxy(hout, baseX, baseY + 1);
	cout << "������������������������";
	for (int i = 0; i < height; i++)
	{
		gotoxy(hout, baseX, baseY + 2 + i);
		cout << "�� ";
		if (i == 0)
			setcolor(hout, COLOR_WHITE, COLOR_BLACK);
		cout << file[i];
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
		gotoxy(hout, baseX + weight-1, baseY + 2 + i);
		cout << "��";
	}
	gotoxy(hout, baseX, baseY +height+1);
	cout << "������������������������\n";
	
}

int chooseAction(char(*file)[30],int numOfFile)//�Ľ���ʱ�򣬳��Բ��
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int baseX = 60, baseY = 2;
	int key1, key2;
	int fileOrder = 0, top = 0;

	while (1)
	{
		key1 = _getch();
		if (key1 == '\r')
			break;
		key2 = _getch();
		if (key1 == 224 && key2 == 80)//���¼�
		{
			if (fileOrder == numOfFile - 1)
				continue;//��ָ�����һ���ļ����ô����벻��Ч
			fileOrder++;
			if (fileOrder == top + 8)//��ָ���file
			{
				top++;
				for (int i = 0; i < 7; i++)
				{
					gotoxy(hout, baseX + 3, baseY + 2 + i);
					cout <<"                  ";
					gotoxy(hout, baseX +3, baseY + 2 + i);
					cout << file[top + i];
				}
				gotoxy(hout, baseX + 3, baseY + 9);
				cout << "                  ";//��ո�λ��֮ǰ��ӡ����Ϣ
				gotoxy(hout, baseX + 3, baseY + 9);
				setcolor(hout, COLOR_WHITE, COLOR_BLACK);//������ɫ
				cout << file[top + 7];
				setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			}
			else
			{
				gotoxy(hout, baseX + 3, baseY + 2 + fileOrder - top-1);
				setcolor(hout, COLOR_BLACK, COLOR_WHITE);
				cout << file[fileOrder-1];
				gotoxy(hout, baseX + 3, baseY + 2 + fileOrder - top);
				setcolor(hout, COLOR_WHITE, COLOR_BLACK);
				cout << file[fileOrder];
				setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			}
		}
		else if (key1 == 224 && key2 == 72)
		{
			if (fileOrder == 0)
				continue;
			fileOrder--;
			if (fileOrder == top - 1)
			{
				top--;
				gotoxy(hout, baseX + 3, baseY + 2);
				cout << "                  ";
				gotoxy(hout, baseX + 3, baseY + 2);
				setcolor(hout, COLOR_WHITE, COLOR_BLACK);
				cout << file[top];
				setcolor(hout, COLOR_BLACK, COLOR_WHITE);

				for (int i = 1; i <= 7; i++)
				{
					gotoxy(hout, baseX + 3, baseY + 2 + i);
					cout << "                  ";
					gotoxy(hout, baseX +3, baseY + 2 + i);
					cout << file[top + i];
				}
			}
			else
			{
				gotoxy(hout, baseX + 3, baseY + 2 + fileOrder - top+1);
				setcolor(hout, COLOR_BLACK, COLOR_WHITE);
				cout << file[fileOrder+1];
				gotoxy(hout, baseX + 3, baseY + 2 + fileOrder - top );
				setcolor(hout, COLOR_WHITE, COLOR_BLACK);
				cout << file[fileOrder];
				setcolor(hout, COLOR_BLACK, COLOR_WHITE);
			}
		}	
	}
	gotoxy(hout, 0, 0);
	return fileOrder;
}

void printConsoleOneFrame(int baseX, int baseY)//��ӡһ�����
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hout, baseX, baseY);
	cout << "������";// ����
	gotoxy(hout, baseX, baseY + 1);
	cout << "��";
	gotoxy(hout, baseX + 4, baseY + 1);
	cout << "��";
	gotoxy(hout, baseX, baseY + 2);
	cout << "������";
}

int printConsoleAllFrame(Sudoku(*sudoku)[N],int *leap)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	signIsErr(sudoku, leap);
	for (int i = 0; i < N; i++)
	{
		gotoxy(hout, 6 * i + 3, 1);
		cout << (char)('a' + i);
		gotoxy(hout, 1, i * 3 + 3);
		cout << i + 1;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			setPrintColor(sudoku, i, j);
			printConsoleOneFrame(j * 6 + 2, i * 3 + 2);
			gotoxy(hout, 6 * j +4, i * 3 + 3);
			cout <<sudoku[i][j].value<<" ";
			sudoku[i][j].isErr = 0;
		}
		cout << endl;
	}
	cout << endl;
	setcolor(hout, COLOR_BLACK, COLOR_WHITE);
	return *leap;
}


int allocateEmptyPoints(Place points[81], Sudoku(*sudoku)[N],int rowStore[][N],int colStore[][N],int blockStore[][3][N])
{
	int num = 0;
	for(int i=0;i<N;i++)
		for (int j = 0; j < N; j++)
		{
			if (sudoku[i][j].value == 0)
			{
				points[num].x = j;
				points[num++].y = i;
			}
			else
				rowStore[i][sudoku[i][j].value] = colStore[j][sudoku[i][j].value] = blockStore[i/3][j/3][sudoku[i][j].value] = 1;

		}
	return num - 1;
}
void DFS(int n,Place points[81], Sudoku(*sudoku)[N],int *flag, int rowStore[][N], int colStore[][N], int blockStore[][3][N],int *paceNum)
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (*flag)
		return;

	if (n == -1)
	{
		*flag = 1;
		return;
	}

	(*paceNum)++;
	gotoxy(hout, 0, 30);
	cout << (*paceNum);
	
	for (int i = 1; i < 10 && !(*flag);i++)
	{
		int x = points[n].x;
		int y = points[n].y;
		if (!rowStore[y][i] && !colStore[x][i] && !blockStore[y / 3][x / 3][i])
		{
			rowStore[y][i] = colStore[x][i] = blockStore[y/ 3][x / 3][i] = true;
			sudoku[y][x].value = i;
			showSearchAction(x, y, sudoku);
			DFS(n - 1,points,sudoku,flag,rowStore,colStore,blockStore,paceNum);
			rowStore[y][i] = colStore[x][i] = blockStore[y / 3][x / 3][i] = false;
			sudoku[y][x].value = 0;
		}
	}
}

void showSearchAction(int x, int y, Sudoku(*sudoku)[N])
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	setcolor(hout, COLOR_HGREEN, COLOR_HWHITE);
	printConsoleOneFrame(x * 6 + 2, y * 3 + 2);
	gotoxy(hout, 6 * x + 4, y * 3 + 3);
	cout << sudoku[y][x].value << " ";
	Sleep(50);
	setcolor(hout, COLOR_BLACK, COLOR_HYELLOW);
	printConsoleOneFrame(x * 6 + 2, y * 3 + 2);
	gotoxy(hout, 6 * x + 4, y * 3 + 3);
	cout << sudoku[y][x].value << " ";
	Sleep(50);
}