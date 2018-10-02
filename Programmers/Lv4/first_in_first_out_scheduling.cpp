#include <string>
#include <vector>
#include <queue>

using namespace std;

/*
// Case1: Time을 증가시켜 가며 코어 전부를 검사, 대략 BigO(n * cores.size)
int solution(int n, vector<int> cores) {
    int size = cores.size();
    int time = 0;

    // n이 0이 될때까지 시간 흐름에 따라 코어를 돌면서 작업량을 할당해 나간다
    while(n > 0)
    {
        for(int i = 0; i < size; ++i)
        {
            if(((time % cores[i]) == 0) && (--n == 0)) return (i + 1);
        }
        ++time;
    }
    
    return time;
}
*/
/*
// Case2: 우선순위 큐를 이용 , 대략 BigO(n)
class coreWork
{
public:
    int num;
    int worktime;

    coreWork(int n, int w): num(n), worktime(w){};

    // 작업시간이 같다면 코어 순서를 비교하고 다르면 작업시간을 비교한다
    friend bool operator > (const coreWork &a, const coreWork &b)
    {
        if(a.worktime == b.worktime) return a.num > b.num;
        else return a.worktime > b.worktime;
    }

    friend bool operator < (const coreWork &a, const coreWork &b)
    {
        if(a.worktime == b.worktime) return a.num < b.num;
        else return a.worktime < b.worktime;
    }
};

template <typename T>
void print_pq(priority_queue<T, vector<T>, greater<T>> pq)
{
    while(!pq.empty())
    {
        T cw = pq.top();
        printf("%d ", cw.worktime);
        pq.pop();
    }
    printf("\n");
}

int solution(int n, vector<int> cores) {
    int size = cores.size();
    int time = 0;
    int answer = 0;
    priority_queue<coreWork, vector<coreWork>, greater<coreWork>> pq;

    if(n <= size) return n; // 코어 개수만큼 작업이 없으면 해당 코어에서 종료한다
    else n -= size; // 작업 시작부터 코어 개수만큼 작업을 할당한다

    // 우선순위 큐에 코어들을 넣는다
    for(int i = 0; i < size; ++i) pq.emplace(i, cores[i]);

    // 이미 시작했으므로 빨리 끝나는 작업부터 처리해 나간다
    for(int i = n; i > 0; --i)
    {
        printf("n[%d]: ", i);
        print_pq(pq);
        coreWork cw = pq.top();
        if(cw.worktime > time) time = cw.worktime; // 어짜피 우선순위 큐의 첫번째 아이템까지 시간을 흘려야 한다

        pq.pop(); // 첫번째 아이템을 뺀다
        pq.emplace(cw.num, (time + cores[cw.num])); // 그리고 뺀 첫 아이템의 작업시간 + 현재 시간을 더해 다시 큐에 넣는다

        if((i - 1) == 0) answer = cw.num + 1;
    }
    
    return answer;
}
*/

// Case3: Parametric Search를 이용, 대략 BigO(log n)
// 매개체인 작업 시간을 통해 최소 최대 범위에서 Binary Search하면서
// 작업시간과 연관된 현재 작업시점의 작업량을 구한다
// 그 작업량이 n과 같을 때 해당 코어를 반환한다
#define MIN_CORE_WORKTIME 10000
int solution(int n, vector<int> cores) {
    int size = cores.size();
    int mincore = MIN_CORE_WORKTIME + 1;
    int maxcore = 0;
    int mintime = 0;
    int maxtime = 0;
    int midtime = 0;

    // 작업 시작 시점부터 하나씩 작업이 할당되기 때문에 코어수 보다 작으면 바로 해당 코어를 반환한다
    if(n <= size) return n;

    // 시간당 작업량의 최소와 최대를 구한다
    for(int i  = 0; i < size; ++i)
    {
        if(mincore > cores[i]) mincore = cores[i];

        if(maxcore < cores[i]) maxcore = cores[i];
    }

    // 모든 코어가 동일한 최소, 최대 값을 가진다고 가정할 때 최대와 최소 걸리는 시간을 구한다
    mintime = (mincore * (n - size)) / size;
    maxtime = (maxcore * (n - size)) / size;

    printf("mincore[%d],maxcore[%d]\n", mincore, maxcore);

    while(mintime <= maxtime)
    {
        int corework = size; // 작업 시작부터 코어 개수 만큼 작업이 할당 된다
        int currentwork = 0;

        // 최소와 최대의 중간 시간을 구한다
        midtime = (mintime + maxtime) / 2;

        // 중간 시간을 현재 시점으로 해서 코어별로 작업량을 구한다
        for(int i : cores)
        {
            corework += (midtime / i); // 현재 시간을 시간당 작업량으로 나누면 현재 코어의 작업량이 된다
            if((midtime % i) == 0) ++currentwork; // 현재 막 작업을 할당 받은 코어의 개수를 구한다
        }

        printf("mint[%d],maxt[%d],midt[%d] | corework[%d],currentwork[%d]\n",mintime,maxtime,midtime,corework,currentwork);
        
        // n이 현재 시점(midtime)에서 코어들의 총 작업량보다 크다면 최소 시간(mintime)을 midtime 으로 끌어 올린다.
        // n <= (corework - currentwork) 경우는 반대쪽에 있으므로 최대 시간(maxtime)을 끌어 내린다 
        if(n > corework) mintime = midtime + 1;
        else if(n <= (corework - currentwork)) maxtime = midtime - 1;
        else
        {
            // corework - currentwork < n <= corework 사이에 있으면
            // 현재 막 작업을 할당 받은 코어 중에 n개가 되는 시점의 코어를 구할 수 있다
            // 참고: corework - currentwork <= n <= corework 라고 가정하면
            // n = corework - currentwork 일수도 있다는 뜻인데 실제 들어가면 아닐 수도 있다
            // 이유는 (midtime % cores[i]) == 0 이면 바로 tmpwork 가 하나 증가하기 때문에
            // n != corework - currentwork 가 아닐 수 있다
            int tmpwork = corework - currentwork;
            for(int i = 0; i < size; ++i)
            {
                if((midtime % cores[i]) == 0) ++tmpwork;

                if(tmpwork == n) return (i + 1);
            }
        }
    }
    
    return 0;
}
