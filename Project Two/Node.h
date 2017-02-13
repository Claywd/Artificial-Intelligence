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
#include <time.h>

using namespace std;


struct Node {
  int index=0, depth=0,listSize, listIndex;   // track index in list, depth in index of list, and listSize;
  char block;  //track block
  float h=0, f=0;
  int g=0;      // for heuristic purposes
  Node *prev, *next, *head=NULL, *tail=NULL; 
  vector<vector<Node*>> parent;

  /*****Constructor*********/ 
  Node(int i, char l, Node *p=NULL, Node *n = NULL)
    : index(i), block(l), prev(p), next(n) {listSize =1;}

   
    Node* searchList(Node* n){  //search a list based on Node characteristics

        Node* ptr = this;

        while(ptr->block != n->block ) ptr = ptr->next;

        return ptr;

    }
    
    int searchListIndex(Node* n){  //search a list based on Node characteristics

        Node* ptr = this;
        int count=0;
        while(ptr->block != n->block ){ 
            if (ptr->block == 't' || ptr == NULL) return -2; //in case it isn't in the list
            ptr = ptr->next;
            count = count+1;
        }
        return count;

    }

    Node* copy(){
        Node* n = new Node(0, 'd');
        
        n->h = h;
        n->g = g;
        n->f = f;
        n->index = index;
        n->listIndex = listIndex;
        n->listSize = listSize;
        n->parent = this->parent;
        
        return n;
    }

    Node* insertFront(int i, char b){    // any other node in the list
        Node* ptr = new Node(i, b);
        
        this->prev = ptr;
        ptr->next = this;
        this->head = ptr;
        ptr->prev = NULL;
        ptr->listIndex = 1;
        ptr->listSize = this->listSize + 1;
       return ptr;
    }

    Node* insertLast(int i, char b){    // any other node in the list
        Node* ptr = new Node(i, b);
        ptr->listIndex = this->tail->prev->listIndex+1;

        this->tail->prev->next = ptr;
        ptr->prev = this->tail->prev;
        ptr->next = this->tail;
        this->tail->prev = ptr;
        ptr->tail = this->tail;
        this->listSize = this->listSize +1;
       return ptr;
    }
};

Node* insertFirst(int i, char b){    // first node in the list
    Node* ptr = new Node(i, b);     // create new node
    ptr->head = ptr;                // set the head for future nodes
    
    if (b != 't'){ 
        ptr->tail =ptr->next = new Node(i, 't');    //set the tail and next
        ptr->tail->prev = ptr;          //set the tail node prev to new node
        ptr->listSize = 1;              // set the listsize of new list
        ptr->listIndex = 1;
    }
    else{ 
        ptr->tail = ptr;   //set the tail and next
        ptr->listSize = 0;              // set the listsize of new list
        ptr->listIndex = -1;
    }
    return ptr;
}