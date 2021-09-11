#include <iostream>

using namespace std;

int main()
{
    int n = 0;
    cout << "Enter a number: " ;
    cin >> n;

    int cube = n * n * n;

    //Virhetarkistus, onko kuution laskemisessa tullut ylivuotoa
    if (cube / n / n != n){
        cout << "Error! The cube of " << n << " is not " << cube <<"." << endl;
        return 1;
    }

    cout << "The cube of " << 2 << " is " << cube << "." << endl;

    return 0;
}
