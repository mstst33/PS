class Solution:
#     # O(log(x)), O(log(x))
#     def isPalindrome(self, x: int) -> bool:
#         if x < 0: return False
#         if x < 10: return True
#         if x % 10 == 0: return False
        
#         x_list = []
#         while x > 0:
#             val = x % 10
#             x //= 10
#             x_list.append(val)
        
#         mid = -1
#         len_x = len(x_list)
#         stack = list()
#         mid = len_x // 2
#         for i, n in enumerate(x_list):
#             if i < mid: stack.append(n)
#             else:
#                 if i == mid and len_x % 2 != 0: continue
#                 else:
#                     if stack[-1] == n: stack.pop()
#         return len(stack) == 0

    # O(log(x)), O(1)
    def isPalindrome(self, x: int) -> bool:
        if x < 0: return False
        if x < 10: return True
        if x % 10 == 0: return False
        
        tmp_x = x
        reverse = 0
        while tmp_x > 0:
            reverse = reverse * 10 + tmp_x % 10
            tmp_x //= 10
        return x == reverse
        