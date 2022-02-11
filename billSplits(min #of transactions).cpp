// SPLIT BILLS(Minimize transactions) ALGORITHM IMPLEMENTATION

// ALGORITHM:-
/*
    Transform the problem of splitting bills with minimum number of transactions to graph problem.

    Each transaction is a directed weighted edge from person who has to pay other person which will receive amount(person = vertex in a graph).

    Will create a mapping of person and its netBalance after initialization of bills.

    After that will use multi-set to store the netBalance of each person if netBalance is non-zero(zero netBalance means not part of transaction in minimized transactions).

    Person with most debit will pay to person which will have most credit.And after payment their transaction is settled. We do this to minimize # of transactions

    If after settlement, netBalance of a person becomes zero, it will no more be part of transaction.(optimization step)

    We will keep storing transaction details in a vector<string> like who has paid how much to whom.

    This will be useful to print at latter stage.
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long;

// class to implement manual comparator for multiset
class amount_compare
{
    public:
    // manual comparator function to sort on the basis of pair.second
    bool operator()(pair<string,int>person1, pair<string,int>person2)
    {
        return person1.second<person2.second;
    }
};


int main() {
    #ifndef ONLINE_JUDGE
    // displaying errors in error.txt
    freopen("Error.txt", "w", stderr);
    // getting input from input.txt
    freopen("input.txt","r",stdin);
    // writing output to output.txt
    freopen("output.txt","w",stdout);
    #endif

    ios_base::sync_with_stdio(true);
    cin.tie(NULL);
    // represent transactions as directed weighted graph between group of peoples
	int no_of_transactions;    // # of edges
	int no_of_persons;        // # of nodes(vertices)
	cin>>no_of_transactions;
	cin>>no_of_persons;

    string person1,person2;
    int amount;
    // hash map to store mapping of person to its net credit or debit in split bills
    map<string,int> netBalance;  
    // take graph input  
    while(no_of_transactions--)
    {
        cin>>person1>>person2>>amount;

        // if person1 not found in mapping, make its default mapping with netBalance = 0
        if(netBalance.find(person1)==netBalance.end()){
            netBalance[person1]=0;
        }
        // if person2 not found in mapping, make its default mapping with netBalance = 0
        if(netBalance.find(person2)==netBalance.end()){
            netBalance[person2]=0;
        }
        // if already found, make transaction 
        // person1(-amount) --> person2(+amount)
        netBalance[person1]-=amount;
        netBalance[person2]+=amount;
    }
    // ALGORITHM:- will use multi-set to pay from person having most debit to person which will have most credit
    multiset<pair<string,int>,amount_compare> st;

    // inserting pairs of {person,its net-bal} in multi-set to execute above algorithm
    for(auto p:netBalance){
        string person=p.first;
        int amount= p.second;
        if(netBalance[person]!=0)
        {
            st.insert({person,amount});
        }
    }

    // to store minimum # of transactions after bill splits
    int minimized_transactions=0;
    // stores details of transaction
    vector<string> transaction_details;
    while(!st.empty())
    {
        auto low =st.begin();
        auto high =--st.end();

        string debit_person=low->first;
        int debit_amount=low->second;

        string credit_person=high->first;
        int credit_amount=high->second;
        
        int settled_amount=min(abs(debit_amount),credit_amount);
        debit_amount+=settled_amount;
        credit_amount-=settled_amount;
        
        transaction_details.push_back(debit_person+" will pay "+to_string(settled_amount)+" to "+credit_person);
        st.erase(low);
        st.erase(high);
        
        if(debit_amount!=0)
        {
            st.insert({debit_person,debit_amount});
            
        }
        if(credit_amount!=0)
        {
            st.insert({credit_person,credit_amount});
        }
        minimized_transactions+=1;       
    }
    cout<<"Minimum number of transactions after bill splits are:- "<<minimized_transactions<<"\n\n";
    cout<<"Transactions are:-"<<"\n";
    for(string res : transaction_details){
        cout<<res<<endl;
    }
	return 0;
}