#include <iostream>
#include <cmath>

/*

解题思路
优化的解法是求出 1~n 数字中每位出现 1 的次数相加。

我们举个例子先：12345

首先个位出现 1 的情况有 1234 + 1 种，因为只要个位为 1 即可，高位可以随便取，为什么 +1 呢，是因为可以取 0。

十位出现 1 的情况有 1239 + 1 种

同理百位出现 1 的情况有 1299 + 1 种，千位 1999 + 1 种，万位 2345 + 1 种。

那么 1 的总的出现次数为 1235 + 1240 + 1300 + 2000 + 2346 = 8121

我们举得例子中每位都大于 0 ，如果等于 0 的话

12045

第三位为 0，那么第三位出现 1，其他位的取值范围位 [0， 1199]，那么总次数为 1200

综上，我们可以得出一个结论

先定义几个变量，cur表示当前位，idx 表示当前的位数(从 0 开始算)，left 表示高位的值，right表示低位的值，

1 2 3 4 5

​ cur

如果当前位为1，当前位出现 1 的次数为 left*10^idx + right + 1

如果当前位为0，当前位出现 1 的次数为 left*(10^idx)

其余情况，当前位出现 1 的次数为 (left+1)*(10^idx)

其实就是相当于除去当前位其他位一共可以组成多大的数字。应该不难理解。

作者：yizhe-shi
链接：https://leetcode-cn.com/problems/number-of-digit-one/solution/c-dui-mei-wei-jin-xing-fen-xi-by-yizhe-shi-2/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

*/
 

int countDigitOne(int n) {
    if(n < 0) return 0;
    int ans = 0;
    int left, right = 0, idx = 0, cur = 0;
    while(n){
        cur = n % 10;
        left = n/10;
        if(cur == 0){
            ans += left*pow(10, idx);
        }else if(cur == 1){
            ans += left*pow(10, idx) + right + 1;
        }else{
            ans += (left + 1)*pow(10, idx);
        }
        right += cur*pow(10, idx);
        n /= 10;
        idx ++;
    }
    return ans;
}

int main()
{
    return 0;
}