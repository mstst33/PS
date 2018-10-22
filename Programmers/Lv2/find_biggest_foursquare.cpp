#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int solution(vector<vector<int>> board)
{
	int answer = 0;
	int tmp = 0;
	int lenY = board.size();
	int lenX = board[0].size();

	if (lenY < 2 || lenX < 2)
	{
		for (int i = 0; i < lenY; ++i)
		{
			for (int j = 0; j < lenX; ++j)
			{
				if (board[i][j] == 1) return 1;
			}
		}
	}
	else
	{
		// 왼쪽과 위쪽에 대하여 구하기 힌트를 얻어서 구하기 때문에 시작점이 0이 아닌 1이다
		for (int i = 1; i < lenY; ++i)
		{
			for (int j = 1; j < lenX; ++j)
			{
				if (board[i][j] == 1)
				{
					// 1 1
					// 1 2
					// 현재 위치를 포함하여 왼쪽 상단, 왼쪽 위 상단, 위 상단 모두 0이 아니면 정사각형이 된다
					tmp = min(board[i - 1][j], board[i][j - 1]);
					board[i][j] = min(tmp, board[i - 1][j - 1]) + 1;

					// 최대값 저장
					if (board[i][j] > answer) answer = board[i][j];
				}
			}
		}
	}

	return (answer * answer);
}
