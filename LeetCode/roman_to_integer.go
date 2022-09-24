// Constrains
// 1 <= s.length <= 15
// s contains only the characters ('I', 'V', 'X', 'L', 'C', 'D', 'M')
// It is guaranteed that s is a valid roman numeral in the range [1, 3999]

// O(n), O(n)
func romanToInt(s string) int {
    symbols := map[rune]int{
        'I': 1,
        'V': 5,
        'X': 10,
        'L': 50,
        'C': 100,
        'D': 500,
        'M': 1000,
    }
    
    var result int
    b4_val := -1
    for _, sv := range s {
        val := symbols[sv]
        if b4_val > 0 && b4_val < val {
            result -= 2 * b4_val
        }
        b4_val = val
        result += val
    }
    return result
}
