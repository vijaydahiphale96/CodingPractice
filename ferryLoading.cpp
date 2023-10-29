/*
Author - Vijay Dattu Dahiphale
B-Number - B01036763

How To Execute the Code - 
Use following commands to compile and run the code - 

g++ ferryLoading.cpp
./a.out ferry04.txt

*/


#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
#include <map>
#include <utility>
#include <algorithm>
#include<fstream>
#include <sstream>

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
    cout<<"Cars Allocated Count: "<<carsAllocated<<endl;
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
        cout<<"Car number: "<< i << "   Car Length: " << carLengths[i-1] << "   Place: " << carsData[i]<<endl;
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



int main(int argc, char *argv[]) {

    if (argc < 2) { //Show error if the user has not provided input file
        cout<<"please provide correct arguments \n";
        exit(1);
    }

    int noOfCars; // Number of cars
    int ferryLength; // Length of left and right lines
    vector<int> carLengths(noOfCars); // Length of each car


    // **********************    Read File Data Starts   **********************
    ifstream file;
    string line;
    string splittedString;
    string fileName = argv[1];

    file.open(fileName); // Open file
    if (!file) { // Show error if file does not exit OR error while opening the file
        cout<<"Could not open "<<fileName;
        exit(1);
    }

    try {
        getline(file, line); // Get single line data into "line" string variable
        istringstream split(line);
        getline(split, splittedString, ' '); // splits the 1st line of input file with space (' '), and add 1st part into splittedString string
        noOfCars = stoi(splittedString); // set noOfCars
        getline(split, splittedString, ' '); // splits the 1st line of input file with space (' '), and add 2nd part into splittedString string
        ferryLength = stoi(splittedString); // set ferryLength
        while (getline(file, line)) {    // Get new one line data into "line" string variable
            carLengths.push_back(stoi(line)); // add length of each car into carLengths vector
        }
    }
    catch(const std::exception& e) {
        // Catch error while reading file
        cout<<"Error while reading input file! Please check input file\n";
        exit(1);
    }
    file.close();
    // **********************    Read File Data Ends   **********************

    maxCarsAllocation(noOfCars, carLengths, ferryLength);

    return 0;
}
