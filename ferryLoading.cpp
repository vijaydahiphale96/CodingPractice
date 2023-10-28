#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <algorithm>

using namespace std;

// Custom hash function for std::pair<int, int>
struct PairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ h2;
    }
};

// Custom equality comparison for std::pair<int, int>
struct PairEqual {
    template <class T1, class T2>
    bool operator () (const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) const {
        return p1.first == p2.first && p1.second == p2.second;
    }
};

int maxCarsAllocation(int n, vector<int>& carLengths, int ferryLength) {
    // vector<vector<vector<int>> > dp(n + 1, vector<vector<int>>(ferryLength+1, vector<int>(2, 0)));
    unordered_set<std::pair<int, int>, PairHash, PairEqual> calculatedMatrixPoints;
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
                pair<int, int> myPair(leftLineSize + carLength, rightLineSize);
                if(calculatedMatrixPoints.find(myPair) == calculatedMatrixPoints.end()) {
                    calculatedMatrixPoints.insert(myPair);
                    vector<int> v2 = {leftLineSize + carLength, rightLineSize};
                    dp[i].push_back(v2);
                }
            }

            if(carLength <= (ferryLength - rightLineSize)) {
                pair<int, int> myPair(leftLineSize, rightLineSize + carLength);
                if(calculatedMatrixPoints.find(myPair) == calculatedMatrixPoints.end()) {
                    calculatedMatrixPoints.insert(myPair);
                    vector<int> v2 = {leftLineSize, rightLineSize + carLength};
                    dp[i].push_back(v2);
                }
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
