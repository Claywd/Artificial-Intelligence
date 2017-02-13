#pragma once
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <cstddef>
#include <vector>
#include <string>
#include <sstream>
#include <cstddef>
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <cmath>
#include <algorithm>
#include <ctgmath>
#include <sys/time.h>

using namespace std;

struct Vertex {
  int id;
  vector<int> edges;
  Vertex(int i){ id=i;}
};

struct Node{
  int yIndex, listSize, depth;
  Vertex obj;
  bool visited = false;
  bool frontier= false;
  bool neighbor = false;
  float h;
  Node *prev, *next, *head, *trailer, *parent;
  Node(int k, Vertex e, Node *p=NULL, Node *n = NULL)
    : yIndex(k), obj(e), prev(p), next(n) {listSize =1;}
  Node * insertNode(int k, Vertex d){
      Node* n = new Node(k, d);
      Node* ptr= this;

       n->head = ptr->head;
       n->trailer = ptr->trailer;

       ptr->trailer->prev->next=n;
       n->prev=ptr->trailer->prev;
       ptr->trailer->prev = n;
       n->next=ptr->trailer;

       ptr->head->listSize = ptr->head->listSize+1;
       return n;
  }
};

struct Graph {
  int n, e;     // |V|, |E|

  vector<Node*> vList;
  Node* map[21][21];   // array of Vertex 
  int  xMap[400];        //map of corresponding x and y values
  int  yMap[400];
  int xMax, yMax;
  vector<Node*> index;
 
  Graph(){}
  void buildGraph();
  void insertVertex(int id, int x, int y);
  void insertEdge(int id, vector<int> edgeList);
  void getData(string file);
};

inline ostream& operator<<(ostream &os, Graph &figure){

  Node* troll;

  cout<<setw(3)<<"\t";
  for(int i=1; i<21; ++i) cout<<setw(3)<<i<<"\t";
  cout<<"\n";
  for (int i =1; i< 21; ++i){
    troll = figure.vList[i-1];
    cout<<setw(3)<<i<<"\t";
    for( int j=0; j<21; ++j){
      if (troll->yIndex == j) {
        cout<<setw(3)<<troll->obj.id<<"\t";
        troll=troll->next;
      }
      else if (troll->yIndex == j+1){
        cout<<setw(3)<<troll->obj.id<<"\t";
        troll=troll->next;
      }
      else cout<<setw(3)<<"\t";
    }
    cout<<"\n";
  }
} 	  