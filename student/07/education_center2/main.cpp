//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------

/* Kurssikeskus
 *
 * Kuvaus: Kurssikeskus sisältää tietoja eri teemoihin kuuluvista kursseista,
 * joista tiedetään kurssin nimi, paikkakunta sekä osallistujien määrä. Tiedot
 * luetaan tiedostosta sopivaan tietorakenteeseen, jos virheitä ei ilmene.
 * Käyttäjä voi syöttää ohjelmalle eri komentoja, joilla saa kurssikeskuksesta
 * tietoja, kursseja voidaan myös poistaa.
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Minttu Niiranen
 * Opiskelijanumero: 291834
 * Käyttäjätunnus: pqmini
 * E-Mail: minttu.niiranen@tuni.fi
 *
 * */

#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

const int COURSE_FULL = 50;
const char CSV_FIELD_DELIMITER = ';';
const char INPUT_LINE_DELIMITER = ' ';

struct Course {
    std::string name;
    std::string location;
    int enrollments;
};

using CourseCenterMap = std::map<std::string, std::vector<Course>>;

// Jakaa annetun merkkijonon str annetun merkin delimiter erottelemiin osiin
// ja palauttaa osat vektorissa.
// Jos erotinmerkki on lainausmerkkien sisällä, erotinmerkistä ei välitetä,
// eli osaa olla erottelematta lainausmerkkien sisällä olevan tekstin.
//
// Splits the given string str into parts separated by the given delimiter
// and returns the parts in a vector.
// If the delimiter appears inside quatation, ignores delimiter,
// i.e. does not split quoted text.
std::vector<std::string> split_ignoring_quoted_delim(const std::string& str,
                                                     char delimiter)
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delimiter and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if(result.back() == "")
    {
        result.erase(--result.end());
    }
    return result;
}

// Funktio ottaa parametrina tiedoston nimen ja vektorin ja lukee tiedoston
//sisällön riveittäin vektoriin. Funktio palauttaa totuusarvon tapahtuman
//onnistumisesta.
bool read_input_file(const std::string& filepath,
                     std::vector<std::string>& lines){

    std::ifstream input_file_in(filepath);
    if(! input_file_in.is_open()){
        return false;
    }

    std::string line = "";
    while(std::getline(input_file_in, line)){
        lines.push_back(line);
    }
    return true;
}

// Funktio ottaa parametrina tiedoston splitatun rivin, tarkastaa kenttien
//määrän ja palauttaa totuusarvon
bool validate_field_count(const std::vector<std::string>& fields){
    if(fields.size() != 4){
        return false;
    }
    return true;
}

// Funktio ottaa parametrina tiedoston splitatun rivin, tarkastaa onko jokin
//niistä tyhjä ja palauttaa totuusarvon
bool validate_no_empty_fields(const std::vector<std::string>& fields){
    for(const auto& field : fields){
        if(field.empty()){
            return false;
        }
    }
    return true;
}

// Funktio ottaa parametrina vektorin tiedoston riveistä sekä tietorakenteen,
//johon tieto talletetaan. Funktio palauttaa totuusarvon.
bool parse_input_lines(const std::vector<std::string>& lines,
                       CourseCenterMap& courses_by_theme){

    for(const std::string& line : lines){
        std::vector<std::string> fields
                = split_ignoring_quoted_delim(line, CSV_FIELD_DELIMITER);

        if(!validate_field_count(fields)
                || !validate_no_empty_fields(fields)){
            return false;
        }

        const std::string& theme = fields.at(0);
        const std::string& name = fields.at(1);
        const std::string location = fields.at(2);
        int enrollments = 0;

        if(fields.at(3) == "full"){
            enrollments = COURSE_FULL;
        }
        else{
            std::istringstream enrollments_in(fields.at(3));
            if(!(enrollments_in >> enrollments)){
                return false;
            }
        }

        Course new_course = Course{name, location, enrollments};

        courses_by_theme.try_emplace({});

        std::vector<Course>& courses_under_theme = courses_by_theme[theme];
        auto it = courses_under_theme.begin();
        for(; it != courses_under_theme.end(); ++it){
            if(it->name == new_course.name
                    && it->location == new_course.location){
                break;
            }
        }

        if(it != courses_under_theme.end()){
            courses_under_theme.erase(it);
        }

        courses_under_theme.push_back(new_course);
    }
    return true;
}

