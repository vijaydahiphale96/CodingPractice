#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxCarsAllocation(int n, vector<int>& carLengths, int ferryLength) {
    // vector<vector<vector<int>> > dp(n + 1, vector<vector<int>>(ferryLength+1, vector<int>(2, 0)));
    vector<vector<vector<int>>> dp(n+1);
    vector<int> v1 = {0,0};
    dp[0].push_back(v1);
    for (int i = 1; i <= n; i++) {
        int carLength = carLengths[i - 1];
        int inner = dp[i-1].size();
        for (int j = 0; j < inner; j++) {
            int leftLineSize = dp[i-1][j][0];
            int rightLineSize = dp[i-1][j][1];

            if(carLength <= (ferryLength - leftLineSize)) {
                vector<int> v2 = {leftLineSize + carLength, rightLineSize};
                dp[i].push_back(v2);
            }

            if(carLength <= (ferryLength - rightLineSize)) {
                vector<int> v2 = {leftLineSize, rightLineSize + carLength};
                dp[i].push_back(v2);
            }
            
            if(carLength > (ferryLength - leftLineSize) && carLength > (ferryLength - rightLineSize)) {
                return i-1;
            }
            // cout<<"i="<<i<<" j="<<j<< " k=("<<dp[i][j][0]<<","<<dp[i][j][1]<<")"<<endl;
            // cout<<"i="<<i<<" j="<<j<< " k=("<<dp[i][j+1][0]<<","<<dp[i][j+1][1]<<")"<<endl;
        }
    }

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < dp[i].size(); ++j) {
            cout<<"i="<<i<<" j="<<j<< " k=("<<dp[i][j][0]<<","<<dp[i][j][1]<<")"<<endl;
        }
    }
    return n;
}

int main() {
    int n; // Number of cars
    cin >> n;
    vector<int> carLengths(n);

    // Input car lengths
    for (int i = 0; i < n; i++) {
        cin >> carLengths[i];
    }

    int columnSize; // Length of both columns
    cin >> columnSize;

    int maxCars = maxCarsAllocation(n, carLengths, columnSize);
    cout << "Maximum number of cars that can be put into the columns: " << maxCars << endl;

    return 0;
}
