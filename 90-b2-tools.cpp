/*1551445 童佳燕 计算机科学与技术1班*/
#include"90-b2.h"
#include"cmd_console_tools.h"

void printMenu()
{
	cout << "--------------------------------------" << endl;
	cout << "1.字符界面游戏（带回退功能）" << endl;
	cout << "2.图形界面功能（带回退功能）" << endl;
	cout << "3.图形界面自动求解（显示过程并带延时）" << endl;
	cout << "0.退出" << endl;
	cout << "--------------------------------------" << endl;
	cout << "【请选择0-3】";
}

/*输入choice并判断输入是否正确，控制光标的位置，提供良好的使用享受*/
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
			if (sudoku[i][j].value == 0)//对于原件初始值进行标记，不可操作
				sudoku[i][j].fixed = 0;
			else
				sudoku[i][j].fixed =1;
			sudoku[i][j].isErr = 0;
		}
}
/*读入相应目录下所有txt文件*/
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

/*error，默认为sudoku.txt尚未解决*/
int getValueFromFile(Sudoku(*value)[N],char fileName[30],int isFromKey)
{
	ifstream fin;
	//char fileName[30];
	if (isFromKey == 0)
	{
		cout << "请输入数独题目文件名（回车表示默认sudoku.txt）:";
		//if (_getch() == '\r')
			//strcat_s(fileName ,"sudoku.txt");
		//else
		cin >> fileName;
	}
	fin.open(fileName, ios::in);
	if (!fin.is_open())
	{
		cout << "打开文件失败" << endl;
		return -1;
	}
	Sudoku(*p)[N] = value;
	for (; p - value < N; p++)
		for (int i = 0; i < N; i++)
			fin >> (*p + i)->value;
	return 0;
}

int isRight(Sudoku(*value)[N])//判断初始文件是否合法（0-9）
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
	cout << "读入的数据为" << endl;
	for (int i = 0; i < N; i++)
	{
		if (i % 3 == 0)
			cout << "-+";
		cout << "-" << (char)('a' + i);
	}
	cout << "-";
	cout << endl;

	/*对判断函数的调用进行剪枝，减少重复判断和调用，原步骤键下方注释，虽然程序简单，但是运行过程冗余*/
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
			setPrintColor(sudoku, i, j);//根据固有值，零，非零，冲突等情况设置输出的颜色
			cout << sudoku[i][j].value << " ";
			sudoku[i][j].isErr = 0;//复原
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

void signIsErr(Sudoku(*sudoku)[N],int *leap)//遍历每个元素，判断是否与其他元素有冲突，这里涉及一系列上下屏蔽的问题，实验报告仔细阐述
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

