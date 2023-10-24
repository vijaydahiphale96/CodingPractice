class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) {
            return false;
        }
        long long int rev = 0;
        long long int tempNum = x;
        while(tempNum) {
            int digit = tempNum%10;
            rev = rev*10 + digit;
            tempNum = tempNum/10;
        }
        if(rev == x) {
            return true;
        }
        return false;
    }
};