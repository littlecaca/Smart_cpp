#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <vector>
#include <functional>

using std::string;
using std::cout;
using std::endl;
using std::list;
using std::for_each;
using std::unique;
using std::sort;
using std::partition;
using std::vector;
using namespace std::placeholders;
using std::bind;


void elimDups(vector<string> &ls) {
    // sort the elimDups
    sort(ls.begin(), ls.end());

    // remove the concequtive duplicates
    auto edge = unique(ls.begin(), ls.end());

    // remove
    ls.erase(edge, ls.end());
}

inline string make_plural(const string &s) {
    return s + "s";
}

inline bool isBigger(const string &s, string::size_type sz) {
    return s.size() >= sz;
}

int main(int argc, char const *argv[])
{
    /* code */
    // remove the duplicates
    vector<string> ls{"you", "are", "really", "a", "genius", "!"};
    elimDups(ls);
    string::size_type sz = 5;

    decltype(ls.cbegin()) edge = partition(ls.begin(), ls.end(), bind(isBigger, _1, sz));
    
    int count = edge - ls.begin();
    
    cout << count << " " << make_plural("word") << " of length "
         << sz << " or longer" << endl;
        
    for_each(ls.cbegin(), edge, [](const string &s) { cout << s << endl; });
    return 0;
}
