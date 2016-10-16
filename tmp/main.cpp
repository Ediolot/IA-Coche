#include <cstdio>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
#include <list>
#include <iomanip>
#include "maze.hpp"
using std::vector;
using namespace std;

int main (void){
    maze_t m(5,10,20);
    vector< vector<int> > maz= m.getMaze();
    for(int i=0;i<m.getrows();i++){
        for(int j=0;j<m.getcols();j++){
            cout<<maz[i][j];
            if(j==(m.getcols())-1){
                cout<<endl;
            }
        }
    }
}