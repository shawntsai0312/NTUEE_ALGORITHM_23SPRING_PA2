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
    for (int i = 0; i < N / 2; i++)
    {
        int node1, node2;
        fin >> node1 >> node2;
        data[i].small = node1 > node2 ? node1 : node2;
        data[i].large = node1 > node2 ? node2 : node1;
    }

    int testResult = 0;

    for (int i = 0; i < N - 1; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            if (!checkNonOverlapped(data[i], data[j]))
            {
                testResult++;
                cout << "line\t" << i << "\tand line\t" << j << "\toverlapped\n"
                     << "line\t" << i << "\t" << data[i].small << "\t" << data[i].large << "\n"
                     << "line\t" << j << "\t" << data[j].small << "\t" << data[j].large << "\n"
                     << "\n";
                fout << "line\t" << i << "\tand line\t" << j << "\toverlapped\n"
                     << "line\t" << i << "\t" << data[i].small << "\t" << data[i].large << "\n"
                     << "line\t" << j << "\t" << data[j].small << "\t" << data[j].large << "\n"
                     << "\n";
            }
        }
    }
    if (!testResult)
    {
        cout << "no error\n";
        fout << "no error\n";
    }
    else
    {
        cout << "there are " << testResult << " error(s)\n";
        fout << "there are " << testResult << " error(s)\n";
    }
}