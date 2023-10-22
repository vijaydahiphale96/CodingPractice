#include <iostream>
#include <map>

using namespace std;

class Abc {
    private:
        string fname;
        string lname;
        int rollNum;

    public:
    Abc() {
        fname = "abc";
        lname = "dddd";
        rollNum = 12334;
    }

    void show() {
        cout<<fname<< " " << lname << " " << rollNum;
    }
};

int main()
{
// Create a map of strings to integers
map<string, int> map1;
map1["one"] = 1;
map1["two"] = 2;
map1["three"] = 3;

map<string, int>::iterator it = map1.begin();
// it = it + 5;
while (it != map1.end())
{
	cout << "Key: " << it->first << ", Value: " << it->second <<endl;
	++it;
}

cout << "Key: " << map1["four"]<<endl;

Abc obj1;

map<string, Abc> m2;

m2["1111"] = obj1;

m2["1111"].show();

return 0;
}
