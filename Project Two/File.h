#include "Node.h"
using namespace std;


bool compare(vector<Node*> a, vector<Node*> b){return a[0]->f > b[0]->f;}

//****************** Function will copy states for use in successor function*****************/
void printState(vector<Node*>& state){
    Node* ptr2;
    cout<<"State Size: "<<state.size()<<" State f: "<<state[0]->f<<"\n";
    cout<<"size of state: "<<state.size()<<"    f : "<<state[0]->f<<"     h: "<<state[0]->h<<"     g: "<<state[0]->g<<"\n";
    for (int i =1; i <state.size(); ++i){
      ptr2 = state[i];
      if (ptr2 != NULL){
        cout<<ptr2->index<<" ";
        while (ptr2->block != 't'){
          cout<<ptr2->block<<" "; //<<"list index "<<ptr2->listIndex<<" ";
          ptr2 = ptr2->next;
        }
        cout<<"\n";
      }
      else cout<<"NULL\n";
    }
}


//****************** Function will  PRINT THE QUEUE FOR DEBUGGING PURPOSES*****************/
void printQueue(priority_queue<std::vector<Node*>, std::vector<vector<Node*>>, decltype(&compare)> q){
    //vector<Node*> p;
    cout<<"*******Printing the Queue*********\n";
    cout<<"Size of Queue"<<q.size()<<"\n";
    while(!q.empty()){
        vector<Node*> p(q.top());
        printState(p);
        q.pop();
    } 
}

void readFile(string fileName, vector<Node*>& list, int& numOfBlocks){
    
    ifstream ifs(fileName);  // open input file

    Node* ptr;

	int index;
    char block, buf;
	string line;
    int count=0;
	bool check = true;
	while (!ifs.eof())
	{
		getline(ifs, line, '\n');
        for(unsigned int i = 0; i<line.length(); i++) {    // loop through the line
            // char c = line[i]; 
            if (!isspace(line[i])){
                char c = line[i];
                if (check){
                    index = c-'0';
                    check = false;
                    list.resize(index+1);   // resizes vector to make room for the linkedlist and avoids doubling the size
                    
                    // for tracking blank nodes within the limits
                    if (index >1 && list[index-1] == NULL) list[index-1]= insertFirst(index-1, 't');
                }
                else{
                    numOfBlocks +=1;
                    ptr= new Node(index, c);
                    // if the linked list is empty then set it up with the first node
                    if (list[index]== NULL) list[index] = insertFirst(index, c);
                    else  list[index]->insertLast(index, c); // if it isn't empty then insert at the end. '
                }
            } 
	    }
        check = true;
    }
    // for tracking the last node if it is blank
    if (list[index] == NULL) list[index]= insertFirst(index, 't');

    list[0] = new Node(0, 'd');// create data node at index 0


	ifs.close(); 
}
