#include <iostream>
#include <fstream>
using namespace std;

struct line
{
    int small;
    int large;
};

bool checkNonOverlapped(line line1, line line2)
{
    // cout << line1.small << "\t" << line1.large << "\t" << line2.small << "\t" << line2.large << endl;
    if ((line1.small == line2.small) && (line1.large == line2.large))
        return true;
    bool checkPointSmall = false;
    bool checkPointLarge = false;
    if ((line2.small > line1.small) && (line2.small < line1.large))
        checkPointSmall = true;
    if ((line2.large > line1.small) && (line2.large < line1.large))
        checkPointLarge = true;
    // cout << checkPointSmall << "\t" << checkPointLarge << "\t" << (checkPointSmall == checkPointLarge) << endl;
    return checkPointSmall == checkPointLarge;
}

int main(int argc, char *argv[])
{
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    int N;
    fin >> N;

    line *data = new line[N];
    for (int i = 0; i < N; i++)
    {
        int node1, node2;
        fin >> node1 >> node2;
        data[i].small = node1 < node2 ? node1 : node2;
        data[i].large = node1 > node2 ? node1 : node2;
    }

    int testResult = 0;

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (!checkNonOverlapped(data[i], data[j]))
            {
                testResult++;
                cout << "line " << i << " and line " << j << " overlapped\n"
                     << "line " << i << " is " << data[i].small << " to " << data[i].large << "\n"
                     << "line " << j << " is " << data[j].small << " to " << data[j].large << "\n"
                     << "\n";
                fout << "line " << i << " and line " << j << " overlapped\n"
                     << "line " << i << " is " << data[i].small << " to " << data[i].large << "\n"
                     << "line " << j << " is " << data[j].small << " to " << data[j].large << "\n"
                     << "\n";
            }
        }
    }
    if (testResult == 0)
    {
        cout << "no error\n";
        fout << "no error\n";
    }
    else
    {
        cout << testResult << " error(s)\n";
        fout << testResult << " error(s)\n";
    }
}