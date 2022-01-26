#include <bits/stdc++.h>
using namespace std;
//struct edge
typedef struct Edge {int from, to, w;} Edge;
//declear function
void dfs(vector<vector<int>>, int, vector<int>&, vector<bool>&, int);
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
    //get the number of vertices
    string v;
    getline(file, v);
    int V = stoi(v);
    vector<int> costs(V);
    vector<vector<int>> adj_mat;
    vector<bool> visited(V);
    //initialize all the vectors needed
    fill(costs.begin(), costs.end(), 0);
    fill(visited.begin(), visited.end(), false);
    for(int i=0;i<V;i++)
    {
        vector<int> weights(V);
        fill(weights.begin(), weights.end(), 0);
        adj_mat.push_back(weights);
    }
    //input costs into adjacency matrix
    string dataline;
    stringstream datas;
    for(int j=0;j<V-1;j++)
    {
        getline(file, dataline);
        datas << dataline;
        int s, t, c;
        datas >> s >> t >> c;
        adj_mat[s-1][t-1] = c;
        adj_mat[t-1][s-1] = c;
        datas.clear();
    }
    string Root;
    //get the root
    getline(file, Root);
    int root = stoi(Root);
    visited[root-1] = true;
    //start dfs
    dfs(adj_mat, root-1, costs, visited, 0);
    for(int a=0;a<costs.size();a++)
        outputfile << a+1 << " " << costs[a] << endl;
    outputfile.close();
}
void dfs(vector<vector<int>> adj_mat, int root, vector<int>& costs, vector<bool>& visited, int curr_cost)
{
    for(int i=0;i<adj_mat.size();i++)
    { //if the node hasn't visited before, and is connected with current node
      //then the node is valid
        if(!visited[i] && adj_mat[root][i] != 0)
        {
            costs[i] += adj_mat[root][i] + curr_cost;
            visited[i] = true;
            bool check = true;
            //check if every node is visited, if so, end dfs traversal
            for(int i=0;i<visited.size();i++)
            {
                if(!visited[i])
                    check = false;
            }
            if(check)
                return;
            //if not, keep going
            dfs(adj_mat, i, costs, visited, costs[i]);
        }
    }
}
