#include <string>
#include <vector>

using namespace std;

/*
// 중복을 허용 하지 않는 경우
vector<int> solution(int n, int s) {
    vector<int> answer;
    
    if(n == 1) answer.push_back(s);
    else
    {
        // n 개의 자연수 최소 집합의 합보다 s는 작으면 -1
        int min_sum = (n * (n + 1)) / 2;
        if(min_sum > s) answer.push_back(-1);
        else 
        {
            // 합이 s이 되는 n개로 이루어진 집합 중에 곱이 최대가 되려면
            // 먼저 s에서 n 개의 최소 집합의 합을 빼준 값을 sn이라 하면
            // sn을 n으로 나눈 몫을 1, 2, 3 .. n 에 각각 더하고
            // sn를 n으로 나눈 나머지를 n .. 3, 2, 1 순서로 1씩 더해 주면 된다
            // ex) n = 2, s = 3, (1, 2)
            // ex) n = 2, s = 4, (1, 3)
            // ex) n = 2, s = 5, (2, 3)
            // ex) n = 2, s = 6, (2, 4)
            int sn = s - min_sum;
            int quota = sn / n;
            int remain = sn % n;
            int nremain = n - remain;
            
            for(int i = 1; i <= n; ++i)
            {
                if(i > nremain) answer.push_back(i + quota + 1);
                else answer.push_back(i + quota);
            }
        }
    }
    
    return answer;
}
*/

// 중복을 허용하는 경우
vector<int> solution(int n, int s) {
    vector<int> answer;
    
    if(n == 1) answer.push_back(s);
    else
    {
        if(n > s) answer.push_back(-1);
        else 
        {
            // 합이 s이 되는 n개로 이루어진 집합 중에 곱이 최대가 되려면
            // s를 n으로 나눈 몫으로 집합을 구성하고
            // s를 n으로 나눈 나머지를 하나씩 뿌려서 더해주면 된다
            int quota = s / n;
            int remain = s % n;
            int nremain = n - remain;
            
            for(int i = 1; i <= n; ++i)
            {
                if(i > nremain) answer.push_back(quota + 1);
                else answer.push_back(quota);
            }
        }
    }
    
    return answer;
}

int main()
{
    int n = 100;
    int s = (n * (n + 1)) / 2 + 0;
    int repeat = 1;

    for(int i = 0; i < repeat; ++i)
    {
        vector<int> answer = solution(n, s + i);

        for(auto v : answer) printf("%d ", v);
        printf("\n");
    }

    return 0;
}
