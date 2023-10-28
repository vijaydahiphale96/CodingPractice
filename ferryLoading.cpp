#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

// Custom hash function for pair<int, int>
struct PairHash {
    template <class T1, class T2>
    size_t operator () (const pair<T1, T2>& p) const {
        size_t h1 = hash<T1>()(p.first);
        size_t h2 = hash<T2>()(p.second);
        return h1 ^ h2;
    }
};

// Custom equality comparison for pair<int, int>
struct PairEqual {
    template <class T1, class T2>
    bool operator () (const pair<T1, T2>& p1, const pair<T1, T2>& p2) const {
        bool areEqual = (p1.first == p2.first) && (p1.second == p2.second);
        return areEqual;
    }
};

class Ferry {
  public:
    int leftLength;
    int rightLength;
    int prevIndexI;
    int prevIndexJ;
    string place;

    Ferry(int left, int right, int i, int j, const string& p) {
        leftLength = left;
        rightLength = right;
        prevIndexI = i;
        prevIndexJ = j;
        place = p;
    }
};

void showData(int allocatedCars, vector<int>& carLengths, vector<vector<Ferry> >& dp) {

    // for (int i = 0; i <= allocatedCars; ++i) {
    //     for (int j = 0; j < dp[i].size(); ++j) {
    //         cout<<"i="<<i<<" j="<<j<< " k=("<<dp[i][j].leftLength<<","<<dp[i][j].rightLength<<") Place= "<<dp[i][j].place<<" PrevInd= ("<<dp[i][j].prevIndexI<<","<<dp[i][j].prevIndexJ<<")"<<endl;
    //     }
    // }

    int carsAllocated = allocatedCars;
    cout<<"Cars Allocated Count:- "<<carsAllocated<<endl;
    map<int, string> carsData;
    int prevIndexJ = 0;
    int prevIndexI = carsAllocated;
    while(carsAllocated>0) {
        carsData.insert(make_pair(carsAllocated, dp[prevIndexI][prevIndexJ].place));
        carsAllocated--;
        int tempPrevIndexI = prevIndexI;
        prevIndexI = dp[prevIndexI][prevIndexJ].prevIndexI;
        prevIndexJ = dp[tempPrevIndexI][prevIndexJ].prevIndexJ;
    }

    for(int i = 1; i<=carsData.size(); i++) {
        cout<<"Car number:- "<< i << "   Car Length:- " << carLengths[i-1] << "   Place:- " << carsData[i]<<endl;
    }

}

void maxCarsAllocation(int n, vector<int>& carLengths, int ferryLength) {
    vector<vector<Ferry> > dp(n+1);
    Ferry obj1(0, 0, -1, -1, "");
    dp[0].push_back(obj1);
    for (int i = 1; i <= n; i++) {
        int carLength = carLengths[i - 1];
        int inner = dp[i-1].size();
        int count = 0;
        unordered_set<std::pair<int, int>, PairHash, PairEqual> calculatedMatrixPoints;
        for (int j = 0; j < inner; j++) {
            int leftLineSize = dp[i-1][j].leftLength;
            int rightLineSize = dp[i-1][j].rightLength;

            if(carLength <= (ferryLength - leftLineSize)) {
                pair<int, int> myPair(leftLineSize + carLength, rightLineSize);
                if(calculatedMatrixPoints.find(myPair) == calculatedMatrixPoints.end()) {
                    calculatedMatrixPoints.insert(myPair);
                    Ferry obj2(leftLineSize + carLength, rightLineSize, i-1, j, "left");
                    dp[i].push_back(obj2);
                    count++;
                }
            }

            if(carLength <= (ferryLength - rightLineSize)) {
                pair<int, int> myPair(leftLineSize, rightLineSize + carLength);
                if(calculatedMatrixPoints.find(myPair) == calculatedMatrixPoints.end()) {
                    calculatedMatrixPoints.insert(myPair);
                    Ferry obj2(leftLineSize, rightLineSize + carLength, i-1, j, "right");
                    dp[i].push_back(obj2);
                    count++;
                }
            }
        }
        if(count == 0) {
            showData(i-1, carLengths, dp);
            return ;
        }
    }

    showData(n, carLengths, dp);

    return ;
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

    maxCarsAllocation(n, carLengths, columnSize);

    return 0;
}
