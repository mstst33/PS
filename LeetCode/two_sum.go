// // Brute force O(n^2), O(1)
// func twoSum(nums []int, target int) []int {
//     ptr1 := 0
//     ptr2 := 1
//     nums_len := len(nums)
    
//     for ptr2 < nums_len {
//         if nums[ptr1] + nums[ptr2] == target {
//             break
//         }
        
//         if ptr2 + 1 == nums_len {
//             ptr1 += 1
//             ptr2 = ptr1
//         }
        
//         ptr2 += 1
//     }
    
//     return []int{ptr1, ptr2}
// }

// O(n), O(n)
func twoSum(nums []int, target int) []int {
    complement_map := make(map[int]int)
    for i, num := range nums {
        if j, exist := complement_map[num]; exist {
            return []int{i, j}
        } else {
            complement_map[target - num] = i
        }
    }
    
    return []int{}
}