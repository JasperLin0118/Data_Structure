#include <bits/stdc++.h>
using namespace std;
//struct edge and disjoint set
typedef struct Edge {int from, to, w;} Edge;
typedef struct disjointset
{
    vector<int> data;
    void initialize(int n) //for disjoint set initialization
    {
        for(int i=0;i<n;i++){
            data.push_back(i);
        }
    }
    int find(int n) //find the number in the disjoint set
    {
        return data[n];
    }
    void merge(int x, int y) //merge 2 sets
    {
        int original = find(y);
        for(int j=0;j<data.size();j++)
        {
            if(data[j] == original)
                data[j] = find(x);
        }
    }
}disjointset;
//compare function for sorting the edges in iterator (smallest to largest)
bool operator < (Edge &a, Edge &b)
{
    return a.w < b.w;
}
fstream file;
ofstream outputfile;
int main()
{
    //get the file name and open the file
    cout << "Please input file name: ";
    string filename = "";
    cin >> filename;
    file.open(filename, ios::in);
    //create another file for output
    string outputfilename = filename.replace(filename.find("input"), 5, "output");
    outputfile.open(outputfilename, ios::out);
    //get the number of vertices and edges
    string v_and_e;
    getline(file, v_and_e);
    stringstream ve;
    int vertices, edges;
    ve << v_and_e;
    ve >> vertices >> edges;
    //get all the edges data (in, out, weight)
    vector<Edge> E;
    for(int i=0;i<edges;i++)
    {
        string dataline;
        getline(file, dataline);
        stringstream datas;
        datas << dataline;
        Edge e;
        datas >> e.from >> e.to >> e.w;
        E.push_back(e);
    }
    //sort the edges
    sort(E.begin(), E.end());
    //create a disjoint set and initialize
    disjointset d;
    d.initialize(vertices);
    int total=0, count=0;
    for(int i=0;i<edges;i++)
    { //if the edge's from and to are from different sets, merge them
        if(d.find(E[i].from) != d.find(E[i].to))
        {
            count++;
            total += E[i].w;
            d.merge(E[i].from, E[i].to);
        } 
        //check if all the vertices are in a single set
        if(count==vertices-1) break;
    }
    outputfile << total << endl;
    outputfile.close();
}