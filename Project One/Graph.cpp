#include "Graph.h"

using namespace std;


void Graph:: buildGraph(){
    //EdgeList.reserve(e);
		vList.reserve(21);

		//set all index values to the check value of -1
		for (int i=0; i<21; ++i){
			for (int j=0; j<21; ++j){
				xMap[i]=yMap[j]=-3;
				//map[i][j]=NULL;
			}
		map[i][0]=NULL;
		vList[i] = NULL;
		} 	
}

void Graph::insertVertex(int id, int x, int y){

	Vertex* vrtx = new Vertex(id);	//initialize new vertex
	Node* v;
	if (x>xMax) xMax = x;
	if (y>yMax) yMax = y;

	if (vList[x-1] == NULL){	// then this is empty and we need to create the list starting here
		vList.reserve(x);
		//dummy header
		Vertex* headV= new Vertex(-1);
		Node* header = new Node(-1, *headV);

		//dummy tail
		Vertex* tailV = new Vertex(-2);
		Node* tail = new Node(-2, *tailV);

		v = new Node(y, *vrtx, header, tail); //create first in list
		v->trailer = tail;
		v->head = header;
		header->next = v;
		tail->prev=v;

		vList.push_back(v);
		//vList[x-1] = v;
		//++vList[x]->listSize;
	}
	else v = vList[x-1]->insertNode(y, *vrtx);

		xMap[id] = x-1;
		yMap[id] = y-1;
		map[x-1][y-1] = v;
		index.push_back(v);

}

void Graph::insertEdge(int id, vector<int> edgeList){
	
	// get the node to operate on
	//Node* troll= vList[xMap[id]];
	//for (int i = 0; i<yMap[id]; ++i) troll = troll->next;

	for(int i =0; i< edgeList.size(); ++i){
		(index[id]->obj.edges).push_back(edgeList[i]);	// store the neighbor ID in the vertex neighbor vector
	}
}

void Graph::getData(string file){

	ifstream ifs(file);  // open input file

	int dataID=0;
	vector<int> num;
	string buf;
	int test, n, e;
    int count=0;
	bool check = true;

	while (!ifs.eof())
	{
			ifs >> buf;
            if (buf =="v"){	
                if (count >0){
                    count =1;
					insertVertex(dataID, num[0], num[1]);
                	num.erase(num.begin(), num.end());
                } 
                else count = count+1;
            }
            else if(buf == "e"){
                if (check){	// check for last vertex in file
                	count =1;
					insertVertex(dataID, num[0], num[1]);
					check =false;
                	num.erase(num.begin(), num.end()); 
                }
                else{
                    if (count >0){
                        count =1;
						insertEdge(dataID, num);
                        num.erase(num.begin(), num.end());
                    } 
                    else count = count+1;
                }               
            }
            else if(count == 1){ //get id
                stringstream(buf)>>dataID;
                count =count+1;
            }
            else if(count ==2){ //get vector values
            	stringstream(buf)>>test;
            	num.push_back(test);
            }
            else cout<<"***************catch case****************\n";	
	}
    num.erase(num.end()-1); // erase the duplicate read value
    insertEdge(dataID,num);
	ifs.close(); 
}