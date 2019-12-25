// prog_3.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <random>
#include <functional>
#include <stdio.h>
#include <fstream>

int main()
{
	std::cout << "產生盤面\n";
	std::random_device rd;
	std::default_random_engine gen = std::default_random_engine(rd());
	std::uniform_int_distribution<int> disa(0, 1);
	std::uniform_int_distribution<int> disb(0, 2);
	auto rand01 = std::bind(disa, gen);
	auto rand02 = std::bind(disb, gen);
	printf("輸入N值以產生N*N盤面:");
	int n = 4;
	if (scanf_s("%d", &n) == NULL) {
		return -1;
	}

	int b = n * n;
	int* board = (int*)calloc(b, sizeof(int));
	int temp = 0;
	for (int j = 0; j < 2; j++) {
		for (int i = 0; i < b; i++) {

			if (i > n + 1 && i < b - 2 - n) {
				//若i不在棋盤邊
				if (*(board + i - n) == 1 && *(board + i + n) == 1 && *(board + i + 1) == 1 && *(board + i - 1) == 1) {
					//若被黑子圍住則只可產生空或黑子
					temp = rand01();
				}
				else if (*(board + i - n) == 2 && *(board + i + n) == 2 && *(board + i + 1) == 2 && *(board + i - 1) == 2) {
					//若被白子圍住則只可產生空或白子
					temp = rand01();
					if (temp == 1) { temp = 2; }
				}
				else {
					temp = rand02();
				}
			}
			else if (i == 0) {
				//i在最左上角
				if (*(board + i + n) == 1 && *(board + i + 1) == 1) {
					//若被黑子圍住則只可產生空或黑子
					temp = rand01();
				}
				else if (*(board + i + n) == 2 && *(board + i + 1) == 2) {
					//若被白子圍住則只可產生空或白子
					temp = rand01();
					if (temp == 1) { temp = 2; }
				}
				else {
					temp = rand02();
				}
			}
			else if (i == n - 1) {
				//i在最右上角
				if (*(board + i + n) == 1 && *(board + i - 1) == 1) {
					//若被黑子圍住則只可產生空或黑子
					temp = rand01();
				}
				else if (*(board + i + n) == 2 && *(board + i - 1) == 2) {
					//若被白子圍住則只可產生空或白子
					temp = rand01();
					if (temp == 1) { temp = 2; }
				}
				else {
					temp = rand02();
				}
			}
			else if (i == n * (n - 1)) {
				//i在最左下角
				if (*(board + i - n) == 1 && *(board + i + 1) == 1) {
					//若被黑子圍住則只可產生空或黑子
					temp = rand01();
				}
				else if (*(board + i - n) == 2 && *(board + i + 1) == 2) {
					//若被白子圍住則只可產生空或白子
					temp = rand01();
					if (temp == 1) { temp = 2; }
				}
				else {
					temp = rand02();
				}
			}
			else if (i == b - 1) {
				//i在最右下角
				if (*(board + i - n) == 1 && *(board + i - 1) == 1) {
					//若被黑子圍住則只可產生空或黑子
					temp = rand01();
				}
				else if (*(board + i - n) == 2 && *(board + i - 1) == 2) {
					//若被白子圍住則只可產生空或白子
					temp = rand01();
					if (temp == 1) { temp = 2; }
				}
				else {
					temp = rand02();
				}
			}
			else if (i % n == 0) {
				//i在最左側
				if (*(board + i - n) == 1 && *(board + i + n) == 1 && *(board + i + 1) == 1) {
					//若被黑子圍住則只可產生空或黑子
					temp = rand01();
				}
				else if (*(board + i - n) == 2 && *(board + i + n) == 2 && *(board + i + 1) == 2) {
					//若被白子圍住則只可產生空或白子
					temp = rand01();
					if (temp == 1) { temp = 2; }
				}
				else {
					temp = rand02();
				}
			}
			else if (i % n == n - 1) {
				//i在最右側
				if (*(board + i - n) == 1 && *(board + i + n) == 1 && *(board + i - 1) == 1) {
					//若被黑子圍住則只可產生空或黑子
					temp = rand01();
				}
				else if (*(board + i - n) == 2 && *(board + i + n) == 2 && *(board + i - 1) == 2) {
					//若被白子圍住則只可產生空或白子
					temp = rand01();
					if (temp == 1) { temp = 2; }
				}
				else {
					temp = rand02();
				}
			}
			else if (i > n* (n - 1) && i < b - 2) {
				//i在最下側
				if (*(board + i - n) == 1 && *(board + i + 1) == 1 && *(board + i - 1) == 1) {
					//若被黑子圍住則只可產生空或黑子
					temp = rand01();
				}
				else if (*(board + i - n) == 2 && *(board + i + 1) == 2 && *(board + i - 1) == 2) {
					//若被白子圍住則只可產生空或白子
					temp = rand01();
					if (temp == 1) { temp = 2; }
				}
				else {
					temp = rand02();
				}
			}
			else if (i > 0 && i < n - 1) {
				//i在上邊
				if (*(board + i + n) == 1 && *(board + i + 1) == 1 && *(board + i - 1) == 1) {
					//若被黑子圍住則只可產生空或黑子
					temp = rand01();
				}
				else if (*(board + i + n) == 2 && *(board + i + 1) == 2 && *(board + i - 1) == 2) {
					//若被白子圍住則只可產生空或白子
					temp = rand01();
					if (temp == 1) { temp = 2; }
				}
				else {
					temp = rand02();
				}
			}
			*(board + i) = temp;
		}
	}
	//output
	std::ofstream output;
	output.open("goinput.txt");
	std::cout << "盤面:\n";
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int check = *(board + n * i + j);
			std::cout << check << " ";
			output << check << " ";

		}
		std::cout << "\n";
		output << "\n";
	}
	output.close();
	free(board);
	
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
