#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <limits>

using namespace std;
enum Direction
{
    UP_LEFT,
    UP,
    LEFT
};

int memoized_LCS_length(string &X, string &Y, std::vector<std::vector<Direction>> &b, std::vector<std::vector<int>> &c, int i, int j)
{
    if (i==0 || j==0)
        return 0;
    if(c[i][j] > 0)
        return c[i][j];

    if(X[i] == Y[j])
    {
        int length = 1 + memoized_LCS_length(X, Y, b, c, i-1, j-1);
        c[i][j] = length;
        b[i][j] = UP_LEFT;
        return length;
    }
    else {
        int length_X = memoized_LCS_length(X, Y, b, c, i-1, j);
        int length_Y = memoized_LCS_length(X, Y, b, c, i, j-1);
        if(length_X >= length_Y)
        {
            c[i][j] = length_X;
            b[i][j] = LEFT;
            return length_X;
        }
        else
        {
            c[i][j] = length_Y;
            b[i][j] = UP;
            return length_Y;
        }
    }
}

int LCS_length(string &X, string &Y, std::vector<std::vector<Direction>> &b, std::vector<std::vector<int>> &c)
{
    for(int i = 0; i < X.size(); i++)
    {
        c[i][0] = 0;
    }
    for (int j = 0; j < Y.size(); j++) {
        c[0][j] = 0;
    }
    for (int i = 1; i <= X.size(); i++)
    {
        for (int j = 1; j <= Y.size(); j++)
        {
            if(X[i] == Y[j])
            {
                c[i][j] = c[i-1][j-1] +1;
                b[i][j] = UP_LEFT;
            }
            else if (c[i-1][j] >= c[i][j-1])
            {
                c[i][j] = c[i-1][j];
                b[i][j] = LEFT;
            }
            else
            {
                c[i][j] = c[i][j-1];
                b[i][j] = UP;
            }
        }
    }
    return c[X.length()][Y.length()];
}

void print_solution(string &X, std::vector<std::vector<Direction>> &b, int i, int j)
{
    if(i == 0 || j == 0)
        return;
    if(b[i][j] == UP_LEFT)
    {
        print_solution(X, b, i-1, j-1);
        cout << X[i];
    }
    else if(b[i][j] == UP)
        print_solution(X, b, i, j-1);
    else
        print_solution(X, b, i-1, j);
}

int main()
{
    string X = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    //            CG T    T CG  GAAGCCGGCCGAA
    //         "    GTCG  T CG  GAAGCCGGCCGAA"
    string Y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";
    //         "GTCGT CGGAA GCCG  GC C G AA"
    //            CGTTCGGAA GCCG  GC C G AA

    // 备忘录自顶向下
    {
        std::vector<std::vector<Direction>> b(X.length() + 1, std::vector<Direction>(Y.length() + 1));
        std::vector<std::vector<int>> c(X.length() + 1, std::vector<int>(Y.length() + 1, -1));
        int result = memoized_LCS_length(X, Y, b, c, X.size(), Y.size());
        cout << "LCS length:\t" << result << endl;
        print_solution(X, b, X.length(), Y.length());
        cout << endl;
    }

    // 自底向上方法
    {
        std::vector<std::vector<Direction>> b(X.length() + 1, std::vector<Direction>(Y.length() + 1));
        std::vector<std::vector<int>> c(X.length() + 1, std::vector<int>(Y.length() + 1));
        int result = LCS_length(X, Y, b, c);
        cout << "LCS length:\t" << result << endl;
        print_solution(X, b, X.length(), Y.length());
        cout << endl;
    }

    return 0;
}
