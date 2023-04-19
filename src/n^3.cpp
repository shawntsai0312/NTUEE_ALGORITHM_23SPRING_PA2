#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void print2DVector(vector<vector<int> > vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec[0].size(); j++)
        {
            cout << vec[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int lineChecker(vector<int> data, int x, int y)
{
    if (x == y)
        return 0;
    return (data[x] == y && data[y] == x) ? 1 : 0;
}

void findSol(vector<int> data, vector<vector<int> > solution, vector<bool> &selected, int i, int j)
{
    if (i <= j)
    {
        int split = solution[i][j];
        cout << "split\t"
             << i << "\t"
             << split << '\t'
             << split << '\t'
             << j << endl;
        if (lineChecker(data, i, split))
        {
            selected[i]=true;
            selected[split]=true;
        }
        if (lineChecker(data, split + 1, j))
        {
            selected[split + 1]=true;
            selected[j]=true;
        }
        if (split > i && split < j)
        {
            findSol(data, solution, selected, i, split);
            findSol(data, solution, selected, split + 1, j);
        }
    }
}

int findMPS(vector<int> data, vector<vector<int> > &M, vector<vector<int> > &S, int i, int j)
{
    if (i >= 0 && j >= 0)
    {
        if (M[i][j] >= 0)
        {
            return M[i][j];
        }
        else
        {
            int split = i;
            int max = lineChecker(data, i, j);
            if (i + 1 <= j - 1)
                max += findMPS(data, M, S, i + 1, j - 1);

            for (int k = i; k < j; k++)
            {
                // cout << i << "\t" << k << "\t" << k + 1 << "\t" << j << "\n";
                int temp = findMPS(data, M, S, i, k) + findMPS(data, M, S, k + 1, j);
                if (temp >= max)
                {
                    max = temp;
                    split = k;
                }
            }
            M[i][j] = max;
            S[i][j] = split;
            // cout << "M\t" << i << "\t" << j << "\t" << M[i][j] << endl;
            return M[i][j];
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

    // initialize data
    vector<int> data;
    for (int i = 0; i < N; i++)
    {
        // cout << "data push back" << i << endl;
        data.push_back(-1);
    }

    // construct the data vector
    for (int i = 0; i < N / 2; i++)
    {
        int node1, node2;
        fin >> node1 >> node2;
        data[node1] = node2;
        data[node2] = node1;
    }
    /*--------------------- convert .in into data end --------------------*/

    /*---------------- check if data is correctly written ----------------*/
    // for (int i = 0; i < N; i++)
    // {
    //     cout << i << '\t' << data[i] << '\n';
    // }
    /*-------------- check if data is correctly written end --------------*/

    /*--------------------- initialize 2D-vector M,S ---------------------*/
    vector<vector<int> > M, S;
    for (int i = 0; i < N; i++)
    {
        vector<int> init;
        for (int j = 0; j < N; j++)
        {
            init.push_back(-1);
        }
        M.push_back(init);
    }
    S = M;
    /*------------------- initialize 2D-vector M,S end -------------------*/

    cout << "*** initialization ***\n";
    /*--------------------- initialize 2D-vector M,S ---------------------*/
    vector<bool> selected;
    for (int i = 0; i <= N; i++)
    {
        selected.push_back(false);
    }
    /*------------------- initialize 2D-vector M,S end -------------------*/
    cout << "*** initialization end ***\n";

    cout << "*** Find MPS ***\n";
    cout << findMPS(data, M, S, 0, data.size() - 1) << '\n';
    // print2DVector(M);
    // print2DVector(S);
    cout << "*** Find MPS end ***\n";

    cout << "*** filter out which to select ***\n";
    /*--------------------- filter out which to select ---------------------*/
    findSol(data, S, selected, 0, S[0].size() - 1);

    vector<int> answer;
    for (int i = 0; i <= N; i++)
    {
        if (selected[i])
        {
            answer.push_back(i);
        }
    }
    /*------------------- filter out which to select end -------------------*/
    cout << "*** filter out which to select end ***\n";
    cout << "*** print the final answer ***\n";
    /*----------------------- print the final answer -----------------------*/
    // cout << mps << endl;
    for (int i = 0; i < answer.size(); i++)
    {
        cout << answer[i];
        if (i % 2 == 0)
            cout << "\t";
        else
            cout << "\n";
    }
    /*--------------------- print the final answer end ---------------------*/
    cout << "*** print the final answer end ***\n";
}