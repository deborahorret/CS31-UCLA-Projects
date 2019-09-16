
/*  Deborah Orret
    CS 31 Spring Quarter: Project 2
    UCLA ID: 304745146
 */


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;


int main() {
    string asset_name = "";
    double value = 0;
    string category = "";
    double trustee_fee = 0;
    const double FIRST_MILLION_FEE = .013 ;
    const double NEXT_NINE_MILLION = 0.01;
    const double MUTUAL_ROYALTY_FEE = 0.002;
    const double OVER_TEN_MILLION = 0.009;
    
        cout << "Asset name: ";
        getline(cin, asset_name);
    
            if (asset_name== "") { //if they enter an empty string
                cout << "---" << endl;
                cout << "You must enter an asset name." << endl;
                return 1;
                }
    
        cout << "Value (in thousands): ";
        cin >> value;
    
            if (value < 0) { //if they enter a negative number
                cout << "---" << endl;
                cout << "The asset value must be nonnegative." << endl;
                return 1;
                }
    
        cout << "Category: ";
        string remainder = "";
        getline(cin, remainder);
        getline(cin, category);
    
            if (category == "") { //if they enter an empty string
                cout << "---" << endl;
                cout << "You must enter an asset category." << endl;
                return 1;
                }
    
    
    if (value <= 1000) {
        trustee_fee = FIRST_MILLION_FEE * value;
    }
    
    
    if (value > 1000 && value <= 10000) {
        
        if (category == "mutual fund" ||  category == "royalty") { //the special case with special const
            const int FIRST_MILLION = 1000;
            double middle;
            
            middle= value - FIRST_MILLION;
            
            trustee_fee = (FIRST_MILLION * FIRST_MILLION_FEE) + (middle * MUTUAL_ROYALTY_FEE);
        }
        else {
            const int FIRST_MILLION = 1000;
            
            double middle = value - FIRST_MILLION;
            
            trustee_fee = (FIRST_MILLION * FIRST_MILLION_FEE) + (middle * NEXT_NINE_MILLION);
        }
    }
    
    if (value > 10000) {
        if (category == "mutual fund" ||  category == "royalty") {
            const int FIRST_MILLION = 1000;
            const int MIDDLE_NINE_MILLION = 9000;
          
            double top = value - (FIRST_MILLION + MIDDLE_NINE_MILLION);
            
            trustee_fee = (FIRST_MILLION * FIRST_MILLION_FEE) + (MIDDLE_NINE_MILLION * MUTUAL_ROYALTY_FEE)
                            + (top * OVER_TEN_MILLION);
        }
        else {
            const int FIRST_MILLION = 1000;
            const int MIDDLE_NINE_MILLION = 9000;
            
            double top = value - (FIRST_MILLION + MIDDLE_NINE_MILLION);
            
            trustee_fee = (FIRST_MILLION * FIRST_MILLION_FEE) + (MIDDLE_NINE_MILLION * NEXT_NINE_MILLION) + (top * OVER_TEN_MILLION);
        }
    }
    
    double output_fee = trustee_fee * 1000; //put into dollars instea of (thousands)
    
    
    cout << "---" << endl;
    cout << "The trustee fee for " << asset_name << " is $";
    cout << fixed << setprecision(0) << output_fee << "." << endl;
    
    
    return 0;
}
