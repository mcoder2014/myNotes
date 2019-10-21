#include <iostream>
#include <vector>
#include <time.h>
#include <limits>
using namespace std;


int memoized_matrix_chain(std::vector<std::vector<int>> &memory,std::vector<std::vector<int>> &solution, std::vector<int>& chains, int i, int j)
{
    if (memory[i][j] < numeric_limits<int>::max())
        return memory[i][j];
    if(i == j)
        memory[i][j] = 0;
    else
    {
        for (int k = i; k < j; k++)
        {
            int result = memoized_matrix_chain(memory, solution, chains, i, k)
                    + memoized_matrix_chain(memory, solution, chains, k+1, j)
                    + chains[i-1] * chains[j] * chains[k];
            if(result < memory[i][j])
            {
                memory[i][j] = result;
                solution[i][j] = k;
            }
        }
    }
    return memory[i][j];
}

void print_solution(std::vector<std::vector<int>> &solution, int i, int j)
{
    if(i == j)
        cout << "A" << i;
    else
    {
        cout << "(";
        print_solution(solution, i, solution[i][j]);
        print_solution(solution, solution[i][j]+1, j);
        cout << ")";
    }
}

int bottom_up_matrix_chains(std::vector<int> &chains, std::vector<std::vector<int>> &solutions)
{
    int n = chains.size() - 1;
    std::vector<std::vector<int>> m(chains.size(), std::vector<int>(chains.size(), numeric_limits<int>::max()));
    for (int i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }
    for (int l = 2; l <= n; l++)
    {
        for (int i = 1; i <= n - l + 1; i++)
        {
            int j = i+l-1;
            for (int k = i; k <= j - 1 ; k++)
            {
                int q = m[i][k] + m[k+1][j] + chains[i-1] * chains[k] * chains[j];
                if(q < m[i][j])
                {
                    m[i][j] = q;
                    solutions[i][j] = k;
                }
            }
        }
    }
    return m[1][n];
}

int main()
{
    // 矩阵链乘，找到一种方案使得乘法的次数最少，
    // 如果A1, A2, A3, ..,An的按行数列数的形式写下来
    // A1.rows, A1.cols, A2.rows, A2.cols, .., An.rows, A,.cols
    // 因为矩阵乘法的性质，A1.cols == A2.rows, 并依次类推，
    // 所以我们可以用一个 n+1 长的数组表示整个矩阵链乘的阶次

    std::vector<int> chains({30, 35, 15, 5, 10, 20 ,25});
    int MATRIX_SIZE = 6;

    // 带备忘录的递归方法
    {
        std::vector<std::vector<int>> notes(MATRIX_SIZE+1, std::vector<int>(MATRIX_SIZE+1, numeric_limits<int>::max()));
        std::vector<std::vector<int>> solution(MATRIX_SIZE+1, std::vector<int>(MATRIX_SIZE+1, numeric_limits<int>::max()));

        clock_t time_start = clock();
        int result = memoized_matrix_chain(notes, solution, chains, 1, MATRIX_SIZE);
        cout << "Top_down:\t" << result << endl;
        clock_t time_end = clock();
        print_solution(solution, 1, MATRIX_SIZE);
        cout << endl;
        cout << "Cost time:\t" << (time_end- time_start)/CLOCKS_PER_SEC << endl;
    }

    // 自底向上的递归方法
    {
        std::vector<std::vector<int>> solution(MATRIX_SIZE+1, std::vector<int>(MATRIX_SIZE+1, numeric_limits<int>::max()));
        clock_t time_start = clock();
        int result = bottom_up_matrix_chains(chains, solution);
        cout << "Top_down:\t" << result << endl;
        clock_t time_end = clock();
        print_solution(solution, 1, MATRIX_SIZE);
        cout << endl;
        cout << "Cost time:\t" << (time_end- time_start)/CLOCKS_PER_SEC << endl;
    }

    return 0;
}