// Funktio ottaa komennon ja sen parametrit parametrina, ja tarkastaa parametrien
//määrän. Jos määrä on virheellinen palautetaan totuusarvo epätosi, muuten tosi.
bool validate_parameter_count(std::vector<std::string>& parameters,
                              std::string& command){
    if(command == "courses" || command == "COURSES"){
        if(parameters.size() != 2){
            std::cout <<"Error: error in command "<< command << std::endl;
            return false;
        }
    }
    else if(command == "courses_in_theme" || command == "COURSES_IN_THEME"
            || command == "courses_in_location" || command == "COURSES_IN_LOCATION"
            || command == "cancel" || command == "CANCEL"){
        if(parameters.size() != 1){
            std::cout <<"Error: error in command "<< command << std::endl;
            return false;
        }
    }
    return true;
}

// Funktio ottaa parametrina komentoparametrit sekä kurssikeskuksen tiedot.
// Funktio käy läpi kurssit teemoittain ja etsii kurssia
// nimeltä. Jos kurssi löytyy funktio palauttaa totuusarvon tosi.
bool validate_course(std::vector<std::string>& parameters,
                     CourseCenterMap& courses_by_theme){

   for(const auto& pair : courses_by_theme){
       std::vector<Course> courses = pair.second;
       std::string course_name = parameters.at(0);

       auto it = courses.begin();
       for(; it != courses.end(); ++it){
           if(it->name == course_name){
               break;
           }
       }

       if(it != courses.end()){
           return true;;
       }
   }
   return false;
}

// Funktio ottaa parametrina komentoparametrit sekä kurssikeskuksen tiedot.
// Funktio etsii sijaintia kursseista ja palauttaa totuusarvon tosi, jos
// sijainti löytyy.
bool validate_location(std::vector<std::string>& parameters,
                       CourseCenterMap& courses_by_theme){

    for(const auto& pair : courses_by_theme){
        std::vector<Course> courses = pair.second;
        std::string location = parameters.at(0);

        auto it = courses.begin();
        for(; it != courses.end(); ++it){
            if(it->location == location){
                break;
            }
        }

        if(it != courses.end()){
            return true;;
        }
    }
    return false;
}

// Funktio ottaa parametrina komentoparametrit sekä kurssikeskuksen tiedot.
// Funktio etsii teemaa tiedoista ja palauttaa totuusarvon tosi, jos se löytyy.
bool validate_theme(std::vector<std::string>& parameters,
                       CourseCenterMap& courses_by_theme){

    std::string theme = parameters.back();
    auto it = courses_by_theme.begin();
    for(; it != courses_by_theme.end(); ++it){
        if(it->first == theme){
            return true;
        }
    }
    return false;
}

// Funktio ottaa parametrina funktion komentoparametrit sekä kurssikeskuksen
// tiedot. Funktio katsoo, onko teeman alla annetun paikkakunnan kursseja. Jos
// yhtään kurssia ei löydy, funktio palauttaa epätosi.
bool is_course_in_location(std::vector<std::string>& parameters,
                           CourseCenterMap& courses_by_theme){

    std::string location = parameters.at(0);
    std::string theme = parameters.at(1);

    auto it = courses_by_theme[theme].begin();
    for(; it != courses_by_theme[theme].end(); ++it){
        if(it->location == location){
            break;
        }
    }
    if(it == courses_by_theme[theme].end()){
        return false;
    }
    return true;
}

// Vertailufunktio Course structeille nimen perusteella.
bool compare_by_name (const Course& a, const Course& b){
    return a.name < b.name;
}

// Vertailufunkio Course structeille ensin sijainnen ja sitten nimen perusteella.
bool compare_by_location_by_name (const Course& a, const Course& b){
    if(a.location != b.location){
        return a.location < b.location;
    }
    return a.name< b.name;
}

// Vertailufunktio Course structeille sijainnin perusteella.
bool compare_by_location (const Course& a, const Course& b){
    return a.location < b.location;
}

// Funkiot ottaa parametrina kurssikeskuksen tiedot ja tulostaa teemat
// järjestyksessä.
void themes_command(CourseCenterMap& courses_by_theme){
    auto it = courses_by_theme.begin();
    ++it;
    for(; it != courses_by_theme.end(); ++it){
        std::cout << it->first << std::endl;
    }
}

