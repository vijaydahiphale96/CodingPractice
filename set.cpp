#include<iostream>
#include<vector>
#include<string>
#include<set>
using namespace std;

int main() {
    set<int> s1 = {1,2,3,4,4,5, 1000};
    s1.erase(2);
    s1.erase(s1.begin());
    auto it = s1.begin();
    it = it++;
    s1.erase(s1.begin(), s1.begin()++); // ERROR
    s1.erase(s1.begin(), s1.find(5)); // ERROR
    for(auto num:s1) {
        cout<<num<<" ";
    }
    cout<<endl;
    set<int, greater<int>> s2 = {1,2,3,4,4,5};
    s2.insert(10);
    s2.insert({10, 30, 40});
    s2.insert(s1.begin(), s1.end());
    for(auto num:s2) {
        cout<<num<<" ";
    }

    cout<<endl;
    set<vector<int>, greater<vector<int> > > s3 = {{1,2,3,4,4,5}, {55,3,244}, {0,3,2}};
    for(auto num:s3) {
        for(int index=0; index<num.size();index++) {
            cout<<num[index]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    return 0;
}