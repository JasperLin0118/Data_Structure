#include <bits/stdc++.h>
using namespace std;
//Struct node and pointer for binary tree
typedef struct node *treePointer;
typedef struct node
{
    int data;
    int index;
    treePointer leftChild, rightChild;
}node;
//declare the functions
void insert(treePointer *,node *);
void postorder(treePointer);
void preorder(treePointer);
fstream file;
ofstream outputfile;
int n, c = 0;
int main()
{
    //get the file name and open the file
    cout << "Please input file name: ";
    string filename = "";
    cin >> filename;
    file.open(filename, ios::in);
    //get the number of datatests
    string num;
    getline(file, num);
    int number = stoi(num);
    //create another file for output
    string outputfilename = filename.replace(filename.find("input"), 5, "output");
    outputfile.open(outputfilename, ios::out);
    while(number--)
    {
        //get the string S and the number of nodes in the binary tree
        string s, n_nodes;
        getline(file, s); 
        getline(file, n_nodes);
        n = stoi(n_nodes);
        vector<int> v, v_in;
        // get the datas of the first binary tree
        string dataline;
        getline(file, dataline);
        stringstream datas;
        datas << dataline;
        int data;
        while(datas >> data)
            v.push_back(data);
        datas.clear();
        //get the datas of the second binary tree
        getline(file, dataline);
        datas << dataline;
        while(datas >> data)
            v_in.push_back(data);
        node *bt = NULL;
        if(s == "preorder-inorder") 
        { //create binary tree by taking nodes in v_in then find its index in v
            for(int i=0;i<n;i++)
            { //create new node and insert it into the binary tree
                node *newnode = (node*) malloc(sizeof(node));
                newnode->data = v[i];
                newnode->leftChild = NULL;
                newnode->rightChild = NULL;
                newnode->index = find(v_in.begin(), v_in.end(), v[i]) - v_in.begin();
                insert(&bt, newnode);
            }
            postorder(bt);
        }
        else if(s == "postorder-inorder")
        { //create binary tree by taking nodes in v_in and find its index in v
            for(int i=n-1;i>=0;i--)
            { //create new node and insert it into the binary tree
                node *newnode = (node*) malloc(sizeof(node));
                newnode->data = v[i];
                newnode->leftChild = NULL;
                newnode->rightChild = NULL;
                newnode->index = find(v_in.begin(), v_in.end(), v[i]) - v_in.begin();
                insert(&bt, newnode);
            }
            preorder(bt);
        }
        outputfile << endl;
        c=0;
    }
    outputfile.close();
}
void insert(treePointer *originalRoot, node *newnode)
{
    treePointer root = *originalRoot;
    if(root) 
    {
        while(root)
        { // find the correct place to insert the node by comparing the index of the nodes
            if(newnode->index < root->index)
            { //find until there's no leftchild
                if(!root->leftChild)
                {
                    root->leftChild = newnode;
                    return;
                }
                root = root->leftChild;
            }
            else if(newnode->index > root->index)
            {//find until there's no rightchild
                if(!root->rightChild)
                {
                    root->rightChild = newnode;
                    return;
                }
                root = root->rightChild;
            }
        }
    }
    else //if there's no root, the new node will be the root
        *originalRoot = newnode;
}
void postorder(treePointer root) //binary tree traversal by postorder
{
    if(root)
    {
        postorder(root->leftChild);
        postorder(root->rightChild);
        c++;
        if(c == n)
            outputfile << root->data;
        else
            outputfile << root->data << " ";
    }
}
void preorder(treePointer root) //binary tree traversal by preorder
{
    if(root)
    {
        c++;
        if(c == n)
            outputfile << root->data;
        else
            outputfile << root->data << " ";
        preorder(root->leftChild);
        preorder(root->rightChild);
    }
}