// Funktio ottaa parametrina funktion komentoparametrit sekä kurssikeskuksen
// tiedot. Alussa on virheentarkastus ja oikeila syötteilä tulostetaan teeman
// kurssit ja osallistujamäärä annetulta paikkakunnalta järjestyksessä.
bool courses_command(std::vector<std::string>& parameters,
                     CourseCenterMap& courses_by_theme){

    if(!validate_location(parameters, courses_by_theme) &&
            !validate_theme(parameters, courses_by_theme)){
        std::cout << "Error: unknown theme" << std::endl;
        return true;
    }
    if(!validate_theme(parameters, courses_by_theme)){
        std::cout << "Error: unknown theme" << std::endl;
        return true;
    }
    if(!validate_location(parameters, courses_by_theme) ||
            !is_course_in_location(parameters, courses_by_theme)){
        std::cout << "Error: unknown location" << std::endl;
        return true;
    }

    std::string location = parameters.at(0);
    std::string theme = parameters.at(1);
    sort(courses_by_theme[theme].begin(), courses_by_theme[theme].end(),
         compare_by_name);

    for(const Course& course : courses_by_theme[theme]){
        if(course.location == location){
            if(course.enrollments == COURSE_FULL){
                std::cout<< course.name << " --- " << "full" << std::endl;
            }
            else{
            std::cout<< course.name << " --- " << course.enrollments
                     << " enrollments" << std::endl;
            }
        }
    }
    return true;
}

// Funkitio ottaa parametrina kurssikeskuksen tiedot, ja tulostaa kurssit, jotka
// eivät ole täynnä teeman, sijainnin ja nimen perusteella järjestyksessä.
void available_command(CourseCenterMap& courses_by_theme){

    for(auto& pair : courses_by_theme){
        sort(pair.second.begin(), pair.second.end(), compare_by_location_by_name);
        for(const Course& course : pair.second){
            if(course.enrollments != COURSE_FULL){
                std::cout<< pair.first << " : ";
                std::cout << course.location << " : " << course.name << std::endl;
            }
        }
    }
}

// Funktio ottaa parametrina komennon parametrit ja kurssikeskuksen tiedot.
// Funktio tulostaa kaikki teeman olevat kurssit paikan mukaan järjestyksessä.
void courses_in_theme_command(std::vector<std::string>& parameters,
                              CourseCenterMap& courses_by_theme){

    if(!validate_theme(parameters, courses_by_theme)){
        std::cout << "Error: unknown theme" << std::endl;
    }

    std::string theme = parameters.at(0);
    sort(courses_by_theme[theme].begin(), courses_by_theme[theme].end(),
         compare_by_location);
    for(const Course& course : courses_by_theme[theme]){
        std::cout << course.location << " : " << course.name << std::endl;
    }
}

// Funktio ottaa parametrina komennon parametrit ja kurssikeskuksen tiedot.
// Funktio tulostaa kaikki paikkakunnan kurssit aakkosjärjestyksessä.
void courses_in_location_command(std::vector<std::string>& parameters,
                                 CourseCenterMap& courses_by_theme){

    if(!validate_location(parameters, courses_by_theme)){
        std::cout << "Error: unknown location" << std::endl;
    }

    std::string location = parameters.at(0);
    std::vector<std::string> courses_under_location = {};
    // Talletetaan sijainnin kurssit ensin vektoriin
    for(const auto& pair : courses_by_theme){
        for(const Course& course : pair.second){
            if(course.location == location){
                courses_under_location.push_back(course.name);
            }
        }
    }

    sort(courses_under_location.begin(), courses_under_location.end());
    for(const std::string& course_name : courses_under_location){
        std::cout << course_name << std::endl;
    }
}

// Funktio ottaa parametrina kurssikeskuksen tiedot ja selvittää suosituimman/
// suosituimmat teemat osallistujamäärän perusteella.
void favorite_theme_command(CourseCenterMap& courses_by_theme){
    std::map< std::string, int> enrollments_by_theme = {};
    auto it = courses_by_theme.begin();
    for(; it != courses_by_theme.end(); ++it){
        enrollments_by_theme.try_emplace({});
        int enrollments = 0;
        for(const Course& course : it->second){
            enrollments += course.enrollments;
        }
        enrollments_by_theme[it->first] = enrollments;
    }

    if(enrollments_by_theme.empty()){
        std::cout << "No enrollments" << std::endl;
    }

    std::map< std::string, int> favorite_themes = {};
    int max_enrollments = 0;
    std::string current_favorite = "";
    for(const auto& pair : enrollments_by_theme){
        if(pair.second > max_enrollments){
            max_enrollments = pair.second;
            favorite_themes[pair.first] = max_enrollments;
            favorite_themes.erase(current_favorite);
            current_favorite = pair.first;
        }
        else if(pair.second == max_enrollments){
            favorite_themes[pair.first] = max_enrollments;
        }
    }

    std::cout << favorite_themes.begin()->second <<
                 " enrollments in themes" << std::endl;
    for(const auto& pair : favorite_themes){
        std::cout << "--- " << pair.first << std::endl;
    }
}

