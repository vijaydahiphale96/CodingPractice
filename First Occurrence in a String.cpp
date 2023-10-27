class Solution {
public:
    int strStr(string haystack, string needle) {
        int matchIndex = -1;
        if(needle.size() > haystack.size()) {
            return matchIndex;
        }
        if(needle == "" && haystack == "") {
            return matchIndex;
        }
        for(int i=0; i<haystack.size(); i++) {
            int k = i;
            matchIndex = i;
            int subI = 0;
            while(subI < needle.size()) {
                if(needle[subI] != haystack[k]) {
                    break;
                }
                k++;
                subI++;
            }
            if(subI == needle.size()) {
                return matchIndex;
            }
        }
        return -1;
    }
};