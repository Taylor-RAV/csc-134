// CSC 134 
// M2T1 
// James Taylor 
// 3/6/2026 
#include <iostream> 
#include <iomanip>
#include <string>


using namespace std; 
int main() { 

    string username;    
    double startBalance, depositAmt, withdrawAmt, finalBalance;
    int accountNum = 12456;

// change to needed
    cout << "What is your full name?"<< endl;
    getline (cin,username);
    cout << accountNum << endl;
    cout << "what is your starting ballance?"<< endl;
    cin >> startBalance;
    cout << "What is the total dollar ammount for deposit?" << endl; 
    cin >> depositAmt;
    cout << "What is the total dollar ammount for withdrawl?" << endl; 
    cin >> withdrawAmt;
    
    // functions
    finalBalance = (startBalance + depositAmt) - withdrawAmt;

    //print 
    cout << fixed << setprecision(2);
    cout << "---------- Receipt------------" << endl;
    cout << left << setw(25) << "Customer name:" << username << endl;
    cout << left << setw(25) << "Account number:" << accountNum << endl;
    cout << left << setw(25) << "Starting ballance:" << "$" << startBalance << endl;
    cout << left << setw(25) << "Total deposits:" << "$" << depositAmt << endl;
    cout << left << setw(25) << "Total withdrawl's:" << "$" << withdrawAmt << endl;
    cout << "--------------------------------------------" << endl;
    cout << left << setw(25) << "Total:" << "$" << finalBalance << endl;
    cout << endl;
    cout << "Have a great Day!"<< endl;
    cout << endl;
    cout << endl;
return 0;
}
