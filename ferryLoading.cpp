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
    int leftLength; // int number to store filled size of left line
    int rightLength; // int number to store filled size of right line
    int prevIndexI; // index of previous row of dp matrix to get reference about previous state
    int prevIndexJ; // index of previous column of dp matrix to get reference about previous state
    string place; // left/right position

    Ferry(int left, int right, int i, int j, const string& p) { // Constructor
        leftLength = left;
        rightLength = right;
        prevIndexI = i;
        prevIndexJ = j;
        place = p;
    }
};

/**
 * function to Traceback the dp matrix to show car position left/right in the line
 * Till this point we already have created the dp matrix and we and index of last row in the matrix (allocated car size) where we have added the car length last time.
 * So, now, we will traceback from the last dp row to the upward to show car positions.
*/
void showData(int allocatedCars, vector<int>& carLengths, vector<vector<Ferry> >& dp) {
    int carsAllocated = allocatedCars;
    cout<<"Cars Allocated Count: "<<carsAllocated<<endl; // show max allocated car count
    map<int, string> carsData; // map to store the car index and its position in the line (left/right) (ordered map is needed to have 1st coming car on beginning position)
    int prevIndexJ = 0; // since 0th position will have one valid combination
    int prevIndexI = carsAllocated; // last I index will the max number of cars allocated.
    while(carsAllocated>0) { // traceback the positions till we reach to 1st row of dp matrix
        carsData.insert(make_pair(carsAllocated, dp[prevIndexI][prevIndexJ].place)); // insert into set, the car index and its position in the line
        carsAllocated--; // decrease the dp row index
        int tempPrevIndexI = prevIndexI;
        prevIndexI = dp[prevIndexI][prevIndexJ].prevIndexI; // update the previous I index referencing
        prevIndexJ = dp[tempPrevIndexI][prevIndexJ].prevIndexJ; // update the previous J index referencing
    }
    // Show car index and its position
    for(int i = 1; i<=carsData.size(); i++) {
        cout<<"Car number: "<< i << "   Car Length: " << carLengths[i-1] << "   Place: " << carsData[i]<<endl;
    }
}

void maxCarsAllocation(int n, vector<int>& carLengths, int ferryLength) {
    vector<vector<Ferry> > dp(n+1); // declared the size of vector based on no of cars + 1 (considering the 0 position)
    Ferry obj1(0, 0, -1, -1, "");
    dp[0].push_back(obj1); // initialize the zero, zero position of the matrix
    for (int i = 1; i <= n; i++) { // iterate from 1st car till last car
        int carLength = carLengths[i - 1]; // car length starts from 0th index so, get the car length for each iteration
        int inner = dp[i-1].size(); // decided the iteration length of inner loop based on the size of (i-1)th row of th matrix
        int count = 0; // variable to count the addition of atleast one of the car length 
        unordered_set<std::pair<int, int>, PairHash, PairEqual> calculatedMatrixPoints; // set of pair to store only unique combinations of the ferry line additions
        for (int j = 0; j < inner; j++) { // iterate based on size of previous row of the matrix, to generate its different combination.
            int leftLineSize = dp[i-1][j].leftLength; // get filled length of left line from previous row
            int rightLineSize = dp[i-1][j].rightLength; // get filled length of right line from previous row

            if(carLength <= (ferryLength - leftLineSize)) { // add car length in left line only if the there is enough space remaining in left line
                pair<int, int> myPair(leftLineSize + carLength, rightLineSize);
                if(calculatedMatrixPoints.find(myPair) == calculatedMatrixPoints.end()) { // push this pair only if this pair is not there in the current row of dp matrix
                    calculatedMatrixPoints.insert(myPair); // insert this pair in set (as this pair is not present in the current row set)
                    Ferry obj2(leftLineSize + carLength, rightLineSize, i-1, j, "left"); // generate matrix cell value
                    dp[i].push_back(obj2); // push current combination into dp matrix
                    count++; // increment counter if there is addition of any car length in the current row
                }
            }

            if(carLength <= (ferryLength - rightLineSize)) { // add car length in right line only if the there is enough space remaining in right line
                pair<int, int> myPair(leftLineSize, rightLineSize + carLength);
                if(calculatedMatrixPoints.find(myPair) == calculatedMatrixPoints.end()) { // push this pair only if this pair is not there in the current row of dp matrix
                    calculatedMatrixPoints.insert(myPair); // insert this pair in set (as this pair is not present in the current row set)
                    Ferry obj2(leftLineSize, rightLineSize + carLength, i-1, j, "right"); // generate matrix cell value
                    dp[i].push_back(obj2); // push current combination into dp matrix
                    count++; // increment counter if there is addition of any car length in the current row
                }
            }
        }
        if(count == 0) { // this will be true only if there it is not possible to add any more car length in the current row of dp matrix. So, problem is completed and show the result
            showData(i-1, carLengths, dp); // show solution of the problem
            return ;
        }
    }
    // if it is coming to this point, that means all car lengths are added to dp matrix and last vector 0th index will have one of the valid combination
    showData(n, carLengths, dp); // generate data to show based on generated dp matrix

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
