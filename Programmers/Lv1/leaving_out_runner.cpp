#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

// 각 배열을 정렬 후, 비교하는 방법 BigO(nlog n)
/*
string solution(vector<string> participant, vector<string> completion) {
    sort(participant.begin(), participant.end());
    sort(completion.begin(), completion.end());

    for(int i = 0; i < completion.size(); ++i)
    {
        if(participant[i] != completion[i]) return participant[i];
    }

    return participant[participant.size() - 1];
}
*/

// 완주 선수 명단을 hashmap에 <이름, 동일 인물 수> 로 넣고
// 달리기 선수 명단 이름으로 hashmap을 탐색하여
// 이름이 없으면 해당 선수가 완주 못 한 것이며
// 동일 인물 수가 0 미만이 되어도 완주 못한 것이다 BigO(n)
string solution(vector<string> participant, vector<string> completion) {
    unordered_map<string, int> hash_completion;

    for(auto s : completion)
    {
        if(hash_completion.find(s) == hash_completion.end()) hash_completion.emplace(s, 1);
        else ++hash_completion[s];
    }

    for(auto s : participant)
    {
        if(hash_completion.find(s) == hash_completion.end()) return s;
        else
        {
            if(--hash_completion[s] < 0) return s;
        }
    }

    return "";
}
