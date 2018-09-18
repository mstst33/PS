#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 하나하나 대조하여 구하는 방법 BigO(n^2)
bool solution(vector<string> phoneBook) {
    int size = phoneBook.size();
    if(size <= 1) return true;
    
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size; ++j)
        {
            if(i != j)
            {
                int len = 0;
                if(phoneBook[i].length() > phoneBook[j].length()) len = phoneBook[j].length();
                else len = phoneBook[i].length();
                
                bool isSame = true;
                for(int k = 0; k < len; ++k)
                {
                    if(phoneBook[i][k] != phoneBook[j][k])
                    {
                        isSame = false;
                        break;
                    }
                }
                
                if(isSame) return false;
            }
        }
    }
    
    return true;
}

// 정렬할 경우 접두어가 같으려면 이웃해 있을 수 밖에 없다 BigO(nlog n)
bool solution(vector<string> phoneBook) {
    int size = phoneBook.size();
    if(size <= 1) return true;
    
    sort(phoneBook.begin(), phoneBook.end());
    
    for(int i = 0; i < (size - 1); ++i)
    {
        string is = phoneBook[i];
        string js = phoneBook[i + 1];
        int len = 0;
        bool isSame = true;
        
        if(is.length() > js.length()) len = js.length();
        else len = is.length();

        for(int k = 0; k < len; ++k)
        {
            if(is[k] != js[k])
            {
                isSame = false;
                break;
            }
        }

        if(isSame) return false;
    }
    
    return true;
}
