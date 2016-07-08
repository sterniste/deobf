#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int
main(int argc, char* argv[]) {
  char* const obf = argv[1];
  auto pos = 0U;
  if (strncmp(obf, "OBF:", 4) == 0)
    pos = 4;
  const auto len = strlen(obf);
  string s;
  while (pos + 4 <= len) {
    const char bufc = obf[pos + 4];
    obf[pos + 4] = 0;
    const auto l = strtoul(obf + pos, nullptr, 36);
    obf[pos + 4] = bufc;
    const auto i1 = (l / 256);
    const auto i2 = (l % 256);
    const char c = static_cast<char>((i1 + i2 - 254) / 2);
    s.push_back(c);
    pos += 4;
  }
  cout << s << endl;
}

      
  
