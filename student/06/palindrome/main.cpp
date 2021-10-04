#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------

  // Triviaalitapaus parittomalle sanalle
  if(s.size() == 1){
      return true;
  }
  // Triviaalitapaus parilliselle sanalle
  else if(s.size() == 2){
      if(s.front() == s.back()){
          return true;
      }
  }

  else{
      if(s.front() == s.back()){
            palindrome_recursive(s.substr(1, s.size()-2));
      }
      else{
          return false;
      }
  }
  return true;
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
