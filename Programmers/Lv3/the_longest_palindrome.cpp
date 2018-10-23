#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 2500
// 문자열 구간 i...j가 팰린드롬이면 table[i][j]는 true, 아니면 false  
bool table[MAX_LEN][MAX_LEN] = { false };

int solution(char* s) {
    int i, j, k;
    int n = strlen(s); 
    int maxLength = 1; 
    
    // 1문자 문자열은 무조건 길이 1인 팰린드롬
    for (i = 0; i < n; i++) table[i][i] = true;

    // 길이 2인 부분 문자열 검사   
    for (i = 0; i < n - 1; i++)
    {
        if (s[i] == s[i + 1])
        {
            table[i][i + 1] = true;
            maxLength = 2;
        }
    }

    // 길이 3 이상인 부분 문자열 검사. k는 부분 문자열 길이
    for (k = 3; k <= n; k++) 
    {
        for (i = 0; i <= (n - k); i++) 
        {
            // 부분 문자열의 시작 i와 길이 k를 이용하여 끝 지점 j 구함
            j = i + k - 1;
            // 부분 문자열의 i부터 j까지 팰린드롬인지 검사 
            if (table[i + 1][j - 1] && s[i] == s[j]) 
            {
                table[i][j] = true;
                if (k > maxLength) maxLength = k;
            }
        }
    }

    return maxLength;
}
