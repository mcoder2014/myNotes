#include <iostream>

using namespace std;

bool equal(double d1, double d2) {
    double tmp = d1 - d2;
    return tmp < 0.0000001
        && tmp > - 0.0000001;
}

double powerWithUnsigned(double base, uint exponent) {
    double result = 1.0;
    for(uint i = 0; i <= exponent; i++) {
        result *= base;
    }
    return result;
}

double power(double base, int exponent) {
    if(equal(base, 0)) {
        return 0;
    }

    uint absExponent = static_cast<uint>(exponent);

    if(exponent < 0) {
        absExponent = static_cast<uint>(-exponent);
        base = 1.0/base;
    }

    return powerWithUnsigned(base, absExponent);
}

int main()
{
    double base;
    int exponent;

    while(true) {
        cin >> base >> exponent;

        cout << "power( " 
        << base << " , " << exponent 
        << " ) = " << power(base, exponent) << endl;
    }
}