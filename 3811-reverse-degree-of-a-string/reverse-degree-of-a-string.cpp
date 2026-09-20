class Solution {
public:
    int reverseDegree(string s) {
        int sum = 0;
        for(int i=0;i<s.length();i++){
            char c = s[i];

            int rev = 26 -(c - 'a');
            int pos = i+1;

            sum += rev * pos;
        }
        return sum;
    }
};