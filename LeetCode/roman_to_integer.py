# Constrains
# 1 <= s.length <= 15
# s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M')
# It is guaranteed that s is a valid roman numeral in the range [1, 3999]
class Solution:
    def __init__(self):
        self.symbol_map = dict()
        self.symbol_map['I'] = 1
        self.symbol_map['V'] = 5
        self.symbol_map['X'] = 10
        self.symbol_map['L'] = 50
        self.symbol_map['C'] = 100
        self.symbol_map['D'] = 500
        self.symbol_map['M'] = 1000
    
    # O(s), O(1)
    def romanToInt(self, s: str) -> int:
        b4 = ''
        answer = 0
        for c in s:
            minus = 0
            if c == 'V' or c == 'X':
                if b4 == 'I':
                    minus = self.symbol_map[b4]
            elif c == 'L' or c == 'C':
                if b4 == 'X':
                    minus = self.symbol_map[b4]
            elif c == 'D' or c == 'M':
                if b4 == 'C':
                    minus = self.symbol_map[b4]

            answer += self.symbol_map[c] - (minus * 2)
            b4 = c
        return answer