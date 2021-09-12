#include <iostream>

using namespace std;

// Funktio laskee kertoman
unsigned long int factorial(unsigned long int n){
    if(n > 1){
        return n * factorial(n - 1);
    }
    return 1;
}

unsigned long int lottery_rows(unsigned long int balls, unsigned long int drawn_balls){
    return factorial(balls) / (factorial(balls - drawn_balls) * factorial(drawn_balls));
}

bool error_check(unsigned long int balls, unsigned long int drawn_balls){
    if (balls < 0 or drawn_balls < 0){
        cout << "The number of balls must be a positive number." << endl;
        return EXIT_FAILURE;
    }

    else if (drawn_balls > balls){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return EXIT_FAILURE;
    }

    else{
        return EXIT_SUCCESS;
    }
}

int main()
{
    unsigned long int lottery_balls = 0;
    unsigned long int drawn_balls = 0;

    cout <<"Enter the total number of lottery balls: ";
    cin >> lottery_balls;
    cout <<"Enter the number of drawn balls: ";
    cin >> drawn_balls;

    //cout << factorial(lottery_balls) << endl;

    //cout << lottery_rows(lottery_balls, drawn_balls) << endl;

    error_check(lottery_balls, drawn_balls);

    return EXIT_SUCCESS;
}
