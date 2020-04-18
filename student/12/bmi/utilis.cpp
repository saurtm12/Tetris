#include "utilis.hh"

bool utils::is_numeric(std::string s, bool zero_allowed)
{
    if( not zero_allowed and s.length() == 1 and s.at(0) == '0' ) {
        return false;
    }
    for( unsigned int i = 0; i < s.length(); ++i ) {
        if( not isdigit(s.at(i)) ) {
            return false;
        }
    }
    return true;
}
