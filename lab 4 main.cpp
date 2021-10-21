#include<vector>
#include<iomanip>
#include<cstring>

#include "Crypt.h"

int main()
{
    char a[MAX][MAX]; char b[50];
    char c[MAX][MAX]{};
    char s1[2600];
    int sz = 0;

    cout << "\nEnter the line-> ";
    cin >> s1;

    sz = strlen(s1);
    cout << sz << endl;

    Code(a, s1, b,sz);
    Code(c,b,b,sz);

    return 0;
}
