#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>  
#include <unordered_map>
#include <cmath> 
using namespace std;

int main()
{

        	int a, b, c, m; //m=no of nodes
            //declaring our resources
             vector<string> resources;
             	 resources.push_back("Telugu");
                 resources.push_back("Hindi");
                 resources.push_back("Malyalam");
                 resources.push_back("Bengali");
                 resources.push_back("English");

             
            //declaring hashmap for resources index 
            unordered_map<string,int> res;
            for (int k = 0; k < resources.size(); k++) {
                    res[resources[k]]=k;
            }
            //declaring hashmap to map logical address values to string
            unordered_map<int,string> hm;
            //taking congruence equation inputs
            try{
            cout<<"The congruence eqaution is ax=>b(modc)"<<endl;
            cout<<"Enter a value from above equation"<<endl;
            cin >> a;
            cout<<"Enter b value from above equation"<<endl;
            cin>>b;
            cout<<"Enter mod value ie c value from above equation"<<endl;
            cin>>c;
            int a1 = a, b1 = b, c1 = c;
                //finding gcd
             int rem = 1;
             string ass;
             //finding GCD and determining possibility of finding solutions
            while (c1 != 0) {
                    rem = a1 % c1;
                    a1 = c1;
                    c1 = rem;
            }
            if (b1 % a1 != 0) {
                    cout<<"Cannot find the logical address for the given congruence"<<endl;
                    return(0);
            }
            else {
                    int gcd = a1;
                    //creating group heads
                for(int i=0;i<70;i++){
                        cout<<"\u2500";
                }
                cout<<"\n"<<"Creating Group heads/Cluster heads:" <<endl;
                vector<vector<int> > groups(gcd,vector<int>(gcd,0));
                cout<<"Resourcetype"<<setw(20)<< "Logical Address"<<setw(20)<< "Ipaddress" <<"\n";
                //creates logical address and assigns randomly generated IP addresses 
                for (int t = 0, n0 = 1; t < gcd; t++) {
                        //System.out.println("hi");
                        int x = (n0 + ((c * t) / gcd));
                        groups[t][0] = x;
                        string resourcetype = resources[t];
                        
                        string ipaddress=to_string(rand() % 256) + "." + to_string(rand() %256) + "." + to_string(rand()%256) + "." + to_string(rand()%256);
                        cout<< resourcetype<<setw(24-resourcetype.size())<< groups[t][0];
                        cout<<setw(30)<< ipaddress<<endl;
                        
                }
                
                //creating peers of each cluster
                for (int t = 0, n0 = 1; t < gcd; t++) {
                    cout<<"\n";
                        for(int i=0;i<70;i++)
                        {
                        cout<<"\u2500";
                        }
                       cout<<"\n"<<"Creating nodes for cluster:";
                        cout<<groups[t][0]<<endl;
                        string resourcetype=resources[t];
                        cout<<"Values for Resource Type " <<resourcetype<<endl;
                        cout<<setw(5)<< "Logical Address"<<setw(12)<< "Value"<<endl;
                        ass = resources[t];
                        for (m = 0; m < gcd; m++) {
                            int x1 = (n0 + ((c * t) / gcd) + (m * c));
                            groups[t][m] = x1;
                            string req = ass[0] + to_string(m + 1);
                            string dis=to_string(groups[t][m]);
                            cout<<setw(5)<<dis<<setw(20)<<req<<endl;
                            hm[x1]= req;
                        }
                }
                //starting node-node or internode search
                while (1 > 0) {
                        cout<<"\n"<<"which search do you want to perform" << "\n" <<"1.Node-Node Searching" <<"\n" <<"2.Inter-Node Searching" <<"\n" << "Select the number 1 or 2"<<endl;
                        int choice;
                        cin>>choice;
                    if (choice == 1) {

                            /*node-node searching*/
                            cout<<"Enter the resource type(Telugu,Hindi..):";
                            string resourcein;
                            cin >>resourcein;
                            cout<<"Enter the value to be searched(T3,E4..):";
                            string valuein;
                            cin>>valuein;
                            int flagg = 0;
                            /*finding group to be searched from resource*/
                                int groupid = (int) res[resourcein];
                                for (int k = 0; k < groups[groupid].size(); k++) {
                                    string comp = (string) hm[groups[groupid][k]];
                                    if (comp.compare(valuein)==0) {
                                        flagg = 1;
                                        cout<<"The Requested value is found at logical address "<<groups[groupid][k]<<endl;
                                        break;
                                    }
                                }
                                if (flagg == 0) {
                                    cout<<"The Requested value is not found. Please check if the requested value is correct"<<endl;
                                }
                    }
                    else {
                            /*internode Searching*/
                            cout<<"Enter the resource type(Telugu,English...):"<<endl;
                            string resourceid;
                            cin>>resourceid;
                            cout<<"Enter the logical address of the peer(1,26,6..):"<<endl;
                            string valueid;
                            cin>>valueid;
                            cout<<"Enter the requested resource type(Telugu,English...):"<<endl;
                            string reqid;
                            cin>>reqid;
                            cout<<"Enter the value to be searched(E3,T4,B3):"<<endl;
                            string searchid;
                            cin>>searchid;
                                int headid = (int) res[resourceid];
                                int peerheadid = (int) res[reqid];
                                int h = (headid - peerheadid);
                                string comp = (string) hm[stoi(valueid)];
                                cout<<comp<<endl;

                                if (comp.compare(searchid)==0) {
                                   cout<<"Error:The Requested value is found at the same address"<<endl;
                                }
                                else {
                                    if (abs(h) > gcd / 2) {
                                        int flag = 0;
                                        for (int k = 0; k < groups[peerheadid].size(); k++) {

                                            comp = (string) hm[groups[peerheadid][k]];
                                            if (comp.compare(searchid)==0) {
                                                flag = 1;
                                                int answer = peerheadid + 1;
                                                if (h != 0) {
                                                    cout<<"The Requested value is found in group " <<answer << " at logical address " <<groups[peerheadid][k] << " in reverse searching order"<<endl;
                                                } else {
                                                    cout<<"The Requested value is found in the same group " << answer << " at logical address " << groups[peerheadid][k]<<endl;

                                                }
                                                break;
                                            }
                                        }
                                        if (flag == 0) {
                                           cout<<"Search Failed"<<endl;
                                        }
                                    }
                                    else {
                                        int flag = 0;
                                        for (int k = 0; k < groups[peerheadid].size(); k++) {

                                            comp = (string) hm[groups[peerheadid][k]];
                                            if (comp.compare(searchid)==0) {
                                                flag = 1;
                                                int answer = peerheadid + 1;
                                                if (h != 0) {
                                                    cout<<"The Requested value is found in group " <<answer<<" at logical address "<< groups[peerheadid][k] << " in forward searching order"<<endl;
                                                } else {
                                                    cout<<"The Requested value is found in the same group " << answer << " at logical address " << groups[peerheadid][k]<<endl;

                                                }
                                                break;

                                            }
                                        }
                                        if (flag == 0) {
                                            cout<<"Search Failed";
                                        }

                                    }
                                }
                        }
                        
                        cout<<"Do you want to perform another search? select y/n "<<endl;
                        string fi;
                        cin>>fi;

                        char repeatsearch = fi[0];
                        if (repeatsearch == 'n' || repeatsearch == 'N') {
                            break;
                        }
                }
            }
        }
        catch(exception e)
        {
            cout<<"Wrong Resource selected or wrong input value given please correct it"<<endl;
        }

}