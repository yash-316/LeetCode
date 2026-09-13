class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        int ans = 0;
        for(int r = -n+1; r<n; r++){
            for(int c = -n+1; c<n; c++){
                int overlap = 0;
                for(int i = 0; i<n; i++){
                    for(int j = 0; j<n; j++){
                        int x = r+i;
                        int y = c+j;
                        if((x>=0 && x<n) && (y>=0 && y<n)){
                            if(img1[i][j] == 1 && img2[x][y]==1){
                                overlap++;
                            }
                        }
                    }
                }
                ans=max(ans,overlap);
            }
        }
        return ans;
    }
};