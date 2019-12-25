// prog_2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

int DFS_1(int* board, bool* went, int index, int n, int* max, int* chain, bool* air,int* temp);
int DFS_2(int* board, bool* went, int index, int n, int* max, int* chain, bool* air,int* temp);
int main()
{
	std::cout << "計算圍棋棋串子數\n";

	clock_t start, end;
	double cpu_time_used;
	start = clock();

	//盤面中，０＝無子、１＝黑子、２＝白子
	//開啟輸入檔案
	std::ifstream fobj;
	fobj.open("goinput.txt");
	int count = 0, upper = 16;
	int buf;
	int* bufv = (int*)malloc(upper * sizeof(int));
	//檢查記憶體是否配置成功
	if (bufv == NULL) {
		std::cout << "failed";
		return -1;
	}
	while (fobj >> buf)
	{
		if (count >= upper)
		{
			int oldupper = upper;
			upper = pow(sqrt(count) + 1, 2);
			int* bigger = (int*)calloc(upper, sizeof(int));
			for (int i = 0; i < oldupper; i++)
			{
				*(bigger + i) = *(bufv + i);
			}
			free(bufv);
			bufv = bigger;

		}

		*(bufv + count) = buf;
		//int check = *(bufv + count);
		//std::cout << check << " ";
		count++;

	}
	int n = sqrt(count);
	int* board = NULL;
	board = (int*)malloc(sizeof(int) * count);
	//檢查記憶體是否配置成功
	if (board == NULL) {
		std::cout << "failed";
		return -1;
	}
	//取得盤面
	for (int i = 0; i < count; i++)
	{
		*(board + i) = *(bufv + i);
	}
	free(bufv);
	fobj.close();

	//紀錄棋盤上的黑白子位置是否有訪問過
	bool* went = (bool*)malloc(count * sizeof(bool));
	//init went
	for (int i = 0; i < count; i++)
	{
		*(went + i) = false;
	}
	//
	for (int i = 0; i < count; i++) {
		if (*(board + i) == 1 && !*(went + i))
		{
			*(went + i) = true;
			//max計算棋串氣數
			int max[1] = { 0 };
			//temp、chain記錄棋串位址
			int temp[1] = { 0 };
			int* chain = (int*)calloc(50, sizeof(int));
			//went_air暫存棋盤上的氣位置是否重複計算
			bool* went_air = (bool*)malloc(count * sizeof(bool));
			for (int i = 0; i < count; i++) {
				*(went_air + i) = false;
			}
			DFS_1(board, went, i, n, max, chain,went_air,temp);
			//更新盤面
			for (int i = 0; i < temp[0]; i++)
			{
				*(board + *(chain + i)) = max[0];
			}
			free(chain);
			free(went_air);
		}else if (*(board + i) == 2 && !*(went + i))
		{
			*(went + i) = true;
			//max計算棋串氣數
			int max[1] = { 0 };
			//temp、chain記錄棋串位址
			int temp[1] = { 0 };
			int* chain = (int*)calloc(50, sizeof(int));
			//went_air暫存棋盤上的氣位置是否重複計算
			bool* went_air = (bool*)malloc(count * sizeof(bool));
			for (int i = 0; i < count; i++) {
				*(went_air + i) = false;
			}
			DFS_2(board, went, i, n, max, chain, went_air,temp);
			//更新盤面
			for (int i = 0; i < temp[0]; i++)
			{
				*(board + *(chain + i)) = max[0];
			}
			free(chain);
			free(went_air);
		}
	}
	//output
	std::ofstream output;
	output.open("gooutput_R.txt");
	std::cout << "計算結果:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int check = *(board + n * i + j);
			std::cout << check << " ";
			output << check << "\t";

		}
		std::cout << "\n";
		output << "\n";
	}
	output.close();
	free(went);
	free(board);

	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time = %f\n", cpu_time_used);

	return 0;
}
int DFS_1(int* board, bool* went, int index, int n, int* max, int* chain,bool* air,int* temp)
{
	*(chain + *temp) = index;
	*temp = *temp + 1;

	if ((index - n) >= 0)
	{
		if (!*(air + index - n) && *(board + index - n) == 0)
		{
			*(air + index - n) = true;
			*max = *max + 1;
		}
		if (!(*(went + index - n)) && *(board + index - n) == 1)
		{
			*(went + index - n) = true;
			DFS_1(board, went, index - n, n, max, chain,air,temp);
		}
	}
	if ((index + 1) < n * n)
	{
		if (!*(air + index + 1) && *(board + index + 1) == 0)
		{
			*(air + index + 1) = true;
			*max = *max + 1;
		}
		if (!(*(went + index + 1)) && *(board + index + 1) == 1)
		{
			*(went + index + 1) = true;
			DFS_1(board, went, index + 1, n, max, chain,air,temp);
		}
	}
	if ((index + n) < n * n)
	{
		if (!*(air + index + n) && *(board + index + n) == 0)
		{
			*(air + index + n) = true;
			*max = *max + 1;
		}
		if (!(*(went + index + n)) && *(board + index + n) == 1)
		{
			*(went + index + n) = true;
			DFS_1(board, went, index + n, n, max, chain,air,temp);
		}
	}
	if ((index - 1) >= 0)
	{
		if (!*(air + index - 1) && *(board + index - 1) == 0)
		{
			*(air + index - 1) = true;
			*max = *max + 1;
		}
		if (!(*(went + index - 1)) && *(board + index - 1) == 1)
		{
			*(went + index - 1) = true;
			DFS_1(board, went, index - 1, n, max, chain,air,temp);
		}
	}
	return 0;
}
int DFS_2(int* board, bool* went, int index, int n, int* max, int* chain, bool* air, int* temp)
{
	*(chain + *temp) = index;
	*temp = *temp + 1;

	if ((index - n) >= 0)
	{
		if (!*(air + index - n) && *(board + index - n) == 0)
		{
			*(air + index - n) = true;
			*max = *max + 1;
		}
		if (!(*(went + index - n)) && *(board + index - n) == 2)
		{
			*(went + index - n) = true;
			DFS_2(board, went, index - n, n, max, chain, air, temp);
		}
	}
	if ((index + 1) < n * n)
	{
		if (!*(air + index + 1) && *(board + index + 1) == 0)
		{
			*(air + index + 1) = true;
			*max = *max + 1;
		}
		if (!(*(went + index + 1)) && *(board + index + 1) == 2)
		{
			*(went + index + 1) = true;
			DFS_2(board, went, index + 1, n, max, chain, air, temp);
		}
	}
	if ((index + n) < n * n)
	{
		if (!*(air + index + n) && *(board + index + n) == 0)
		{
			*(air + index + n) = true;
			*max = *max + 1;
		}
		if (!(*(went + index + n)) && *(board + index + n) == 2)
		{
			*(went + index + n) = true;
			DFS_2(board, went, index + n, n, max, chain, air, temp);
		}
	}
	if ((index - 1) >= 0)
	{
		if (!*(air + index - 1) && *(board + index - 1) == 0)
		{
			*(air + index - 1) = true;
			*max = *max + 1;
		}
		if (!(*(went + index - 1)) && *(board + index - 1) == 2)
		{
			*(went + index - 1) = true;
			DFS_2(board, went, index - 1, n, max, chain, air, temp);
		}
	}
	return 0;
}
// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
