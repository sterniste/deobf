#include <cctype>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

int
main(int argc, char* argv[]) {
  if (argc < 2) {
    cerr << "Usage: " << argv[0] << "obfuscated-guid [...]" << endl;
    return 1;
  }
  for (auto i = 1; i < argc; ++i) {
    char* const obf_guid = argv[i];
    auto pos = 0U;
    if (strncmp(obf_guid, "OBF:", 4) == 0)
      pos = 4;
    const auto len = strlen(obf_guid);
    if (len - pos != 144) {
      cerr << "obfuscated-guid " << i << ": not 144 chars long" << endl;
      return 1;
    }
    string deobf_guid;
    while (pos + 4 <= len) {
      const char obf_guid_c = obf_guid[pos + 4];
      obf_guid[pos + 4] = 0;
      const auto l = strtoul(obf_guid + pos, nullptr, 36);
      obf_guid[pos + 4] = obf_guid_c;
      const char deobf_guid_c = static_cast<char>(((l / 256) + (l % 256) - 254) / 2);
      if (deobf_guid.length() == 8 || deobf_guid.length() == 13 || deobf_guid.length() == 18 || deobf_guid.length() == 23) {
        if (deobf_guid_c != '-') {
          cerr << "obfuscated-guid " << i << ": invalid guid: non '-' at output pos " << deobf_guid.length() << endl;
          return 1;
        }
      } else if (!isxdigit(deobf_guid_c)) {
        cerr << "obfuscated-guid " << i << ": invalid guid: non hex digit at output pos " << deobf_guid.length() << endl;
        return 1;
      }
      deobf_guid.push_back(deobf_guid_c);
      pos += 4;
    }
    cout << deobf_guid << endl;
  }
}
