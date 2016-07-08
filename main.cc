#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int
main(int argc, char* argv[]) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << "obfuscated-string" << endl;
    return 1;
  }
  char* const obf = argv[1];
  auto pos = 0U;
  if (strncmp(obf, "OBF:", 4) == 0)
    pos = 4;
  const auto len = strlen(obf);
  if (len - pos != 144) {
    cerr << "obfuscated-string not 144 chars long!" << endl;
    return 1;
  }
  string s;
  while (pos + 4 <= len) {
    const char bufc = obf[pos + 4];
    obf[pos + 4] = 0;
    const auto l = strtoul(obf + pos, nullptr, 36);
    obf[pos + 4] = bufc;
    const auto i1 = (l / 256);
    const auto i2 = (l % 256);
    const char c = static_cast<char>((i1 + i2 - 254) / 2);
    if (!islower(c) && !isdigit(c) && c != '-') {
      cerr << "bad char in obfuscated-string, positions " << pos << '-' << (pos + 4 - 1) << endl;
      return 1;
    }
    s.push_back(c);
    pos += 4;
  }
  cout << s << endl;
}

      
  
