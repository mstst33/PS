class Solution:
    # O(S), O(1), S is the sum of all characters in all strings
    def longestCommonPrefix(self, strs: List[str]) -> str:
        len_strs = len(strs)
        if len_strs == 0: return ''
        if len_strs == 1: return strs[0]
        
        ref = strs[0]
        for i in range(1, len_strs):
            min_len = min(len(ref), len(strs[i]))
            
            tmps = ''
            for j in range(min_len):
                if ref[j] == strs[i][j]: tmps += ref[j]
                else: break
                        
            ref = tmps
            if ref == '': return ''
        
        return ref
        