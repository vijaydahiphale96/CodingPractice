#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility>
#include <algorithm>

using namespace std;

// Custom hash function for std::pair<int, int>
struct PairHash {
    template <class T1, class T2>
    size_t operator () (const pair<T1, T2>& p) const {
        size_t h1 = hash<T1>()(p.first);
        size_t h2 = hash<T2>()(p.second);
        return h1 ^ h2;
    }
};

// Custom equality comparison for std::pair<int, int>
struct PairEqual {
    template <class T1, class T2>
    bool operator () (const pair<T1, T2>& p1, const pair<T1, T2>& p2) const {
        bool areEqual = (p1.first == p2.first) && (p1.second == p2.second);
        return areEqual;
    }
};

int maxCarsAllocation(int n, vector<int>& carLengths, int ferryLength) {
    vector<vector<vector<int> > > dp(n+1);
    vector<int> v1;
    v1.push_back(0);
    v1.push_back(0);
    dp[0].push_back(v1);
    for (int i = 1; i <= n; i++) {
        int carLength = carLengths[i - 1];
        int inner = dp[i-1].size();
        int count = 0;
        unordered_set<std::pair<int, int>, PairHash, PairEqual> calculatedMatrixPoints;
        for (int j = 0; j < inner; j++) {
            int leftLineSize = dp[i-1][j][0];
            int rightLineSize = dp[i-1][j][1];

            if(carLength <= (ferryLength - leftLineSize)) {
                pair<int, int> myPair(leftLineSize + carLength, rightLineSize);
                if(calculatedMatrixPoints.find(myPair) == calculatedMatrixPoints.end()) {
                    calculatedMatrixPoints.insert(myPair);
                    vector<int> v2;
                    v2.push_back(leftLineSize + carLength);
                    v2.push_back(rightLineSize);
                    dp[i].push_back(v2);
                    count++;
                }
            }

            if(carLength <= (ferryLength - rightLineSize)) {
                pair<int, int> myPair(leftLineSize, rightLineSize + carLength);
                if(calculatedMatrixPoints.find(myPair) == calculatedMatrixPoints.end()) {
                    calculatedMatrixPoints.insert(myPair);
                    vector<int> v2;
                    v2.push_back(leftLineSize);
                    v2.push_back(rightLineSize + carLength);
                    dp[i].push_back(v2);
                    count++;
                }
            }
        }
        if(count == 0) {
            return i-1;
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
