#include <iostream>
#include <cmath>
using namespace std;

int solution(int n) {
	int answer = 0;
	for (int i = 1; i <= sqrt(n); ++i)
	{
		if (n % i == 0)
		{
			answer += i;
			// n = a * b 에서 a != b 이어야 한다
			if (i != n / i) answer += n / i;
		}
	}

	return answer;
}
