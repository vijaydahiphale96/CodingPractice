#include<iostream>
#include<vector>
#include<string>
#include <numeric>
using namespace std;

void show(vector<int> &vect) {
    for(int i = 0; i< vect.size(); i++) {
        cout<<vect[i]<< " ";
    }
    cout<<endl;
}

int main() {
    vector<int> v1(5);

    vector<int> v2(5, 100);
    show(v2);

    vector<int> v3 = {1,2,3,4,5,6,3,2,1};
    vector<int> v4 {1,2,3,4,5,6,3,2,1};

    vector<int> v5(v4);
    show(v5);

    vector<int> v6(v4.begin(), v4.begin() + 5);

    show(v6);

    fill(v1.begin(), v1.end(), 10);
    show(v1);

    iota(v1.begin(), v1.end(), 1);
    show(v1);

    cout<<v1.front()<<endl;
    cout<<v1.back()<<endl;

    v1.insert(v1.begin(), 3, 5);
    show(v1);

}