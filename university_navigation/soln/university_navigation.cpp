#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    // Good luck on your final morning problem!
    // Great job getting through the semester!
    int n, m;
    cin >> n >> m;
    long long grid[m+1][n+1];

    for (int i = 0; i<=m; i++)
        grid[i][0] = 1;
    for (int i = 0; i<=n; i++)
        grid[0][i] = 1;

    for (int i = 1; i<=m; i++){
        for (int j = 1; j<=n; j++){
            long long temp = grid[i][j-1] + grid[i-1][j];
            grid[i][j] = temp % 4201337;
        }
    }
    
    cout << grid[m][n] << endl;
    return 0;
}