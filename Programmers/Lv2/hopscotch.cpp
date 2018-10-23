#include <iostream>
#include <vector>
using namespace std;

#define COL 4
#define MAX_N 100000

int dp[MAX_N][COL] = { 0 };
int solution(vector<vector<int>> land)
{
	int answer = 0;
	int N = land.size();

	for (int i = 0; i < COL; ++i) dp[0][i] = land[0][i];

	for (int i = 1; i < N; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			for (int k = 0; k < COL; ++k)
			{
				if (j != k) dp[i][j] = max(dp[i][j], land[i][j] + dp[i - 1][k]);
			}
		}
	}

	for (int i = 0; i < COL; ++i) answer = max(answer, dp[N - 1][i]);

	return answer;
}
