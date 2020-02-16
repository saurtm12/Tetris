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
    if (s.length() == 1)
  {
      return true;
  }
  else if (s.length() == 0)
  {
      return true;
  }
  else
  {
      if (s[0] != s[s.length()-1])
          return false;
      else {
            std::string s1="";
            for (unsigned int i = 1; i<s.length()-1; i++ )
            {
                s1+=s[i];
            }
            return palindrome_recursive(s1);
      }
  }

  // Add your implementation here
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
