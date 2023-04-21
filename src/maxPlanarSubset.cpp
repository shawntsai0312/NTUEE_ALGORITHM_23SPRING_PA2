#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

void printPath(int data[], vector<int> &result, int **S, int i, int j)
{
    if (i >= j)
        return;
    if (data[j] == i)
    {
        result.push_back(i);
        result.push_back(j);
        printPath(data, result, S, i + 1, j - 1);
    }
    else if (S[i][j] == S[i][j - 1])
    {
        printPath(data, result, S, i, j - 1);
    }
    else
    {
        result.push_back(j);
        result.push_back(data[j]);
        printPath(data, result, S, i, data[j] - 1);
        printPath(data, result, S, data[j] + 1, j - 1);
    }
}

int main(int argc, char *argv[])
{
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);
    int n = 0;
    fin >> n;

    int data[180000] = {};
    for (int i = 0; i < n >> 1; i++)
    {
        int a = 0, b = 0;
        fin >> a >> b;
        data[a] = b;
        data[b] = a;
    }

    int **map = new int *[n];
    for (int i = 0; i < n; i++)
    {
        map[i] = new int[n]();
    }

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (data[j] == i)
            {
                map[i][j] = map[i + 1][j - 1] + 1;
            }
            else if (data[j] > j || data[j] < i)
            {
                map[i][j] = map[i][j - 1];
            }
            else
            {
                int c = map[i][data[j] - 1] + map[data[j] + 1][j - 1] + 1;
                int nc = map[i][j - 1];
                map[i][j] = max(c, nc);
            }
        }
    }

    fout << map[0][n - 1] << "\n";
    vector<int> result;
    printPath(data, result, map, 0, n - 1);
    vector<int> sorted(result.size() >> 1);
    for (int i = 0; i < result.size() >> 1; i++)
    {
        if (result[i << 1] > result[(i << 1) + 1])
        {
            swap(result[i << 1], result[(i << 1) + 1]);
        }
        sorted[i] = result[i << 1];
    }
    sort(sorted.begin(), sorted.end());
    for (int p : sorted)
    {
        fout << p << " " << data[p] << "\n";
    }
    clock_t totalTime = clock();
    cout<<"total time: "<<(float)totalTime/CLOCKS_PER_SEC<<endl;

    return EXIT_SUCCESS;
}