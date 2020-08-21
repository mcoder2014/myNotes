/**
 斐波那契蛇
时间限制： 3000MS
内存限制： 589824KB
题目描述：
小明昨晚做了一个梦。在梦里，很多很多斐波那契数连成了一条蛇。突然，最大的那个数变成了蛇头，把小明一口给吞到肚子里去了。

小明被吓醒了，他赶紧拿笔在纸上面画了一条斐波那契蛇。



这是一个蛇形迂回的斐波那契数列，它是一个n*n的矩阵，在上面的矩阵中n=3。第1行第1列是最大值，然后按照顺时针的次序数字逐渐变小。

下面是n=4时的情况：



小明希望你能够编写一个程序，输入一个正整数n，然后逐行逐列输出斐波那契蛇形矩阵中的元素。



输入描述
单组输入，输入数据占一行，包含一个正整数n，表示斐波那契蛇形矩阵的大小。(n<10)

输出描述
输出数据占一行，逐行逐列（从第1行开始到第n行，每一行从第1列开始到第n列）输出斐波那契蛇形矩阵中的元素，每两个数字之间用一个空格隔开。


样例输入
3
样例输出
34 21 13
1 1 8
2 3 5

 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void print(vector<vector<int64_t>> &mat);

bool DEBUG = false;

vector<int64_t> getFabi(int size) 
{
    vector<int64_t> fabi(size, 1);

    if(size <= 2)
    {
        return fabi;        
    }

    for(int i = 2; i <size; i++)
    {
        fabi[i] = fabi[i-1] + fabi[i-2];
    }

    return fabi;
}

vector<vector<int64_t>> getMatrix(vector<int64_t> &fabi, int size)
{
    vector<vector<int64_t>> matrix(size, vector<int64_t>(size, 0));
    if(DEBUG) print(matrix);

    int left = 0;
    int right = size;
    int top = 0;
    int bottom = size;
    
    int i = 0, j = 0;
    int count = 0;
    
    while(i >= top && i < bottom && j >= left && j <right)
    {
        // 从左往右
        for(;j<right; j++) {
            matrix[i][j] = fabi[count++];
            if(DEBUG) cout << i <<" " << j << " " << matrix[i][j] << endl;
        }
        top++;
        i++;j--;

        // 向下
        if(!(i >= top && i < bottom && j >= left && j <right))
        {
            break;
        }

        for(;i<bottom; i++) {
            matrix[i][j] = fabi[count++];
            if(DEBUG) cout << i <<" " << j << " " << matrix[i][j] << endl;
        }
        right--;
        i--;j--;

        // 向左
        if(!(i >= top && i < bottom && j >= left && j <right))
        {
            break;
        }

        for(;j>=left; j--) {
            matrix[i][j] = fabi[count++];
            if(DEBUG) cout << i <<" " << j << " " << matrix[i][j] << endl;
        }
        bottom--;
        j++;i--;

        // 向上
        if(!(i >= top && i < bottom && j >= left && j <right))
        {
            break;
        }

        for(;i>=top;i--){
            matrix[i][j] = fabi[count++];
            if(DEBUG) cout << i <<" " << j << " " << matrix[i][j] << endl;
        }
        left++;
        i++; j++;
    }

    return matrix;
}

void print(vector<vector<int64_t>> &mat)
{
    for(vector<int64_t>& line:mat) 
    {
        for(int i = 0; i < line.size()-1; i++)
        {
            cout << line[i] << " ";
        }
        cout << line[line.size()-1] << endl;
    }
}

int main()
{
    int n;
    cin >> n;

    vector<int64_t> fabi = getFabi(n * n);
    reverse(fabi.begin(), fabi.end());

    if(DEBUG)
    {
        for(int64_t i:fabi)
            cout << i << " ";
        cout << endl;
    }


    vector<vector<int64_t>> mat = getMatrix(fabi, n);
    print(mat);

    return 0;
}