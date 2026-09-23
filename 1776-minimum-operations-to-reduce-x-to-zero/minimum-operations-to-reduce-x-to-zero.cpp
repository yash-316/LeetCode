class Solution {
public:
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        int total = accumulate(nums.begin(),nums.end(),0);
        int target = total - x;

        if(target<0){
            return -1;
        }
        if(target==0){
            return n;
        }

        int l = 0;
        int s = 0;
        int lon = -1;

        for(int r = 0; r<n; r++){
            s += nums[r];
            while(l<=r && s>target){
                s -= nums[l++];
            }
            if(s==target){
                lon = max(lon,r-l+1);
            }
        }
        return lon == -1 ? -1 : n - lon;

    }
};