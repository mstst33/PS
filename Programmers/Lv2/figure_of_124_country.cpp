#include <string>
#include <vector>

using namespace std;

/*
string solution(int n) {
	string answer = "";
	int tmp = 0;

	while (n > 0)
	{
		tmp = n % 3;
		if (tmp == 0)
		{
			tmp = 4;
			n = (n / 3) - 1;
		}
		else n /= 3;

		answer.insert(0, to_string(tmp));
	}

	return answer;
}
*/

// 새로운 방법
string solution(int n) {
	string answer = "";
	int tmp = 0;

	while (n > 0)
	{
		tmp = n % 3;
		if (tmp == 0) n = (n / 3) - 1;
		else n /= 3;

		answer = "412"[tmp] + answer;
	}

	return answer;
}
