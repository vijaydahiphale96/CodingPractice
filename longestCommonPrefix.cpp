class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string targetString = strs[0];
        for(int i=0; i<strs.size(); i++) {
            string temp = "";
            for(int j=0; j<targetString.size(); j++) {
                if(targetString[j] == strs[i][j]) {
                    temp += strs[i][j];
                } else {
                    targetString = temp;
                    break;
                }
            }
        }
        return targetString;
    }
};