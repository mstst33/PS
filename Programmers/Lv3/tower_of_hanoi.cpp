#include <string>
#include <vector>

using namespace std;

void recordTrace(vector<vector<int>>& v, int from, int to)
{
    vector<int> tmp;
    
    tmp.push_back(from);
    tmp.push_back(to);
    v.push_back(tmp);
}

void moveDisk(vector<vector<int>>& v, int n, int from, int to, int ex)
{
    if(n == 1) recordTrace(v, from, to);
    else
    {
        // 위에서부터 n - 1개를 1번에서 2번으로 옮긴다
        // 나머지 바닥에 있는 한 개를 1번에서 최종 3번으로 옮긴다
        // 2번으로 옮긴 n - 1 개를 2번에서 최종 3번으로 옮긴다
        moveDisk(v, n - 1, from, ex, to);
        recordTrace(v, from, to);
        moveDisk(v, n - 1, ex, to, from);
    }
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;
    
    moveDisk(answer, n, 1, 3, 2);
    
    return answer;
}

int main()
{
    int n = 3; // 최소로 옮기는 수는 2^n - 1

    vector<vector<int>> answer = solution(n);
    
    for(vector<int> v : answer)
    {
        printf("[");
        for(int i : v) printf(" %d ", i);
        printf("]\n");
    }
    
    return 0;
}
