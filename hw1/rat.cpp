#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<stack>
#include<fstream>
#include<string>
#include<cstring>
using namespace std;

//Each point's parameter(attributes)
struct element
{
    int x, y, dir;
};
//Set up each direction's direction vector
struct index{int x, y;};
enum directions{RIGHT, DOWN, UP, LEFT};
index direction[4] = {
    {.x = 0, .y = 1},  //Right
    {.x = 1, .y = 0},  //Down
    {.x = -1, .y = 0}, //Up
    {.x = 0, .y = -1}  //Left
};
//set up start point and end point coordinates, and declare the function to of getting the path
int start_x, start_y, end_x, end_y;
void Path(int, int, string[]);

int main() {
	//Get the file name
    string file_name = "";
    cout << "enter file name : ";
    cin >> file_name;
    //Open the file by using relative path
    fstream file;
    file.open(file_name, ios::in);
    //set up the maze by reading the contents of the file
    string maze[17] = {};
    for(int i=0;i<17;i++)
        getline(file, maze[i]);
    for(int j=0;j<17;j++)
        cout << maze[j] << endl;
    //We enter start and end points and find its path until either one gets (-1, -1) and we end the code
    while(1)
    {
    	//Input the start position
        cout << "enter start position : ";
        cin >> start_x >> start_y;
        //Check if start position's coordinate is (-1, -1). If it's (-1, -1), end the code
        if(start_x == -1 && start_y == -1)
        {
            cout << "end the code.";
            break;
        }
        //Input the end position
        cout << "enter exit position : ";
        cin >> end_x >> end_y;
        //Check if end position's coordinate is (-1, -1). If it's (-1, -1), end the code
        if(end_x == -1 && end_y == -1)
        {
            cout << "end the code.";
            break;
        }
        //Start the pathfinding journey by calling the function
        Path(17, 17, maze);
    }
    return 0;
}

void Path(int m, int p, string maze[])
{
    //initialize visited routes and total steps
    int visited[17][17] = {0}, total_step = 0;
    //begin at (start_x, start_y) and print it
    visited[start_x][start_y] = 1;
    stack<element> s;
    //put the starting point into stack to begin pathfinding
    element current = {.x = start_x, .y = start_y, .dir = RIGHT};
    s.push(current);
    //pathfinding
    while(!s.empty())
    {
        //set the current point to top element of the stack and pop it from the stack
        current = s.top();
        s.pop();
        int current_x = current.x, current_y = current.y, current_dir = current.dir;
        //output the current position
        cout << total_step++ << ":" << current_x << "," << current_y << endl;
        //try to move to next step starting from going right, down, up and then left
        while(current_dir < 4) 
        {
        	//set up next step's points
            int next_x = current_x + direction[current_dir].x;
            int next_y = current_y + direction[current_dir].y;
            //if we get to the end point, output the result and end the pathfinding
            if(next_x == end_x && next_y == end_y)  
            {
                cout << total_step++ << ":" << next_x << "," << next_y << endl;
                cout << "successfully escaped!!" << endl;
                return;
            }
            //if the point is new and is not wall, then push it into stack, which means we moved to that step
            if(maze[next_x][next_y] == '0' && visited[next_x][next_y] == 0)
            {
            	//push next step position into the stack, and set the current point to next direction
                visited[next_x][next_y] = 1;
                current.x = current_x;
                current.y = current_y;
                current.dir = current_dir + 1;
                s.push(current);
                //move to next step
                current_x = next_x;
                current_y = next_y;
                current_dir = RIGHT;
            }
            else //move to next direction
            {
                current_dir++;
                continue;
            }
            //output the point we checked that is valid
            cout << total_step++ << ":" << next_x << "," << next_y << endl;
        }
    }
    //if we have popped out all the elements in the stack and didn't find out the path, which means we failed to escape then we output the result
    cout << "Failed to escape." << endl;
}
