// O(S), O(1), S is the sum of all characters in all strings
func longestCommonPrefix(strs []string) string {
    pickedStr := strs[0]
    lenPickedStr := len(pickedStr)
    for i := 1; i < len(strs); i++ {
        if lenPickedStr == 0 {
            break
        }
        
        str := strs[i]
        lenStr := len(str)
        if lenStr == 0 {
            return ""
        }
        
        
        for j := 0; j < lenStr && j < lenPickedStr; j++ {
            if str[j] != pickedStr[j] {
                pickedStr = str[:j]
                lenPickedStr = j
                break
            }
            
            if j + 1 == lenStr {
                pickedStr = str[:j + 1]
                lenPickedStr = j + 1
            }
        }
    }
    
    return pickedStr
}