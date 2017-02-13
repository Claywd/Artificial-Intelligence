#include "Search.h"

using namespace std;

int maxStack = 26;
int maxBlock = 20;


/******** Notes***********/
  // State vector will be of size 1 more than the total index
  // Each index in the state vector will be a pointer to a list of characters in that index
  // Each list will begin with the first block in the list and end with 't'
  // Each node in the list will keep track of the first block in the list using the head pointer

int main(int argc, char **argv)
{
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
cout<<"***************************\n";
    // Argument Variables
    extern char *optarg;
    extern int optind;
    int i;
    string state1, state2;
    
    //get argument input into variables
    while((i = getopt(argc, argv, "a:b:")) != -1){
      switch(i){
        case 'a':
          state1 = optarg;
          break;
        case 'b':
          state2 = optarg;
          break;
      }
    }

    
    // declare list to hold the list of states
    vector<Node*> initialState;
    vector<Node*> goalState;
    int numOfBlocks=0;

    // Fill those vectors
    readFile(state1, initialState, numOfBlocks);
    cout<<"end of read\n";
    readFile(state2, goalState, numOfBlocks);
    cout<<"end of read\n";
    
    cout<<"***Initial State****\n";
    printState(initialState);
    cout<<"***Goal State****\n";
    printState(goalState);

    if (initialState.size() != goalState.size() ){
      cout<<"Error Indexes are not the same\n";
      return -1;
    }


    cout<<"start search\n";
    vector<vector<Node*>> solution = greedy(initialState, goalState, numOfBlocks);

    cout<<"Solution Found!\n";
    int lastStep=0;
    for(int i =0; i<solution.size(); ++i){
      
             for (int j =0; j<solution[i][0]->parent.size(); ++j){
                   cout<<"*************Step "<<j<<"*************\n";
                       printState(solution[i][0]->parent[j]);
                       lastStep = j;
                }
         }
    cout<<"*************Step "<<lastStep+1<<"*************\n";
    printState(solution[solution.size()-1]);
    
   


    cout<<"!!!!!!!!!!!!!!!!****************!!!!!!!!!!!!!!FINISHED!!!!!!!!!!!!!**************!!!!!!!!!!!!!!!!\n";
return 0;
}
