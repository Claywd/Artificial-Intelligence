#include "File.h"
using namespace std;

//****************** Function will RETURN THE INDEX OF THE POINTER N, IN THE VECTOR STATE*****************/
int searchState(vector<Node*>& state, Node* n){

    int count=0;
    Node* ptr;
    for (int i=1; i<state.size()+1; ++i){
        ptr = state[i];
        while(ptr->block != 't'){
            if (ptr->block == n->block){
                 count = i;
                 break;                 
            }
            else ptr= ptr->next;
        }
        if(count != 0) break;
    }
    return count;
}
//****************** Function will RETURN Heauristic Value of the State*****************/

float numOutPlace(vector<Node*>& currentState, vector<Node*>& goalState, int numOfBlocks){
         Node* goalPtr, *currentPtr;
        float count=0;
        float valueOffset;
        bool flag = false;
        for (auto i=1; i<goalState.size(); ++i){
            goalPtr = goalState[i];
            
            while(goalPtr->block != 't'){ //search through the list
            
                if (currentState[i]->searchListIndex(goalPtr) != goalState[i]->searchListIndex(goalPtr)){ 
                    
                    // if the block isn't even in the right index then add the cost of moving it to this index of the state. 
                    if (currentState[i]->searchListIndex(goalPtr) == -2){
                        int temp = searchState(currentState, goalPtr); // index of the goalPtr in the current state

                        // add cost of freeing that List index in that list
                        if (currentState[temp]->block != 't' && temp != 0) {
                            count += currentState[temp]->tail->prev->listIndex - currentState[temp]->searchListIndex(goalPtr);
                            }
                            //add the cost of freeing the block in this list
                        if (currentState[i]->block != 't') {count += currentState[i]->tail->prev->listIndex;}
                    } 
                    //count += 1;
                    count += numOfBlocks + 1 - goalPtr->listIndex + currentState[i]->listIndex;
                }
                else{ //check the previous blocks 
                    Node* prevPtr = currentState[i]->searchList(goalPtr);
                    while(prevPtr->block != currentState[i]->searchList(goalPtr)->block){
                        if (currentState[i]->searchListIndex(prevPtr) != goalState[i]->searchListIndex(prevPtr)){
                            count += (currentState[i]->tail->prev->listIndex - prevPtr->listIndex);
                        }
                        prevPtr = prevPtr->next;
                    }
                    //weight the previous nodes higher than the following nodes since following nodes are sure to have already produced states.
                    count += (currentState.size()-1)* count; 
                    prevPtr = currentState[i]->searchList(goalPtr);
                    while(prevPtr->block != 't'){
                        if (currentState[i]->searchListIndex(prevPtr) != goalState[i]->searchListIndex(prevPtr)){
                            count += (currentState[i]->tail->prev->listIndex - prevPtr->listIndex);
                        }
                        prevPtr = prevPtr->next;
                    }


                } 
                
                goalPtr = goalPtr->next;
            }
        }

        return count;
}

//****************** Function will copy states for use in successor function*****************/
vector<Node*> copyNodes (vector<Node*>& state){
    vector<Node*> newState;
    Node* ptr2;
    for (int i =1; i <state.size(); ++i){
        newState.resize(state.size());      //reserve space in new vector

        ptr2 = state[i];        //set pointer
        while(ptr2 != NULL){ 
            if (state[i]->block == ptr2->block ){ 
            newState[i] = insertFirst(i, ptr2->block);} //new list
            else { 
                if (ptr2->block != 't'){
                    newState[i]->insertLast(ptr2->index, ptr2->block);}
                }
            ptr2 = ptr2->next;
        }
    }
    newState[0] = state[0]->copy();
    return newState;
}

//****************** Function will create successor states and return them in a vector*****************/
vector<vector<Node*>> successor(vector<Node*>& state, Node* n, vector<Node*>& goal){
  // determine weather or not to add node to successor list
    int indexToLeaveAlone = n->index;
    vector<vector<Node*>> successorStates;

    /***Loop through the state****/ 
    for (int i=1; i< state.size(); ++i){
        vector<Node*> tempState = copyNodes(state);

            if(i != indexToLeaveAlone){    // insert a new node with n characteristics
                
                if (tempState[i]->block != 't'){            // its a tail
                    tempState[i]->insertLast(i, n->block);
                }
                else {
                    Node* temp = insertFirst(i, n->block);
                    tempState[i] = temp;
                }
             if (tempState[n->index]->block == n->block){ // remove header
                    tempState[n->index] = tempState[n->index]->next;
                    tempState[n->index]->prev = NULL;        
                    if (tempState[i]->block == 't') tempState[i]->index = n->index;
                }
                else{   // remove in list
                    Node* ptr = tempState[n->index]->tail->prev->prev;
                      ptr->next = ptr->tail;
                      
                      ptr->tail->prev = ptr;
                    }
            }
                            successorStates.resize(successorStates.size()+1);           // resize vector to hold the new state
                successorStates[successorStates.size()-1] = (tempState);      // access directly to assist with memory efficiency
                tempState.clear();
        }
return successorStates;
}


