#include "Graph.h"


void printEdge(Node* ptr){
     for(int i=0; i<ptr->obj.edges.size(); ++i){
       cout<<ptr->obj.edges[i]<<" ";
     }
     cout<<"\n";
}

/****** compare function for sorting queue according to SLD***********/
bool compare(Node* a, Node* b){ return a->h > b->h;    }

/****** for testing purposes**********/
void printQueue(priority_queue<Node*, std::vector<Node*>, decltype(&compare)> q){
  
  for(auto i=0; i<q.size(); ++i){
    cout<<q.top()->obj.id<<"\n";
    q.pop();
  }
  
}

/********** function to compute the straight line distance for each node to another node***********/
float getSLD(int a, int b, int c, int d){ // using straight-line distance formula for the distance between two points  
  return sqrt(pow(c-a, 2)+ pow(d-b, 2)); 
}

Node* searchGraph(Graph graph, int a, int b, int c, int d, vector<Node*>& pathList, int& maxFrontier, int& iter, int& visited){

Node* start = graph.map[a][b];
Node* goal = graph.map[c][d];
priority_queue<Node*, std::vector<Node*>, decltype(&compare)> frontier(&compare);
Node* ptr = start;      // add the root node
Node* ptr1 = ptr;
Node* child;
int depth;
int smallest; 
vector<Node*> visitedList;
ptr->h = getSLD(graph.xMap[ptr->obj.id]+1,graph.yMap[ptr->obj.id]+1,c+1,d+1);
cout<<"value of "<<ptr->obj.id<<" is "<<ptr->h<<"\n";
ptr->depth =1;

  /*********Error Checking*************/
  if (start == goal) return start; // check start node for goal node
  else if (goal == NULL) return NULL; // check for NULL goal
  
  /*********Initialize the frontier with given state of problem************/
  else{                            //push the start edges into the queue
    for(int i =0; i<ptr->obj.edges.size(); ++i){ 
      child = graph.index[ptr1->obj.edges[i]];
      child->parent = ptr;         // set parent 
      ptr->visited = true;
      if (child->parent != NULL) child->depth = child->parent->depth+1;
      else child->depth = 0; // set root
      child->frontier=true;
      int edgeID = ptr1->obj.edges[i];
      child->h=getSLD(graph.xMap[edgeID]+1,graph.yMap[edgeID]+1,c+1,d+1);
      child->h = child->h + (ptr->h );      
      frontier.push(child);
    }


    pathList.push_back(ptr);
    visitedList.push_back(ptr);  // add to pathList after expanding nodes into frontier 
    ++visited; 
  }
  cout<<"iteration: "<<iter<<" checking "<<"("<<graph.xMap[ptr->obj.id]+1<<","<<graph.yMap[ptr->obj.id]+1<<")";
  cout<<", frontier size = "<<frontier.size()<<"\n";
  ++iter;
  
  while(iter<600 && ptr != NULL){
    cout<<"iteration: "<<iter<<" checking "<<"("<<graph.xMap[ptr->obj.id]+1<<","<<graph.yMap[ptr->obj.id]+1<<")";
    if (frontier.empty()) return NULL;
    ptr = frontier.top();
    frontier.pop();
    if (ptr->obj.id == goal->obj.id){
       pathList.push_back(ptr);
      return ptr;
    } 
    if (!ptr->visited){
      pathList.push_back(ptr);
      // if (graph.xMap[ptr->obj.id] <= c && graph.yMap[ptr->obj.id]<d){
      // if (pathList.size()-1 < ptr->depth+1) pathList.push_back(ptr);
      // else if (pathList[ptr->depth+1]->h > ptr->h) pathList[ptr->depth+1] = ptr;
       }
      } 
    /************ expand children to frontier***********/
    for(int i =0; i<ptr->obj.edges.size(); ++i){ 
      child = graph.index[ptr->obj.edges[i]];
      if (!child->frontier){
        if (!child->visited){
          child->parent = ptr;
          ptr->visited = true;
          if (child->parent != NULL) child->depth = child->parent->depth+1;
          else child->depth = 0;
          int edgeID = child->obj.edges[i];
          if (child == goal){ child->h = child->h+ getSLD(graph.xMap[edgeID]+1,graph.yMap[edgeID]+1,graph.xMap[child->parent->obj.id]+1,graph.yMap[child->parent->obj.id]+1);}
          else{
            
            child->h=getSLD(graph.xMap[edgeID]+1,graph.yMap[edgeID]+1,c+1,d+1);

          }
          child->frontier=true; 
          frontier.push(child);
        }
      }
    }
    if (maxFrontier < frontier.size()) maxFrontier = frontier.size();
    
    cout<<", frontier size = "<<frontier.size()<<"\n";
    ++iter; 

  }



int main(int argc, char **argv) {
  try {

    // Argument Variables
    extern char *optarg;
    extern int optind;
    int debug, i, visited, maxFrontier, iter, err = 0;
    unsigned short xStart, yStart, xGoal, yGoal;
    string path="";

    //get argument input into variables
    while((i = getopt(argc, argv, "a:b:c:d:e:")) != -1){
      switch(i){
        case 'a':
          path = optarg;
          break;
        case 'b':
          xStart = atoi(optarg) -1;
          break;
        case 'c':
          yStart = atoi(optarg)-1;
          break;
        case 'd':
          xGoal = atoi(optarg)-1;
          break;
        case 'e':
          yGoal = atoi(optarg)-1;
          break;
        default:
          cout<<"No input."<<endl;
          break;
      }
    }
    
    
    Graph TAMU;
    TAMU.buildGraph();    // creates the structures needed
    TAMU.getData(path);   // fills the graph we created
    cout<<TAMU<<"\n";     //outputs the graph that was read in

    vector<Node*> solutionPath;


    if (TAMU.map[xGoal][yGoal] == NULL) cout<<"Sorry Goal is not in list\n";
    else{
      Node* ptr = searchGraph(TAMU, xStart, yStart, xGoal, yGoal, solutionPath, maxFrontier, iter, visited);
      if (ptr!=NULL)cout<<ptr->obj.id<<"\n";
      else cout<<"DAMMIT\n";
      cout<<" Solution Path\n";
    for (int i = 0; i< solutionPath.size(); ++i) {
      cout<<"vertex "<<solutionPath[i]->obj.id<< "("<<TAMU.xMap[solutionPath[i]->obj.id]+1<<","<<TAMU.yMap[solutionPath[i]->obj.id]+1<<")\n";
    }
    cout<<"Total Iterations: "<<iter<<"\n";
    cout<<"Max Frontier Size: "<<maxFrontier<<"\n";
    cout<<"Vertices Visited: "<<visited<<"\n";
    cout<<"path length: "<<solutionPath.size()<<"\n";

     }
}
  catch(exception &e) {
    cerr << e.what() << endl;
    return -1;
  }

}
