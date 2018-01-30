/******************************************************************
** Author: James Meehan
** HackerRank coin change problem solution in C++
** Input: n is the target amount, m is the number of denominations,
** the next line is the value of each coin denomination
******************************************************************/
#include <bits/stdc++.h>

using namespace std;

long getWays(long n, vector <long>& c){
    
    //sort vector of coin denominations
    sort(c.begin(), c.end());
    
    //create 2D vector table for bottom-up DP
    vector<vector<long> > table(c.size() + 1, vector<long>(n + 1));

    //initialize the first row
    for (int col = 0; col <= n; col++)
    {
        if (col == 0)
            table[0][0] = 0;
        else if (col % c[0] == 0)
            table[0][col] = 1;
        else
            table[0][col] = 0;
    }
    
    //go through and caculate each cell value from the bottom up
    for (int row = 1; row < c.size(); row++) {
        for (int col = 0; col <= n; col++) {
            //if col value is less than coin denomination value, use value stored in cell above
            //(i.e. the higher denom coin can't be used)
            if (col < c[row])  
                table[row][col] = table[row-1][col];
            //if the higher denom coin can be used you check if it goes evenly into the coin denomination for that row 
            else {
                //if it goes in evenly it will be the max of adding the value of the above row + 1 (this adds the 
                //solution of just using the higher denom coin) or the value of adding the above row (combos without
                //using the higher denom coin) + the  value in the cell of the last multiple of the current denomination
                //(combos using the higher denom coin)
                if (col % c[row] == 0)
                    table[row][col] = max((table[row-1][col] + 1), (table[row - 1][col] + table[row][col - c[row]]));
                else
                    table[row][col] = table[row - 1][col] + table[row][col - c[row]];
            }    
        }
    }
    
    //print out table for debugging
   /*for (int i = 0; i < c.size(); i++) {
        for (int j = 0; j <= n; j++)
            cout << table[i][j] << " ";
    cout << endl;
    }*/
    
    //return the last value in the last cell of the table
    return table[c.size()-1][n];
}

    

int main() {
    int n;
    int m;
    cin >> n >> m;
    vector<long> c(m);
    for(int c_i = 0; c_i < m; c_i++){
       cin >> c[c_i];
    }
    // Print the number of ways of making change for 'n' units using coins having the values given by 'c'
    long ways = getWays(n, c);
    cout << ways << endl;
    return 0;
}
