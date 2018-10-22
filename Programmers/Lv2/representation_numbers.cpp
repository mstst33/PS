#include <string>
#include <vector>

using namespace std;

int solution(int n) {
	int answer = 1; // 자기 자신 포함
	int half = n / 2; // 31 = 15 + 16 -> 반 자르면 그 다음 수가 같거나 넘는다

	for (int i = 1; i <= half; ++i)
	{
		for (int j = 1; j <= half; ++j)
		{
			// n = i + (i + 1) ... (i + (j - 1))
			// n = (j * i) + ((j - 1) * j) / 2
			int tmp = (j * i) + j * (j - 1) / 2;

			if (tmp == n)
			{
				++answer;
				break;
			}
			else if (tmp > n) break;
		}
	}

	return answer;
}

int main()
{
	int n = 16;
	printf("%d: %d\n", n, solution(n));
	return 0;
}
