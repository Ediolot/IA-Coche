#include <cstdio>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <list>
#include <iomanip>
using std::vector;
class maze_t{
   
   private:
   
    int rows; //rows
    int cols; //columns
    int obs; //obstacles
    
    public:
    
     maze_t(int r,int c, int o);
     int getrows(void);
     int getcols(void);
     vector< vector<int> > getMaze(void);
     vector< vector<bool> > getObstacles(vector< vector<int> > maze);
};