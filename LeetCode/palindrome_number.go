// // O(log(x)), O(log(x))
// func isPalindrome(x int) bool {
//     if x < 0 {
//         return false
//     } else if x < 10 {
//         return true
//     } else {
//         var xList []int
//         num := x
//         for num > 0 {
//             xList = append(xList, num % 10)
//             num /= 10
//         }
        
//         len_xlist := len(xList)
//         half_len_xlist := len_xlist / 2
//         for i := 0; i < half_len_xlist; i++ {
//             if xList[i] != xList[len_xlist - i - 1] {
//                 return false
//             }
//         }
        
//         return true
//     }
// }

// O(log(x)), O(1)
func isPalindrome(x int) bool {
    if x < 0 {
        return false
    } else if x < 10 {
        return true
    } else {
        tmp_x := x
        reverse := 0
        for tmp_x > 0 {
            reverse = reverse * 10 + tmp_x % 10
            tmp_x /= 10
        }
        
        return x == reverse
    }
}