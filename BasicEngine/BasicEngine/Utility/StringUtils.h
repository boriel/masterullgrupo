#pragma once

#include <vector>
#include <string>
using namespace std;

class cStringUtils {
public:
	static void Tokenize(const string& lsStr, vector<string>& lvTokens,  const string& lsDelimiters);
};

