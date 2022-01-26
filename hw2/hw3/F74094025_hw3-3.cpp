#include <bits/stdc++.h>
using namespace std;
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
    { //get number of vertices m and entry point of BFS traversal
        string mt, dataline;
        getline(file, mt);
        stringstream ss, datas;
        ss << mt;
        int start, m;
        ss >> m >> start;
        //get all the data of the adjacency matrix
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
        // initialize visited vector for bfs traversal
        vector<bool> visited(m);
        fill(visited.begin(), visited.end(), false);
        queue<int> q;
        q.push(start);
        //start the bfs traversal
        while(!q.empty())
        {
            int num = q.front();
            q.pop();
            if(visited[num]) //if this node has been visited, skip it
                continue;
            visited[num] = true;
            bool check = true;
            for(int i=0;i<visited.size();i++)
            {
                if(!visited[i])
                    check = false;
            }
            if(!check)
                outputfile << num << " ";
            else
                outputfile << num;
            for(int i=0;i<adj_mat.size();i++)
            { //add unvisited nodes connected with current node into queue
                if(!visited[i] && adj_mat[num][i] == 1)
                    q.push(i);
            }
        }
        outputfile << endl;
    }
    outputfile.close();
}