#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
// 각 숫자를 string 형으로 만든 다음 처음부터 비교해 나가는 방법 (실패)
bool numbersCompare(const string& a, const string& b)
{
    if(a == b) return false;

    int alen = a.length();
    int blen = b.length();
    int longlen = (alen > blen ? alen : blen);
    int pos = 0;
    char tmpa = 0;
    char tmpb = 0;
    
    while(pos < longlen)
    {
        if(pos < alen) tmpa = a[pos];
        if(pos < blen) tmpb = b[pos];

        if(tmpa > tmpb) return true;
        else if(tmpa < tmpb) return false;

        ++pos;
    }

    return false;
}
*/

// 확실한 비교를 하려면 결국 a + b, b + a 를 하여 비교하는 방법이 최고인거 같다
bool numbersCompare(const string& a, const string& b)
{
    if(a == b) return false;

    string ab = a + b;
    string ba = b + a;

    if(ab > ba) return true;
    else return false;
}

string solution(vector<int> numbers) {
    string answer = "";
    int zero_count = 0;
    vector<string> s_numbers;
    
    for(auto i : numbers)
    {
        if(i == 0) ++zero_count;
        s_numbers.push_back(to_string(i));
    }

    // 0, 0, 0 이 들어 있는 경우는 000 이 아니라 0 이다
    if(zero_count == numbers.size()) return "0";

    // 만들어 둔 비교 함수에 따라 정렬한다
    sort(s_numbers.begin(), s_numbers.end(), numbersCompare);

    for(auto s : s_numbers) answer.append(s);

    return answer;
}
