class Solution {
public:
    struct State {
        long long score;
        vector<int> ids;
    };

    // Return true if a is better than b
    bool better(const State& a, const State& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return lexicographical_compare(
            a.ids.begin(), a.ids.end(),
            b.ids.begin(), b.ids.end()
        );
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<long long, 4>> v;

        for (int i = 0; i < n; i++) {
            v.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        // Sort by right endpoint
        sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
            if (a[1] != b[1])
                return a[1] < b[1];

            return a[0] < b[0];
        });

        // ends[i] = ending point of interval i
        vector<long long> ends(n);

        for (int i = 0; i < n; i++)
            ends[i] = v[i][1];

        /*
            prev[i] = index of the last interval whose
            right endpoint is strictly smaller than v[i].left.

            We need:
                right < left

            because intervals sharing a boundary overlap.
        */
        vector<int> prev(n);

        for (int i = 0; i < n; i++) {
            int pos = lower_bound(
                ends.begin(),
                ends.end(),
                v[i][0]
            ) - ends.begin();

            prev[i] = pos - 1;
        }

        /*
            dp[k][i]:
            best answer using at most k intervals
            among first i intervals.

            i ranges from 0 to n.
        */
        vector<vector<State>> dp(
            5,
            vector<State>(n + 1)
        );

        // Base cases
        for (int k = 0; k <= 4; k++) {
            dp[k][0] = {0, {}};
        }

        for (int i = 1; i <= n; i++) {

            int idx = i - 1;

            for (int k = 1; k <= 4; k++) {

                // Option 1: don't take current interval
                State skip = dp[k][i - 1];

                // Option 2: take current interval
                State take;

                take.score =
                    v[idx][2] +
                    dp[k - 1][prev[idx] + 1].score;

                take.ids =
                    dp[k - 1][prev[idx] + 1].ids;

                take.ids.push_back((int)v[idx][3]);

                // Keep indices sorted because the final answer
                // must be lexicographically compared.
                sort(take.ids.begin(), take.ids.end());

                dp[k][i] =
                    better(take, skip) ? take : skip;
            }
        }

        return dp[4][n].ids;
    }
};