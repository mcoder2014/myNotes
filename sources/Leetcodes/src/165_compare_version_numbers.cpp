#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int compareVersion(string version1, string version2) {
        while(version1.size() > 0 && version2.size() > 0) {
            int majorVersion1 = getMajorVersion(version1);
            int majorVersion2 = getMajorVersion(version2);
            if(majorVersion1 > majorVersion2) {
                return 1;
            } else if (majorVersion1 < majorVersion2) {
                return -1;
            }
        }

        if(version1.size() >0) {
            int diff = 0;
            while(version1.size() >0) {
                diff += getMajorVersion(version1);
            }
            if(diff > 0)
                return 1;
            return 0;
        } if(version2.size() >0) {
            int diff = 0;
            while(version2.size() >0) {
                diff += getMajorVersion(version2);
            }
            if(diff > 0)
                return 1;
            return 0;
        } else {
            return 0;
        }

    }

    // 获得主版本号，
    int getMajorVersion(string& version){
        int i = 0;
        int majorVersion = 0;
        while(i < version.size() && version[i] != '.') {
            majorVersion = majorVersion *10 + (version[i]-'0');
            i++;
        }

        // cout << "majorVersion " << majorVersion << "left " << version << endl;
        // 判断是遇到小数点了还是到头了
        if(i >= version.size()) {
            version = "";
        } else if(version[i] == '.') {
            version = version.substr(i+1);
            // cout << version << endl;
        }

        return majorVersion;
    }
};

int main()
{
    Solution slu;
    auto f = [&](string v1, string v2){
        int result = slu.compareVersion(v1, v2);
        cout << v1 << " " << result << " " << v2 << endl;
    };

    f("1.01", "1.001");
    f("7.5.6", "7.5.4");
    

    return 0;
}