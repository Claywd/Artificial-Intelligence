#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/time.h>
#include <vector>
#include <cctype>

using namespace std;

int main (){

    string temp;
	string line;
	ifstream ifs("ATM_graph2.txt");  // open input file

	int dataID=0;
	vector<int> num;
	string buf, word;
	bool lines =false;
	string nodeType = "n";
	int test, n, e;
    int count=0;
	bool check = true;

	while (!ifs.eof())
	{
			//if (ifs.eof()) loop = false;
			ifs >> buf;
            // cout<<buf<<"\n";
            if (buf =="v"){
                if (count >0){
                    count =1;
                    // cout<<"print the v and reset the count\n";
                    cout<<dataID<<" ";
                        for(int i=0; i<num.size(); ++i) cout<<num[i]<<" "; 
                        cout<<"\n";
                    num.erase(num.begin(), num.end());
                } 
                else count = count+1;
            }
            else if(buf == "e"){
                if (check){
                   count =1;
                   check = false;
                    // cout<<"print the v and reset the count\n";
                    cout<<dataID<<" ";
                        for(int i=0; i<num.size(); ++i) cout<<num[i]<<" "; 
                        cout<<"\n";
                    num.erase(num.begin(), num.end()); 
                }
                else{
                    if (count >0){
                        count =1;
                        cout<<dataID<<" ";
                        for(int i=0; i<num.size(); ++i) cout<<num[i] <<" "; 
                        cout<<"\n";
                        num.erase(num.begin(), num.end());
                    } 
                    else count = count+1;
                }
                
               
                // cout<<"got the e\n";
            }
            else if(count == 1){ //get id
            // cout<<"got the dataID\n";
                stringstream(buf)>>dataID;
                count =count+1;
            }
            else if(count ==2){ //get vector values
            // cout<<"got the values\n";
            stringstream(buf)>>test;
            num.push_back(test);
                // stringstream(buf)>>num[count-1];
            }
            else cout<<"***************catch case****************\n";



			

	}
    num.erase(num.end()-1); // erase the duplicate read value
    cout<<dataID<<" ";
                        for(int i=0; i<num.size(); ++i) cout<<num[i]<<" "; 
                        cout<<"\n";
	ifs.close(); 
}