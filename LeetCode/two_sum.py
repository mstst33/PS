class Solution:
#     # Brute force, O(n^2), O(1)
#     def twoSum(self, nums: List[int], target: int) -> List[int]:
#         len_nums = len(nums)
#         for i in range(len_nums):
#             for j in range(i + 1, len_nums):
#                 if nums[i] + nums[j] == target:
#                     return [i, j]
#         raise Exception('No two sum solution')

    # O(n), O(n)
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        nums_hash = dict()
        for i, n in enumerate(nums):
            complement = target - n
            if complement in nums_hash:
                return [nums_hash[complement], i]
            nums_hash[n] = i
        raise Exception('No two sum solution')