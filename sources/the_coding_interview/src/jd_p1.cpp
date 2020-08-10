/**
X星人的基因
时间限制： 1000MS
内存限制： 65536KB
题目描述：
X星人的基因由A、B、C、D、E五种不同的结构组合而成。

如果两个性别不同的X星人的基因序列相似度大于50%，按照X星的法律他们是禁止结婚的，等于50%据说还是可以的。

那么基因的相似度怎么计算呢？分别从两个人身上取长度均为N的基因片段，如果它们的最长公共子序列（注意，最长公共子序列不需要连续）的长度为M，则相似度=M/N。是不是很简单呢？

现在给你两段X星人的基因序列片段，请你判断他们是不是可以结婚？



输入描述
单组输入。

每一组测试数据包含3行：

第1行数字N表示待比较基因序列片段的长度，N<=10^3。

第2行和第3行为两个长度为N的基因序列片段，中间以空格隔开。 

输出描述
先输出相似度，结果保留两位小数（四舍五入），然后输出判断结果（中间以空格隔开），如果可以输出”Yes“，如果不可以输出”No“。


样例输入
6
A B C D E E
A E D C B B
样例输出
0.33 Yes
 */ 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


    int longestCommonSubsequence(string &text1, string &text2) {
        int len1 = text1.length();  //5
        int len2 = text2.length();  //3
        vector<vector<int>> dp(len1+1, vector<int>(len2+1));

        for(int i = 1; i <= len1; i++){
            for(int j = 1; j <= len2; j++){
                if(text1[i - 1] == text2[j - 1]){
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }else {
                    dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[len1][len2];
    }

int main ()
{
    int n;
    string alienA;
    string alienB;
    char tmpCh;

    while(cin >> n) {
        alienA.clear();
        alienB.clear();

        for(int i = 0; i < n; i++) {
            cin >> tmpCh;
            alienA.push_back(tmpCh);
        }

        for(int i = 0; i < n; i++) {
            cin >> tmpCh;
            alienB.push_back(tmpCh);
        }

        int commonLength = longestCommonSubsequence(alienA, alienB);
        float result = 1.0 * commonLength / n;
        printf("%.2f ", result);
        if(result > 0.5) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }

    }
    return 0;
}