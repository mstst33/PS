#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    unordered_map<string, int> um;
    
    if(clothes.size() <= 1) return clothes.size();
    
    // 옷 종류별로 개수를 헤아린다
    for(auto vsc : clothes)
    {
        auto it = um.find(vsc[1]);
        if(it == um.end()) um.emplace(vsc[1], 1);
        else ++it->second;
    }
    
    // 옷 종류별로 +1 (옷이 없는 경우) 하여 곱한다
    // 옷을 하나도 안 입는 경우가 생기므로 정답을 반환하기 전에 -1을 해준다
    for(auto c : um) answer *= (c.second + 1);
    
    return --answer;
}
