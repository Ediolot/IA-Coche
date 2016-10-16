#include "maze.hpp"
#include <stdlib.h>
#include <time.h>
#include <list>
#include <vector>
#include<iostream>
#include <iomanip>
using std::vector;

using namespace std;


maze_t::maze_t(int r, int c, int o):
    rows(r),
    cols(c),
    obs(o){}
int maze_t::getrows(void)
{
  return(rows);
}
int maze_t::getcols(void)
{
  return(cols);
}

vector< vector<int> > maze_t::getMaze(void){
   vector< vector<int> > maze( rows, vector<int> (cols) );
    srand(time(NULL));
    int num=obs+1;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(num>0){
                    maze[i][j]=(0+rand() % (2-0));
                    if(maze[i][j]==1){
                        num--;
                    }
                }
                if(num==0){
                    maze[i][j]=0;
                }
            }
        }
        return maze; 
}
vector< vector<bool> > maze_t::getObstacles(vector< vector<int> > maze){
   vector< vector<bool> > obstacles( rows, vector<bool> (cols) );
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(maze[i][j]==1){
               obstacles[i][j]==true; 
            }
            if(maze[i][j]==0){
               obstacles[i][j]==false; 
            }
        }
    }
    return obstacles; 
}
