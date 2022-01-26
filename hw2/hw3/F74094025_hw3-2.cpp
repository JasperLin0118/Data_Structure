#include <bits/stdc++.h>
using namespace std;
//Declare functions
void dfs(vector<bool>&, vector<vector<int>>, int);
fstream file;
ofstream outputfile;
int main()
{
    //get the file name and open the file
    cout << "Please input file name: ";
    string filename = "";
    cin >> filename;
    file.open(filename, ios::in);
    //get the number of datasets
    string num;
    getline(file, num);
    int n = stoi(num);
    //create another file for output
    string outputfilename = filename.replace(filename.find("input"), 5, "output");
    outputfile.open(outputfilename, ios::out);
    while(n--)
    { //get number of vertices m and entry point of DFS traversal
        string mt, dataline;
        getline(file, mt);
        stringstream ss, datas;
        ss << mt;
        int start, m;
        ss >> m >> start;
        // get all the data of the adjacency matrix
        vector<vector<int>> adj_mat;
        for(int i=0;i<m;i++)
        {
            getline(file, dataline);
            datas << dataline;
            vector<int> v;
            int data;
            while(datas >> data)
                v.push_back(data);
            adj_mat.push_back(v);
            datas.clear();
        }
        // initialize visited vector for dfs traversal
        vector<bool> visited(m);
        fill(visited.begin(), visited.end(), false);
        visited[start] = true;
        outputfile << start << " ";
        // start the dfs traversal
        dfs(visited, adj_mat, start);
        outputfile << endl;
    }
}
void dfs(vector<bool>& visited, vector<vector<int>> adj_mat, int curr)
{
    for(int i=0;i<adj_mat.size();i++)
    { // if the node hasn't visited before, and is connected with current node
      // then the node is valid
        if(!visited[i] && adj_mat[curr][i] == 1)
        {
            visited[i] = true;
            bool check = true;
            //check if every node is visited, if so, end dfs traversal
            for(int i=0;i<visited.size();i++)
            {
                if(!visited[i])
                    check = false;
            }
            if(check)
            {
                outputfile << i;
                return;
            }
            else
                outputfile << i << " ";
            //if not, keep going
            dfs(visited, adj_mat, i);
        }
    }
}