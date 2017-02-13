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


void fillKb(queue<string>& kb, string KB){
    ifstream ifs(KB);
    while (!ifs.eof()){
        string line;
        getline(ifs, line, '\n');
        if (line[0] != '#') kb.push(line);
    }
    ifs.close();
}

int main(int argc, char **argv){
    // Argument Variables
    extern char *optarg;
    extern int optind;
    int i;
    string KB, facts;
    
    //get argument input into variables
    while((i = getopt(argc, argv, "a:b:")) != -1){
      switch(i){
        case 'a':
          KB = optarg;
          break;
        case 'b':
          facts = optarg;
          break;
      }
    }
    
    char board[3][3];

    string blank;
    string fact;
    char buf;
    int count=0;

    //set the board to blank
    for (int i=0; i<3; ++i)
        for(int j=0; j<3; ++j)
            board[i][j] = 'b';

    // read the facts and store them in the board
    for (int i=0; i<facts.length(); ++i) {
        buf = facts[i];
        if (isspace(buf)) {
            board[(fact[1]-'0')-1][(fact[2]-'0')-1] = (fact[0]);
            fact = blank;
        } 
        else {
            fact = fact + buf;
            if (count == 2) count = 0;
            else ++count;
        }
    }

    board[(fact[1]-'0')-1][(fact[2]-'0')-1] = (fact[0]);

    //check for whose turn

    int turnCheck = 0;
    string turnX = "turn_x";
    string turnO = "turn_o";
    size_t found = facts.find(turnX);
    if (found!=std::string::npos) turnCheck = 1; //turn x
    else{
        found = facts.find(turnO);
        if (found!=std::string::npos) turnCheck = 2; //turn o
    } 

    vector<string> possibleSol;
    queue<string> kb;
    fillKb(kb, KB);
    bool check = false;
    while (kb.size() != 0 && !check){
        string truth= kb.front();
        string values;
        string possible;
        string inference;        
        string turn;
        size_t foundTruth;
        kb.pop();

        if (turnCheck == 1) foundTruth = truth.find(turnX);
        else if (turnCheck == 2) foundTruth = truth.find(turnO);

        if (foundTruth != std::string::npos){ //error checking

            int numValues = (foundTruth+1)/4; // get the number of literals in the string
            string blank;

            //push literals toa  vector
            for (int i=0; i<numValues; ++i){
                for (int j=0; j<4; ++j) possible=possible + truth[j+(i*4)];
                possibleSol.push_back(possible);
                possible = blank;
            }

            //loop through vector and if all values of the vector are found in the fact then we have a winner
            vector<int> table;
            bool check = true;
            for (int i=0; i<possibleSol.size(); ++i){
                size_t foundPossible = facts.find(possibleSol[i]);
                if (foundPossible == std::string::npos){ 
                    check = false;
                    break;
                    }
                }

            //get values
            for(int i=0; i<foundTruth-1; ++i)values = values+truth[i];

            //get inference
            for(int i=foundTruth+7; i<truth.length(); ++i)inference = inference+truth[i];

            //get turn
            for(int i=foundTruth; i<foundTruth+6; ++i)turn = turn+truth[i];
            
            // cout<<"KB Truth "<<truth<<"\n";
            // cout<<"Values "<<values<<" "<<values.length()<<"\n";
            // cout<<"inference "<<inference<<" "<<inference.length()<<"\n";
            // cout<<"turn "<<turn<<" "<<turn.length()<<"\n";
            // cout<<"query "<<facts<<" "<<facts.length()<<"\n";

            size_t findValues = facts.find(values);
            size_t findTurn = facts.find(turn);

            if (check && findTurn != std::string::npos){
                for (int i=0; i<3; ++i){
                    for(int j=0; j<3; ++j)
                        cout<< board[i][j]<<" ";
                    cout<<"\n";
                    check = true;
                }
                cout<<inference<<"\n";
            break;
            }
        }        
        possibleSol.clear();
    }
return 0;
}
