#include <string>
#include <vector>

using namespace std;

/*
void getLaser(vector<int>& st)
{
    // stack에 있는 쇠막대 모두 laser개수 하나를 증가시킨다
    for(int i = 0; i < (int) st.size(); ++i) ++st[i];
}

// Case 1: stack을 이용하여 해결, BigO(n)
int solution(string arrangement)
{
    int answer = 0;
    vector<int> st;

    // stack에는 괄호 쌍이 보장되므로 괄호 모양은 저장하지 않고 laser 개수만 저장한다
    for(int i = 0; i < (int) arrangement.length(); ++i)
    {
        // 닫는 괄호가 나올 때 stack top을 봤을 때
        // laser 개수가 없으면 laser인 것이고 laser 개수가 있으면 쇠막대기이다.
        if(arrangement[i] == ')')
        {
            int top = st.back();
            st.pop_back();
            if(top > 0) answer += top + 1;
            else getLaser(st);
        }
        else st.push_back(0);
    }

    return answer;
}
*/

// Case 2: stack 이용하지 않고 해결, BigO(n)
int solution(string arrangement)
{
    int answer = 0;
    int open_bracket = 0;

    // stack에는 괄호 쌍이 보장되므로 괄호 모양은 저장하지 않는다
    for(int i = 0; i < (int) arrangement.length(); ++i)
    {
        // 닫는 괄호가 나올 때,
        // 전 괄호가 여는 괄호면 stack에 있는 쇠막대기 개수가 전체 증가한다
        // 전 괄호가 닫는 괄호면 나머지 하나의 쇠막대기를 늘려주고 종료한다
        if(arrangement[i] == ')')
        {
            --open_bracket;
            if(arrangement[i - 1] == '(') answer += open_bracket;
            else ++answer;
        }
        else ++open_bracket;
    }

    return answer;
}

int main()
{
    string arrangement = "()(((()())(())()))(())";
    printf("%d\n", solution(arrangement));
    return 0;
}
