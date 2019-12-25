// prog_1.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>

int DFS_1(int* board, bool* went,int index,int n,int* max,int* chain);
int DFS_2(int* board, bool* went, int index, int n, int* max, int* chain);
int main()
{
	clock_t start, end;
	double cpu_time_used;
	start = clock();

    std::cout << "計算圍棋棋串子數\n";

	//盤面中，０＝無子、１＝黑子、２＝白子
	//開啟輸入檔案
	std::ifstream fobj;
	fobj.open("goinput.txt");
	int count=0,upper=16;
	int buf;
	int *bufv = (int*)malloc(upper * sizeof(int));
	if (bufv == NULL) {
		std::cout << "failed";
		return -1;
	}
	while (fobj >> buf)
	{
		if (count >= upper)
		{
			int oldupper = upper;
			upper = pow(sqrt(count) + 1,2);
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
	int *board=NULL;
	board = (int *)malloc(sizeof(int) * count);
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
	//輸出至螢幕確認盤面
	std::cout << "盤面:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int check = *(board + n * i + j);
			std::cout << check << " ";
		}
		std::cout << "\n";
	}
	fobj.close();

	std::cout << count << "\n";
	//went_white、went_black紀錄棋子是否有訪問過
	bool* went_white = (bool*)malloc(count * sizeof(bool));
	bool* went_black = (bool*)malloc(count * sizeof(bool));
	//initial
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			*(went_black + n * i + j) = false; 
			*(went_white + n * i + j) = false;
			//bool check = *(went_black + n * i + j);
			//std::cout << check << " ";
		}
		//std::cout << "\n";
	}

	//遍歷整個棋盤做DFS
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//index目前所在位置、check黑或白
			int index = n * i + j;
			int check = *(board + index);
			//std::cout << check << " ";
			if (check != 0 && check < 3)
			{
				//對找到的未探訪的黑子做DFS
				if (check == 1)
				{
					if (!*(went_black + index))
					{
						*(went_black + index) = true;
						//chain紀錄那些位址連在一起
						int* chain = (int*)malloc(50*sizeof(int));
						//initial chain
						for (int i = 0; i < 50; i++)
						{
							*(chain + i) = -1;
						}
						//max[1]計算連接長度
						int max[1] = { 0 };
						DFS_1(board, went_black, index, n,max,chain);
						//更新盤面
						for (int i = 0; i < max[0]; i++)
						{
							*(board + *(chain + i)) = max[0];
						}
						free(chain);
					}
				}
				//對找到的未探訪的白子做DFS
				if (check == 2)
				{
					if (!*(went_white + index))
					{
						*(went_white + index) = true;
						//chain紀錄那些位址連在一起
						int* chain = (int*)malloc(50 * sizeof(int));
						//initail chain
						for (int i = 0; i < 50; i++)
						{
							*(chain + i) = -1;
						}
						//max[1]計算連接長度
						int max[1] = { 0 };
						DFS_2(board, went_white, index, n,max,chain);
						//更新盤面
						for (int i = 0; i < max[0]; i++)
						{
							*(board + *(chain + i)) = max[0];
						}
						free(chain);
					}
				}
			}
		}
	}
	std::cout << "\n";
	/*
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			bool check = *(went_black + n * i + j);
			std::cout << check << " ";
		}
		std::cout << "\n";
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			bool check = *(went_white + n * i + j);
			std::cout << check << " ";
		}
		std::cout << "\n";
	}
	*/
	
	//output
	std::ofstream output;
	output.open("gooutput_Q.txt");
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
	free(went_black);
	free(went_white);
	free(board);
	
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time = %f\n", cpu_time_used);

	return 0;

	
	
}
//DFS for black
int DFS_1(int* board, bool* went,int index,int n,int* max,int* chain)
{
	*(chain + *max) = index;
	*max = *max+1;

	if ((index - n) >= 0)
	{
		if (!(*(went + index - n)) && *(board + index - n) == 1)
		{
			*(went + index - n) = true;
			DFS_1(board, went, index - n, n,max,chain);
		}
	}
	if ((index + 1) < n*n)
	{
		if (!(*(went + index + 1)) && *(board + index + 1) == 1)
		{
			*(went + index + 1) = true;
			DFS_1(board, went, index + 1, n,max,chain);
		}
	}
	if ((index + n) < n * n)
	{
		if (!(*(went + index + n)) && *(board + index + n) == 1)
		{
			*(went + index + n) = true;
			DFS_1(board, went, index + n, n,max,chain);
		}
	}
	if ((index - 1) >= 0)
	{
		if (!(*(went + index - 1)) && *(board + index - 1) == 1)
		{
			*(went + index - 1) = true;
			DFS_1(board, went, index - 1, n,max,chain);
		}
	}
	return 0;
}
//DFS for white
int DFS_2(int* board, bool* went, int index, int n, int* max, int* chain)
{
	*(chain + *max) = index;
	*max = *max + 1;

	if ((index - n) >= 0)
	{
		if (!(*(went + index - n)) && *(board + index - n) == 2)
		{
			*(went + index - n) = true;
			DFS_2(board, went, index - n, n,max,chain);
		}
	}
	if ((index + 1) < n * n)
	{
		if (!(*(went + index + 1)) && *(board + index + 1) == 2)
		{
			*(went + index + 1) = true;
			DFS_2(board, went, index + 1, n,max,chain);
		}
	}
	if ((index + n) < n * n)
	{
		if (!(*(went + index + n)) && *(board + index + n) == 2)
		{
			*(went + index + n) = true;
			DFS_2(board, went, index + n, n,max,chain);
		}
	}
	if ((index - 1) >= 0)
	{
		if (!(*(went + index - 1)) && *(board + index - 1) == 2)
		{
			*(went + index - 1) = true;
			DFS_2(board, went, index - 1, n,max,chain);
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
