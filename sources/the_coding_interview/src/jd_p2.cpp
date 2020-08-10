/**
 回文素数
时间限制： 3000MS
内存限制： 589824KB
题目描述：
现有一个正整数，希望去掉这个数中某一个数字之后可以得到一个回文素数。

回文素数是指一个素数同时还是一个回文数（回文数即从左到右和从右到左均一样的数，例如12321）。【注意：一位数也被认为是回文数】

输入两个正整数N和M，满足N<M，请编写一个程序统计N和M之间存在多少个满足上述要求的数？



输入描述
单组输入。

输入一行，包含两个正整数N和M，1<=N<M<=1000000，两个数字之间用空格隔开。

输出描述
输出在N和M之间（包含N和M）满足要求的数的个数。


样例输入
110 120
样例输出
10

提示
样例解释
在110和120之间存在10个满足要求的数，分别是110、111、112、113、114、115、116、117、118和119，它们去掉最后一位数都可以得到一个回文素数11。120不符合。故最终结果为10
规则
请尽量在全场考试结束10分钟前调试程序，否则由于密集排队提交，可能查询不到编译结果
点击“调试”亦可保存代码
编程题可以使用本地编译器，此页面不记录跳出次数
 */

#include <iostream>
#include <vector>
#include <set>

using namespace std;

bool huiwen(int n)
{
    int x = 0;
    int s = n;
    while(s > 0){
        x = x*10 + s%10;
        s = s/10;
    }
    if(x == n) {
        return true;
    } else {
        return false;
    }
}
void buildPrimeTable() {
    vector<int> table(1000000, 1);

    for(int i = 2; i < table.size(); i++) {
        if(table[i] == 0) {
            continue;
        }

        for(int j = 2; i *j < table.size(); j++) {
            table[i*j] = 0;
        }
    }
    set<int> primeSet;
    for(int i=1; i < table.size(); i++) {
        if(table[i] != 0 && huiwen(i)) {
            primeSet.insert(i);
        }
    }

    cout << "{";
    for(int item:primeSet) {
        cout << item << ", ";
    }
    cout << "}" << endl;
}

// 先构建出答案放在数组中
set<int> primeSet{2, 3, 5, 7, 11, 101, 131, 151, 181, 191, 313, 353, 373, 383, 727, 757, 787, 797, 919, 929, 
10301, 10501, 10601, 11311, 11411, 12421, 12721, 12821, 13331, 13831, 13931, 14341, 14741, 15451, 15551, 16061, 
16361, 16561, 16661, 17471, 17971, 18181, 18481, 19391, 19891, 19991, 30103, 30203, 30403, 30703, 30803, 31013, 
31513, 32323, 32423, 33533, 34543, 34843, 35053, 35153, 35353, 35753, 36263, 36563, 37273, 37573, 38083, 38183,
38783, 39293, 70207, 70507, 70607, 71317, 71917, 72227, 72727, 73037, 73237, 73637, 74047, 74747, 75557, 76367, 
76667, 77377, 77477, 77977, 78487, 78787, 78887, 79397, 79697, 79997, 90709, 91019, 93139, 93239, 93739, 94049, 
94349, 94649, 94849, 94949, 95959, 96269, 96469, 96769, 97379, 97579, 97879, 98389, 98689};

bool check(int n) {
    if(n<10){
        return false;
    }
    
    string num = std::to_string(n);
    for(int i = 0; i < num.size(); i++) {
        string tmpNum = num;
        tmpNum.erase(tmpNum.begin() + i);
        int resNum = std::stoi(tmpNum);
        if(primeSet.find(resNum) != primeSet.end()) {
            return true;
        }
    }
    return false;
}

int solu(int n, int m) {
    int value = 0;
    for(int i = n; i <= m; i++) {
        if(check(i)) {
            value++;
        }
    }
    return value;
}

int main()
{
    // buildPrimeTable(); // 构造回文素数表
    // buildResultTable();   // 构造结果表
    int n, m;
    while(cin >> n >> m) {
        cout << solu(n, m) << endl;
    }
    return 0;
}