// Funktio ottaa parametrina komennon parametrit ja kurssikeskuksen tiedot.
// Funktio poistaa annetun kurssin kaikki toteutukset.
void cancel_command(std::vector<std::string>& parameters,
                    CourseCenterMap& courses_by_theme){

    if(!validate_course(parameters, courses_by_theme)){
       std::cout << "Error: unknown course" << std::endl;
    }

    std::string course_name = parameters.at(0);
    std::vector<std::vector<Course>::iterator> courses_to_delete = {};
    auto it = courses_by_theme.begin();
    for(; it!= courses_by_theme.end(); ++it){
        auto iter = it->second.begin();
        for(; iter != it->second.end(); ++iter){
            if(iter->name == course_name){
                courses_to_delete.push_back(iter);
            }
        }
        if(courses_to_delete.size() > 0){
            break;
        }
    }

    for(size_t i = 0; i < courses_to_delete.size(); ++i){
    courses_by_theme[it->first].erase(courses_to_delete.at(i));
    }
    std::cout << course_name << " cancelled in all locations" << std::endl;

}

// Funktio ottaa parametrina komennon ja sen parametrit sekä kurssikeskuksen
//tiedot. Funktio selvittää komennon ja kutsuu sen funktiota. Funktion paluuarvo
//on epätosi jos annetaan lopuetuskomento, muuten tosi.
bool get_command(std::string& command, std::vector<std::string>& parameters,
                 CourseCenterMap& courses_by_theme){
    if(!validate_parameter_count(parameters, command)){
        return true;
    }
    if(command == "quit" || command == "QUIT"){
        return false;
    }
    else if(command == "themes" || command == "THEMES"){
        themes_command(courses_by_theme);
    }
    else if(command == "courses" || command == "COURSES"){
        courses_command(parameters, courses_by_theme);
    }
    else if(command == "available" || command == "AVAILABLE"){
        available_command(courses_by_theme);
    }
    else if(command == "courses_in_theme" || command == "COURSES_IN_THEME"){
        courses_in_theme_command(parameters, courses_by_theme);
    }
    else if(command == "courses_in_location" || command == "COURSES_IN_LOCATION"){
        courses_in_location_command(parameters, courses_by_theme);
    }
    else if(command == "favorite_theme" || command == "FAVORITE_THEME"){
        favorite_theme_command(courses_by_theme);
    }
    else if(command == "cancel" || command == "CANCEL"){
        cancel_command(parameters, courses_by_theme);
    }
    else{
        std::cout <<"Error: Unknown command: "<< command <<std::endl;
    }
    return true;
}

int main(){
    std::string input_filepath = "";
    std::cout << "Input file: ";
    std::getline(std::cin, input_filepath);

    std::vector<std::string> input_file_lines = {};
    if(!read_input_file(input_filepath, input_file_lines)){
        std::cerr << "Error: the input file cannot be opened" << std::endl;
        return EXIT_FAILURE;
    }

    CourseCenterMap courses_by_theme = {};
    if(!parse_input_lines(input_file_lines, courses_by_theme)){
       std::cerr << "Error: empty field" << std::endl;
       return EXIT_FAILURE;
    }

    std::string input_line ="";
    while(true){
    std::cout <<"> ";
    std::getline(std::cin, input_line);

    std::vector<std::string> input_parts
            = split_ignoring_quoted_delim(input_line, INPUT_LINE_DELIMITER);
    std::string command = input_parts.at(0);
    input_parts.erase(input_parts.begin());
    std::vector<std::string> parameters = input_parts;

    if(!get_command(command, parameters, courses_by_theme)){
            return EXIT_SUCCESS;
    }
    }
    return EXIT_SUCCESS;
}

