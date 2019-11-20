#include <iostream>
#include <string>
#include <stack>
#include <deque>
#include <algorithm>
using namespace std;

class Solution {
public:
    string simplifyPath(string path)
    {
        stack<string> stk;
        string tmp;
        for(char ch:path)
        {
            if(ch == '/')
            {
                // check tmp;
                if(tmp.size() == 0)
                {
                    // check if this is root
                    if(stk.size() == 0)
                        stk.push(string("/"));
                }
                else if (tmp == ".")
                {
                    tmp.clear();
                }
                else if(tmp == "..")
                {
                    if(stk.size() >1)
                        stk.pop();
                    tmp.clear();

                }
                else
                {
                    tmp.push_back(ch);
                    stk.push(tmp);
                    tmp.clear();
                }
            }
            else
            {
                tmp.push_back(ch);
            }
        }


        // push back last floder
        if(tmp.size() > 0)
        {
            if (tmp == ".")
            {}
            else if(tmp == "..")
            {
                if(stk.size() >1)
                    stk.pop();
            }
            else
            {
                tmp.push_back('/');
                stk.push(tmp);
            }
        }

        // remove the last char '/'
        if(stk.size() >1)
            stk.top() = stk.top().substr(0, stk.top().size()-1);

        deque<string> deq;
        while(stk.size() > 0)
        {
            deq.push_front(stk.top());
            stk.pop();
        }
        string res;
        for(string s:deq)
        {
            res += s;
        }
        return res;
    }
};


int main()
{
    Solution solution;
    auto test = [&](string path)
    {
        string res = solution.simplifyPath(path);
        cout << "Origin:\t" << path
             << "\nAfter:\t" << res << "\n\n";
    };

    test("/home");
    test("/home/");
    test("/../");
    test("/home//foo/");
    test("/a/./b/../../c/");
    test("/a/../../b/../c//.//");
    test("/a//b////c/d//././/..");
    test("");
    test("/");
    test("home/..////fo//");
    test("/.././GVzvE/./xBjU///../..///././//////T/../../.././zu/q/e");
    test("zu/q/e");
    return 0;
}
