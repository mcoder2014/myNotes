#include <iostream>
#include <unistd.h>
#include <sys/utsname.h>

using namespace std;

int main()
{
    union Un
    {
        short s;
        char c[sizeof(short)];
    };

    Un un;
    un.s = 0x0102;

    struct utsname sysName;
    int ret = uname(&sysName);

    cout << "System name: " << sysName.sysname << "\n"
         << "System domain name: " << sysName.domainname << "\n"
         << "System version: " << sysName.version << "\n"
         << "System release: " << sysName.release << "\n"
         << "System machine: " << sysName.machine << endl;

    if(sizeof(short) == 2)
    {
        if(un.c[0]==1 && un.c[1]==2) {
            cout << "Big-endian\n";
        } else if(un.c[0]==2 && un.c[1]==1) {
            cout << "Little-endian\n";
        } else {
            cout << "Unkown-endian\n";
        }
    } else {
        cout << "Short length is " << sizeof(short) << endl;
    }

    return 0;
}