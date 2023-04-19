#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct line
{
    int small;
    int large;
};

bool overlapped(line line1, line line2)
{
    if ((line2.small < line1.small && line2.large > line1.large) ||
        (line2.small > line1.small && line2.large < line1.large))
        return true;
    else
        return false;
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

    vector<line> lineArr;
    for (int i = 0; i < N / 2; i++)
    {
        int node1, node2;
        fin >> node1 >> node2;
        line temp;
        temp.small = node1 < node2 ? node1 : node2;
        temp.large = node1 > node2 ? node1 : node2;
        lineArr.push_back(temp);
    }
    /*--------------------- convert .in into data end --------------------*/
}