void setPrintColor(Sudoku(*sudoku)[N], int i, int j)//设置输出颜色
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	if (sudoku[i][j].isErr == 1)//不同的颜色输出
	{
		if (sudoku[i][j].fixed == 1)
			setcolor(hout, COLOR_HWHITE, COLOR_HBLUE);//固定不动的用蓝色前景色显示
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

int isRowDifferent(Sudoku(*value)[N], int row)//横向判断是否有重复的,如果有重复的，返回 -1,同时给该行的所有值的isErr赋值为1
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

int isColDifferent(Sudoku(*value)[N], int col)//纵向判断是否有重复的
{
	for (int i = 0; i < N; i++)
		if (value[i][col].value == 0)
			continue;
		else
			for (int k = i + 1; k < N; k++)
				if (value[i][col].value == value[k][col].value)
				{
					for (int m = 0; m < N; m++)
						value[m][col].isErr = 1;//作为标记，供输出使用
					return -1;
				}
	return 0;
}

int isBlockDifferent(Sudoku(*value)[N], int row, int col)//3*3方块中判断是否有重复的
{
	int Y = row / 3 * 3, X = col / 3 * 3;//寻找每个3*3小宫格的“头”
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (value[Y + i][X + j].value == 0)//对于0是不需要检查相同的
				continue;
			else
				for (int k = i; k < 3; k++)
					for (int h = 0; h < 3; h++)
						if (value[Y + k][X + h].value == value[Y + i][X + j].value && (k!=i||h!=j))//错误之处：int h=j  遍历不充分；缺少k!=i||h!=j  导致找到必定找到相同的值，也就是自身
						{
							for (int m = 0; m < 3; m++)
								for (int n = 0; n < 3; n++)
									value[Y + m][X + n].isErr = 1;//对于被检查是否冲突过程中被查中的，进行标记，便于输出
							return -1;
						}
	return 0;
}


void getCheckInput(Sudoku (*sudoku)[N], char index[4])//检查输入是否正确，同时给index赋值
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	int x, y;
	cout << "请按行\\列\\值的方式输入(例如：5c6=第五行第c列为6)，输入bk表示回退一次";
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
			cout << "输入错误，请重新输入" << endl;
			continue;
		}
		if (index[0] == 'b'&&index[1] == 'k')
			break;
		gotoxy(hout, 0, y + 1);
		cout << "                  ";
		gotoxy(hout, 0, y + 1);
		if (index[0] > '9' || index[0] < '1')
		{
			cout << "第" << index[0] << "行不是【0-9】，请重新输入";
			continue;
		}
		if (index[1] > 'i' || index[1] < 'a')
		{
			cout << "第" << index[1] << "列不是【a-i】，请重新输入";
			continue;
		}
		if (index[2] > '9' || index[2] < '1')
		{
			cout << "填入的值" << index[2] << "不是【1-9】,请重新输入";
			continue;
		}
		if (sudoku[index[0] - '1'][index[1] - 'a'].fixed ==1)//初始非零值是不可以更改的
		{
			cout << "该位置不允许被操作" << endl;
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
		int isBack = 0;//作为判断是否回退的标记
		if (p != NULL)
			q = p;
		p = (struct Step *)malloc(sizeof(Step));
		if (p == NULL)//同下
			return ;
		if (q == NULL)//加入第一步不能退回之后，各种p是nullptr，用以避免
		{
			head = p;
			head->before = NULL;
		}
		else
		{
			q->next = p;
			p->before = q;//建立双向链表
		}
		gotoxy(hout, x, y + 1);
		getCheckInput(sudoku, p->index);//记录操作
		if (!strcmp(p->index, "bk"))
		{
			/*加入对第一步就回退的判断，调试：只退到第二步，事实上第一步都是可以被退掉的*/
			if (p == head)
			{
				cout << "这是第一步，不能回退" << endl;
				free(head);
				p = NULL;
				continue;
			}

			free(p);//释放新申请的空间
			q->next = NULL;
			p = q;//为了适应q前p后，对p,q进行移位
			q = q->before;
			isBack = 1;
		}
		int row = (p->index)[0] - '1';
		int col = (p->index)[1] - 'a';
		if (isBack)
		{
			sudoku[row][col].value = p->preValue;
			free(p);//如果回退,p指向的空间记录的操作是不需要的，因此可以释放
			if (q != NULL)
				q->next = NULL;
			p = q;//careful，不然就回不去了
		}
		else
		{
			p->preValue = sudoku[row][col].value;//记录更改之前的值
			sudoku[row][col].value = ((p->index)[2] - '0');
			p->next = NULL;
		}
		if (isConsole == 1)
		{
			if (printConsoleAllFrame(sudoku, &isInvalid))
				cout << "数据有冲突";
		}
		else
			if (printCharBegin(sudoku, &isInvalid))
				cout << "数据有冲突";
		isGameOver(sudoku, isInvalid);
	}
	release(head);
}

int isGameOver(Sudoku(*sudoku)[N], int leap)//判断是否游戏结束
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

void release(Step *head)//释放动态空间
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
	cout << "数独样本文件";
	gotoxy(hout, baseX, baseY + 1);
	cout << "┏━━━━━━━━━━┓";
	for (int i = 0; i < height; i++)
	{
		gotoxy(hout, baseX, baseY + 2 + i);
		cout << "┃ ";
		if (i == 0)
			setcolor(hout, COLOR_WHITE, COLOR_BLACK);
		cout << file[i];
		setcolor(hout, COLOR_BLACK, COLOR_WHITE);
		gotoxy(hout, baseX + weight-1, baseY + 2 + i);
		cout << "┃";
	}
	gotoxy(hout, baseX, baseY +height+1);
	cout << "┗━━━━━━━━━━┛\n";
	
}

int chooseAction(char(*file)[30],int numOfFile)//改进的时候，尝试拆分
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
		if (key1 == 224 && key2 == 80)//向下键
		{
			if (fileOrder == numOfFile - 1)
				continue;//以指向最后一个文件，该次输入不生效
			fileOrder++;
			if (fileOrder == top + 8)//所指向的file
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
				cout << "                  ";//清空该位置之前打印的信息
				gotoxy(hout, baseX + 3, baseY + 9);
				setcolor(hout, COLOR_WHITE, COLOR_BLACK);//设置颜色
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

void printConsoleOneFrame(int baseX, int baseY)//打印一个框架
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hout, baseX, baseY);
	cout << "┏━┓";// ┗┛
	gotoxy(hout, baseX, baseY + 1);
	cout << "┃";
	gotoxy(hout, baseX + 4, baseY + 1);
	cout << "┃";
	gotoxy(hout, baseX, baseY + 2);
	cout << "┗━┛";
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