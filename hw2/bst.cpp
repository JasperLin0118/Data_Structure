#include<bits/stdc++.h>
using namespace std;
//Define binary tree's node and its node fields
typedef struct node *treePointer;
typedef struct node
{
    int data;
    treePointer leftChild, rightChild;
} node;
//Declare all the functions used in this problem
bool BST_Insert(int, treePointer *);
void BST_Print(treePointer);
//I separate all the orders into 4 functions in BST_Print function to be more understandable
void inorder(treePointer);
void preorder(treePointer);
void postorder(treePointer);
void levelorder(treePointer);
bool BST_Search(int, treePointer);
bool BST_Delete(int, treePointer *);
void meaty_postorder(treePointer, queue<int>&);
int main()
{
    //For main menu input and always sustainably executing the actions
    int main_select; 
    while(1)
    {
        //Main menu outputs and user input
        cout<<"(1)Binary searching Tree.\n(2)Finding Meaty.\n(0)Escape and face to music next year."<<endl;
        cin>>main_select;
        if(main_select == 1) //User selects (1)Binary searching Tree
        {
            node *bst = NULL;  //Creates a new Binary Search Tree
            //For action menu input and always sustainably executing the actions
            char action;
            while(1)
            {
                //Action menu outputs and user input
                cout<<"(I)nsert a number.\n(D)elete a number.\n(S)earch a number.\n(P)rint 4 kinds of orders.\n(R)eturn"<<endl;
                cin >> action;
                if(action == 'i') //User selects (I)nsert a number
                {
                    cout<<"Enter numbers: ";
                    while(1) //Let user input all the numbers to be inserted
                    {
                        int current_num;
                        cin>>current_num;
                        if(current_num != -1) //If the number doesn't equal to -1, insert that number into Binary Search Tree
                        {
                            if(BST_Insert(current_num, &bst))  //The number is already in the tree
                                cout<<"Error. Number "<<current_num<<" exists."<<endl;
                            else //The number doesn't exist in the tree and is successfully inserted into the tree
                                cout<<"Number "<<current_num<<" is inserted."<<endl;
                        }
                        else    //If the number equals to -1, which means to end up inserting the nodes
                            break;
                    }
                }
                else if(action == 'd') //User selects (D)elete a number
                {
                    cout<<"Enter numbers to be deleted : ";
                    while(1) //Let user input all the numbers to be deleted
                    {
                        int current_num;
                        cin>>current_num;
                        if(current_num != -1)  //If the number doesn't equal to -1, delete the number in the Binary Search Tree
                        {
                            if(BST_Delete(current_num, &bst)) //The number is in the tree, so it needs to be deleted
                                cout<<"Number "<<current_num<<" is deleted."<<endl;
                            else  //The number doesn't exist in the tree so it can't be deleted
                                cout<<"Number "<<current_num<<" does not exist."<<endl;
                        }
                        else  //If the number equals to -1, which means to end up deleting the nodes
                            break;
                    }
                }
                else if(action == 's') //User selects (S)earch a number
                {
                    cout<<"Enter numbers to search : ";
                    while(1) //Let user input all the numbers wanted to be searched
                    {
                        int current_num;
                        cin>>current_num;
                        if(current_num != -1) //If the number doesn't equal to -1, search the number
                        {
                            if(BST_Search(current_num, bst))  //The number is in the tree, so the searching is successful
                                cout<<"Bingo! "<<current_num<<" is found."<<endl;
                            else  //The number doesn't exist in the tree so it doesn't found
                                cout<<"SORRY. "<<current_num<<" does not found."<<endl;
                        }
                        else //If the number equals to -1, which means to end up searching
                            break;
                    }
                }
                else if(action == 'p')  //User selects (P)rint 4 kinds of orders
                    BST_Print(bst); //Print the Binary Search Tree in 4 different ways
                else if(action == 'r') //Return to main menu
                    break;
            }
        }
        else if(main_select == 2) //User selects (2)Finding Meaty
        {
            //Get the file name
            cout<<"Please input the map file: ";
            string file_name = "";
            cin>>file_name;
            fstream file;
            file.open(file_name, ios::in);
            //Create a new Binary Search Tree and a vector to save all the numbers
            node *bst = NULL;
            while(file.peek() != EOF) //The program continues to read the file until it reaches the end of file
            {
                //Read a single line each time in the file and insert the value into the tree 
                string num;
                getline(file, num);
                bool temp = BST_Insert(stoi(num), &bst);
            }          
            //visit the tree in postorder and push the visited value into queue
            queue<int> q;
            meaty_postorder(bst, q);
            cout<<"Load file success."<<endl;
            int sword_location, meaty_location;
            char trap_index;
            //User inputs sword location, meaty location and trap index
            cout<<"\nPlease input the sword location: ";
            cin>>sword_location;
            cout<<"Please input the Meaty's location: ";
            cin>>meaty_location;
            cout<<"Please input the broccoli traps' index (0~9): ";
            cin>>trap_index;
            cout<<endl;
            while(!q.empty()) //Check all the values from smallest to largest if any digit of it matches the trap index. If so, delete that node.
            {
                string str_num = to_string(q.front());
                q.pop();
                if(str_num.find(trap_index)!=string::npos) //There's at least a digit of the value matches the trap index, so it needs to be deleted
                {
                    cout<<"Number "<<str_num<<" is deleted."<<endl;
                    bool tmp = BST_Delete(stoi(str_num), &bst);
                }
            }
            cout<<"\nCapoo successfully found his favorite meaty<3.\n\nShortest path to find meaty :"<<endl;
            //We use stack to deal with finding the shortest path
            stack<treePointer> s;
            s.push(bst);
            treePointer current = bst;
            while(!s.empty())  //Find the sword starting from the root of the tree
            {
                if(sword_location < current->data) //If the sword location is less than the number of current node, go to left chlid
                {
                    cout<<current->data<<"->";
                    s.push(current->leftChild);
                    current = current->leftChild;
                }
                else if(sword_location > current->data) //If the sword location is greater than the number of current node, go to right chlid
                {
                    cout<<current->data<<"->";
                    s.push(current->rightChild);
                    current = current->rightChild;
                }
                else //If the sword location is equal to the number of current node, we found the sword
                    break;
            }
            while(!s.empty()) //Find Meaty starting from where we find the sword
            {
                treePointer current = s.top();
                s.pop();
                if(BST_Search(meaty_location, current)) //If current location is the ancestor of Meaty's location in the tree
                {
                    if(meaty_location < current->data) //If the Meaty's location is less than the number of current node, go to left chlid
                    {
                        cout<<current->data<<"->";
                        s.push(current->leftChild);
                    }
                    else if(meaty_location > current->data) //If the Meaty's location is greater than the number of current node, go to right chlid
                    {
                        cout<<current->data<<"->";
                        s.push(current->rightChild);
                    }
                    else if(meaty_location == current->data) //If the Meaty's location is equal to the number of current node, we found Meaty
                    {
                        cout<<current->data;
                        break;
                    }
                }
                else //If current location is not the ancestor of Meaty's location in the tree, go up a level
                    cout<<current->data<<"->";
            }
            cout<<endl;
        }
        else if(main_select == 0)  //End the program
            break;
    }
}
bool BST_Insert(int num, treePointer *originalroot)  //Inserting a number into the binary search tree
{
    treePointer root = *originalroot;
    if(root) //If the root exists
    {
        while(root) //Compare the number and the current node's value until it's null
        {
            if(root->data > num) //If the number is less than the current value, go to left child
            {
                if(!root->leftChild) //Insert the number if left child doesn't exist
                {
                    node *newnode = (node*) malloc(sizeof(node));
                    newnode->data = num;
                    newnode->leftChild = NULL;
                    newnode->rightChild = NULL;
                    root->leftChild = newnode;
                    return false;
                }
                root = root->leftChild;
            }
            else if(root->data < num) //If the number is greater than the current value, go to right child
            {
                if(!root->rightChild) //Insert the number if right child doesn't exist
                {
                    node *newnode = (node*) malloc(sizeof(node));
                    newnode->data = num;
                    newnode->leftChild = NULL;
                    newnode->rightChild = NULL;
                    root->rightChild = newnode;
                    return false;
                }
                root = root->rightChild;
            }
            else //The number already exists in the tree, no need to insert
                return true;
        }
    }
    else //If the root doesn't exist, let the number be the root of the tree
    {
        node *newnode = (node*) malloc(sizeof(node));
        newnode->data = num;
        newnode->leftChild = NULL;
        newnode->rightChild = NULL;
        *originalroot = newnode;
    }
    return false;
}
bool BST_Search(int num, treePointer originalroot) //Check whether the number is in the tree
{
    treePointer root = originalroot;
    if(root)  //Check if root exists
    {
        while(root) //Compare the number and the current node's value until it's null
        {
            if(root->data > num) //If the number is less than the current value, go to left child, otherwise, go to right child
                root = root->leftChild;
            else if(root->data < num)
                root = root->rightChild;
            else //If the number is in the tree
                return true;
        }
    }
    return false;
}
bool BST_Delete(int num, treePointer *originalroot) //Deleting a number from the binary search tree
{
    treePointer root = *originalroot;
    treePointer parent = NULL; 
    while(root) //Compare the number and the current node's value until it's null
    {
        if(root->data > num) //If the number is less than the current value, go to left child
        {
            if(!root->leftChild) //The number doesn't exist in the tree
                return false;
            else if(root->leftChild->data == num) //Keep on going
                parent = root;
            root = root->leftChild;
        }
        else if(root->data < num) //If the number is greater than the current value, go to right child
        {
            if(!root->rightChild) //The number doesn't exist in the tree
                return false;
            else if(root->rightChild->data == num) //Keep on going
                parent = root;
            root = root->rightChild;
        }
        else if(root->data == num) //There are 3 conditions if we find the node
        {
            if(!root->leftChild && !root->rightChild) //The node is a leaf
            {
                if(root != *originalroot) 
                {
                    if(parent->leftChild == root) //Let parent's left or right child point to null
                        parent->leftChild = NULL;
                    else if(parent->rightChild == root)
                        parent->rightChild = NULL;
                }
                else //If the number is the root, let the root be null
                    *originalroot = NULL;
            }
            else if(root->leftChild && root->rightChild) //The node has 2 children
            {
                treePointer min_node = root->rightChild;
                treePointer parent = root;
                while(min_node) //Find the smallest node of the right sub-tree
                {
                    if(!min_node->leftChild)
                        break;
                    else 
                    {
                        parent = min_node;
                        min_node = min_node->leftChild;
                    }
                }
                //Switch the root number to the smallest number in right sub-tree
                root->data = min_node->data;
                //Connect the right subtree (if exist) of the smallest number in right sub-tree to the parent node
                if(parent->rightChild == min_node) parent->rightChild = min_node->rightChild;
                if(parent->leftChild == min_node) parent->leftChild = min_node->rightChild;
            }
            else //The node has 1 child only
            {
                treePointer child;
                if(root->leftChild) //Get the child node
                    child = root->leftChild;
                else
                    child = root->rightChild;
                if(!parent) //If the root is original root
                    *originalroot = child;    
                else if(parent->leftChild == root) //Connect parent node with child node
                    parent->leftChild = child;
                else if(parent->rightChild == root)
                    parent->rightChild = child;
            }
            return true;
        }
    }
    return false;
}
void BST_Print(treePointer root) //Prints the Binary Search Tree in 4 orders
{
    cout<<"The tree in prefix order : ";
    preorder(root); //Print in prefix order
    cout<<"\nThe tree in infix order : ";
    inorder(root); //Print in infix order
    cout<<"\nThe tree in postfix order : ";
    postorder(root); //Print in postfix order
    cout<<"\nThe tree in level order : ";
    levelorder(root); //Print in level order
    cout<<endl;
}
void inorder(treePointer root)
{
    if(root) //Go to left most child first, then print the value and lastly go to right child
    {
        inorder(root->leftChild);
        cout<<root->data<<" ";
        inorder(root->rightChild);
    }
}
void preorder(treePointer root)
{
    if(root) //Print the value first, then go to left child and lastly go to right child until you can't continue
    {
        cout<<root->data<<" ";
        preorder(root->leftChild);
        preorder(root->rightChild);
    }
}
void postorder(treePointer root)
{
    if(root) //Visit the children first and lastly print the value
    {
        postorder(root->leftChild);
        postorder(root->rightChild);
        cout<<root->data<<" ";
    }
}
void levelorder(treePointer root)
{
    queue<treePointer> q; //Use queue to store the nodes in each level (first in first out)
    if(!root) return;
    q.push(root);
    while(!q.empty()) 
    {
        root = q.front(); 
        q.pop();
        cout<<root->data<<" ";
        //Push the left child first then right child to perform the traversal from left to right each level
        if(root->leftChild)
            q.push(root->leftChild);
        if(root->rightChild)
            q.push(root->rightChild);
    }
}
void meaty_postorder(treePointer root, queue<int>& q)
{
    if(root) //Visit the children first and lastly push the value into queue
    {
        meaty_postorder(root->leftChild, q);
        meaty_postorder(root->rightChild, q);
        q.push(root->data);
    }
}