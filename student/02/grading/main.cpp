#include <iostream>

using namespace std;

// Before passing automated tests, do not touch the values of the following
// constants, even if they differ from those you see in Plussa.
// At the end of the course, if you use this program to count your final grade,
// you should update the constants to make them identical with those in Plussa.
unsigned int MAX_N_POINTS = 790;
unsigned int MAX_G_POINTS = 120;

unsigned weekly_excercise_score(unsigned int n, unsigned int g){
    float n_points = (n * 100) / MAX_N_POINTS;
    float n_and_g_points = ((n + g) * 100) / (MAX_N_POINTS + MAX_G_POINTS);
    float best_score = max(n_points, n_and_g_points);
    if(best_score < 50.0) return 0;
    if(best_score < 60.0) return 1;
    if(best_score < 70.0) return 2;
    if(best_score < 80.0) return 3;
    if(best_score < 90.0) return 4;
    return 5;
}

unsigned gui_excercise_score(unsigned g){
    float g_percentage = (g * 100) / MAX_G_POINTS;
    if(g_percentage < 30.0) return 2;
    if(g_percentage < 40.0) return 3;
    if(g_percentage < 50.0) return 4;
    return 5;
}

unsigned project_points_score(unsigned p){
    if(p < 51) return 0;
    if(p < 75) return 1;
    if(p < 125) return 2;
    if(p < 150) return 3;
    if(p < 175) return 4;
    return 5;
}

unsigned rounded_number(float fp){
    unsigned rounded_value = static_cast<unsigned>(fp);
    if(fp - rounded_value > 0.5){
        return (rounded_value + 1);
    }
    return rounded_value;
}

unsigned final_grade(float mean, unsigned g){
    unsigned rounded_mean = rounded_number(mean);
    if (rounded_mean < 3){
        return rounded_mean;
    }
    if (rounded_mean < 4 and g >= 3){
        return rounded_mean;
    }
    if (rounded_mean < 5 and g >= 4){
        return rounded_mean;
    }
    if (rounded_mean < 4 and g >= 5){
        return rounded_mean;
    }
    if (rounded_mean == 5 and g == 5){
        return rounded_mean;
    }
    return g;
}


int main(){

    unsigned int n = 0;
    unsigned int g = 0;
    unsigned int p = 0;
    unsigned int e = 0;
    cout << "Enter N points, G points, P points: ";
    cin >> n;
    cin >> g;
    cin >> p;
    cout << "Enter exam grade (if no exam, enter zero): ";
    cin >> e;

    float mean = 0.0;
    int score_w = weekly_excercise_score(n, g);
    int score_p = project_points_score(p);

    if (score_w == 0 or score_p == 0){
        cout <<"The final grade is 0" << endl;
        return 0;
    }

    if (e == 0){
        mean = ((score_p + score_w) / 2.0 )- 2.0;
    }

    else{
        mean = (score_p + score_w + e) / 3.0;
    }

    cout <<"The final grade is "<< final_grade(mean, gui_excercise_score(g)) << endl;

    return 0;
}
