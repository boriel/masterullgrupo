#include "StringUtils.h"


//para hacer un split de un string
void cStringUtils::Tokenize(const string& lsStr, vector<string>& lvTokens,  const string& lsDelimiters)
{
    // Skip delimiters at beginning.
    string::size_type lLastPos = lsStr.find_first_not_of(lsDelimiters, 0);

    // Find first "non-delimiter".
    string::size_type lPos  = lsStr.find_first_of(lsDelimiters, lLastPos);

    while (string::npos != lPos || string::npos != lLastPos)
    {
        // Found a token, add it to the vector.
        lvTokens.push_back(lsStr.substr(lLastPos, lPos - lLastPos));

        // Skip delimiters.  Note the "not_of"
        lLastPos = lsStr.find_first_not_of(lsDelimiters, lPos);

        // Find next "non-delimiter"
        lPos = lsStr.find_first_of(lsDelimiters, lLastPos);
    }
}

