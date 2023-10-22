#include<iostream>
#include<string>
using namespace std;

int main() {
    string s1 = "abcd";
    string s2 = "vijay", s3 = "aaaa";
    s1.insert(s1.begin(), 's');
    s1.insert(s1.begin(), 3, 's');
    s1.insert(s1.end()-1, s2.begin(), s2.end());
    s1.append(s3);
    cout<<s1;
}