//****************** Function will call heuristic on each list index*****************/
bool searchVector(vector<vector<Node*>>& list, vector<Node*>& state, int numOfBlocks){

    for (int i=0;  i<list.size(); ++i){
        if (numOutPlace(list[i], state, numOfBlocks) == 0){   //found the state in the list so return true
            return true;
        }
    }
    return false;       // did not find state in list so return false
}



vector<vector<Node*>> greedy(vector<Node*> start, vector<Node*> goal, int& numOfBlocks){
  priority_queue<vector<Node*>, std::vector<vector<Node*>>, decltype(&compare)> frontier(&compare);
  
  vector<vector<Node*>> successorStates; // for good children states
  vector<vector<Node*>> temp;           // for temporary children states
 
  vector<vector<Node*>> visited;    // for all states that have been ejected from the queue
  vector<vector<Node*>> solution;   //for the solution
  
//   clock_t t1;
//     t1=clock();

  Node* ptr;
    cout<<"Watching the iteration\n";

    start[0] = new Node(0, 'd');
    start[0]->h = numOutPlace(start, goal, numOfBlocks);
    cout<<" h of start "<<start[0]->h<<"\n";
    solution.push_back(start);

visited.push_back(start);
     vector<Node*> currentState (start);
  for(int i=1; i<currentState.size(); ++i){
      ptr = currentState[i]; 
      if (ptr != NULL && ptr->tail != NULL && ptr->tail->prev != NULL && ptr->block != 't'){
          ptr = ptr->tail->prev;
          ptr->g = 1;
          
          temp = successor(currentState, ptr, goal);
          for( int j=0; j<temp.size(); ++j){
              if (!searchVector(visited, temp[j], numOfBlocks) && !searchVector(successorStates, temp[j], numOfBlocks)  ){
                temp[j][0]->parent.push_back(start); 
                temp[j][0]->h = numOutPlace(temp[j], goal, numOfBlocks);
                temp[j][0]->g = 1; 
                temp[j][0]->f = temp[j][0]->h + temp[j][0]->g;
                successorStates.push_back(temp[j]);
                frontier.push(temp[j]);
                 
               }

            }
            temp.clear(); 
      }
  }
  cout<<"******************printing queue**************\n";
    printQueue(frontier);
      
    int count =0;
  while (!frontier.empty()){    // Start working on the queue
  
    
    
    vector<Node*> currentState(frontier.top());
    frontier.pop();
    //cout<<"queue size is"<<frontier.size()<<"\n";
    visited.push_back(currentState);


    /****used for watching the iterations every 5 seconds********/
    // float seconds = (clock()-t1) / CLOCKS_PER_SEC;
    // if (seconds  >= 5){
    //     cout<<"iteration "<<count<<"\n";
    //     printState(currentState);
    //     seconds = 0;
    //     t1=clock();
    // }


    if (numOutPlace(currentState, goal, numOfBlocks) == 0 ){
       
       cout<<"WE FOUND THE GOAL! on iteration "<<count<<"\n";
       printState(currentState);
       solution.push_back(currentState);

       cout<<"printing solution parent size "<<solution[0][0]->parent.size()<<"\n";

        return solution;
    }

      for(int i=1; i<currentState.size(); ++i){
        ptr = currentState[i]; 
        if (ptr != NULL && ptr->tail != NULL && ptr->tail->prev != NULL && ptr->block != 't'){
          //cout<<"in the loop\n";
          ptr = ptr->tail->prev;
          //ptr->g = 1;
          
          temp = successor(currentState, ptr, goal);
          for( int j=0; j<temp.size(); ++j){
            if (!searchVector(visited, temp[j], numOfBlocks) && !searchVector(successorStates, temp[j], numOfBlocks)  ){
                temp[j][0]->parent.push_back(currentState); // tracking the parent
                temp[j][0]->h = numOutPlace(temp[j], goal, numOfBlocks);    // keeping track of h
                temp[j][0]->g = currentState[0]->g + 1;                     //keeping track of root to node
                temp[j][0]->f = temp[j][0]->h + temp[j][0]->g;              // using f to combine the best of both. 
                successorStates.resize(successorStates.size()+1);           // resize vector to hold the new state
                successorStates[successorStates.size()-1] = (temp[j]);      // access directly to assist with memory efficiency
                frontier.push(temp[j]);
             }  
            }
            temp.clear(); 
          }
        }
         count=count+1;
  }
 
  return solution;
}
