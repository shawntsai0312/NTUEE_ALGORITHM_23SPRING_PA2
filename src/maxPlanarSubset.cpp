#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Merge
void Merge(vector<int> &data, int low, int middle1, int middle2, int high)
{
    vector<int> leftArr, rightArr;
    leftArr = vector<int>(data.begin() + low, data.begin() + middle1 + 1);
    rightArr = vector<int>(data.begin() + middle2, data.begin() + high + 1);

    int i = 0,
        j = 0;
    for (int k = low; k <= high; k++)
    {
        if (i == leftArr.size())
        {
            data[k] = rightArr[j];
            j++;
        }
        else if (j == rightArr.size())
        {
            data[k] = leftArr[i];
            i++;
        }
        else
        {
            if (leftArr[i] <= rightArr[j])
            {
                data[k] = leftArr[i];
                i++;
            }
            else
            {
                data[k] = rightArr[j];
                j++;
            }
        }
    }
}

// Sort subvector (Merge sort)
void MergeSortSubVector(vector<int> &data, int low, int high)
{
    if (low < high)
    {
        int middle = (low + high) / 2;
        MergeSortSubVector(data, low, middle);
        MergeSortSubVector(data, middle + 1, high);
        Merge(data, low, middle, middle + 1, high);
    }
}

// Merge sort method
void MergeSort(vector<int> &data)
{
    MergeSortSubVector(data, 0, data.size() - 1);
}

int mps(int *data, int **M, int **S, int i, int j)
{
    if (i >= 0 && j >= 0)
    {
        if (M[i][j] >= 0)
            return M[i][j];
        else
        {
            // case 1 j==i
            if (i == j)
            {
                M[i][j] = 0;
                return 0;
            }
            // case 2 j>i
            else if (j > i)
            {
                // the point connected to j is i
                if (data[j] == i)
                {
                    M[i][j] = mps(data, M, S, i + 1, j - 1) + 1;
                    S[i][j] = 0;
                }
                // the point connected to j is not in the region of i to j
                else if (data[j] > j || data[j] < i)
                {
                    M[i][j] = mps(data, M, S, i, j - 1);
                    S[i][j] = 1;
                }
                // the point connected to j is in the region of i to j
                else
                {
                    // choose line(j,data[j])
                    int temp1 = mps(data, M, S, i, data[j] - 1) + mps(data, M, S, data[j] + 1, j - 1) + 1;
                    // not choose line(j,data[j])
                    int temp2 = mps(data, M, S, i, j - 1);
                    // save the larger one
                    if (temp1 > temp2)
                    {
                        M[i][j] = temp1;
                        S[i][j] = 2;
                    }
                    else
                    {
                        M[i][j] = temp2;
                        S[i][j] = 3;
                    }
                }
                // cout << i << "\t" << j << "\t" << M[i][j] << endl;
                return M[i][j];
            }
        }
    }
}

void printPath(int *data, vector<int> &result, int **S, int i, int j)
{
    if (i >= j)
        return;
    else
    {
        switch (S[i][j])
        {
        case 0:
            result.push_back(i);
            result.push_back(j);
            printPath(data, result, S, i + 1, j - 1);
            break;
        case 1:
            printPath(data, result, S, i, j - 1);
            break;
        case 2:
            result.push_back(j);
            result.push_back(data[j]);
            printPath(data, result, S, i, data[j] - 1);
            printPath(data, result, S, data[j] + 1, j - 1);
            break;
        case 3:
            printPath(data, result, S, i, j - 1);
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    /*----------------------- convert .in into data ----------------------*/
    // N is the total number of nodes
    int N;
    fin >> N;

    int *data = new int[N];
    for (int i = 0; i < N / 2; i++)
    {
        int node1, node2;
        fin >> node1 >> node2;
        data[node1] = node2;
        data[node2] = node1;
    }
    // for(int i=0;i<data.size();i++)
    //     cout<<i<<"\t"<<data[i]<<endl;
    /*--------------------- convert .in into data end --------------------*/
    int **M = new int *[N];
    int **S = new int *[N];
    for (int i = 0; i < N; i++)
    {
        int *temp = new int[N];
        for (int j = 0; j < N; j++)
        {
            temp[j] = -1;
        }
        M[i] = temp;
    }
    for (int i = 0; i < N; i++)
    {
        int *temp = new int[N];
        for (int j = 0; j < N; j++)
        {
            temp[j] = -1;
        }
        S[i] = temp;
    }
    int ans = mps(data, M, S, 0, N - 1);
    cout << ans << endl;
    fout << ans << endl;
    cout << "\n";
    vector<int> result;
    vector<int> sortResult;
    printPath(data, result, S, 0, N - 1);
    for (int i = 0; i < result.size() / 2; i++)
    {
        if (result[2 * i] > result[2 * i + 1])
        {
            swap(result[2 * i], result[2 * i + 1]);
        }
        // cout << result[2*i] << "\t" << result[2*i+1] << "\n";
        sortResult.push_back(result[2 * i]);
    }
    MergeSort(sortResult);
    for (int i = 0; i < sortResult.size(); i++)
    {
        cout << sortResult[i] << " " << data[sortResult[i]] << "\n";
        fout << sortResult[i] << " " << data[sortResult[i]] << "\n";
    }
}