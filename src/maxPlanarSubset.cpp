#include <iostream>
#include <fstream>
#include <queue>
#include <time.h>

using namespace std;

// mps_tool.h
int **Matrix2D(int, int);
int **MPS(int *, int);
void MPS_result(int **, int *, queue<int> &, int, int);
// mps_tool.cpp
int **Matrix2D(int n, int m) // declare nxm matrix
{
    int **Mtx = new int *[n];
    for (int i = 0; i < n; i++)
    {
        Mtx[i] = new int[m];
    }
    return Mtx;
}

long long counter1 = 0;
long long counter2 = 0;
long long counter3 = 0;

int **MPS(int *C, int n)
{
    int **M = Matrix2D(n, n);
    int **A = Matrix2D(n, n);
    for (int i = 0; i < n; i++)
    {
        M[i][i] = 0;
    }
    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (C[i] < i || C[i] > j)
            {
                counter1++;
                M[i][j] = M[i + 1][j];
            }
            else if (C[i] == j)
            {
                counter2++;
                M[i][j] = M[i + 1][j - 1] + 1;
                A[i][j] = 1;
            }
            else
            {
                counter3++;
                int q1 = M[i + 1][C[i] - 1] + M[C[i] + 1][j] + 1;
                int q2 = M[i + 1][j];
                if (q1 >= q2)
                {
                    M[i][j] = q1;
                    A[i][j] = 2;
                }
                else
                {
                    M[i][j] = q2;
                }
            }
        }
    }
    return A;
}
void MPS_result(int **A, int *C, queue<int> &R, int p, int r)
{
    if (r <= p)
        return;

    switch (A[p][r])
    {
    case 1:
        R.push(p);
        MPS_result(A, C, R, p + 1, r - 1);
        break;
    case 2:
        R.push(p);
        MPS_result(A, C, R, p + 1, C[p] - 1);
        MPS_result(A, C, R, C[p] + 1, r);
        break;
    default:
        MPS_result(A, C, R, p + 1, r);
        break;
    }
}

int main(int argc, char *argv[])
{
    // read input
    char buffer[200];
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    int pts;
    fin >> pts;
    fin.getline(buffer, 200);
    int num1, num2;

    int *Set = new int[pts];
    for (int i = 0; i < pts; i++)
    {
        Set[i] = -1;
    }

    while (fin >> num1 >> num2)
    {
        Set[num1] = num2;
        Set[num2] = num1;
    }
    // find answer
    int **Ans = Matrix2D(pts, pts);
    Ans = MPS(Set, pts);
    queue<int> Result;
    MPS_result(Ans, Set, Result, 0, pts - 1);

    // result
    int resultSize = Result.size();
    fout << resultSize << endl;
    for (int i = 0; i < resultSize; i++)
    {
        fout << Result.front() << " " << Set[Result.front()] << endl;
        Result.pop();
    }
    fin.close();
    fout.close();
    clock_t totalTime = clock();
    cout << "total time: " << (float)totalTime / CLOCKS_PER_SEC << endl;
    cout << "counter 1 " << counter1 << endl;
    cout << "counter 2 " << counter2 << endl;
    cout << "counter 3 " << counter3 << endl;
    return 0;
}