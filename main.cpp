#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <wchar.h>

#ifdef _WIN32

typedef unsigned char      dxf_bool_t;           // 8 bit
typedef char               dxf_byte_t;           // 8 bit
typedef unsigned char      dxf_ubyte_t;  // 8 bit
typedef wchar_t            dxf_char_t;           // 16 bit
//typedef unsigned wchar_t   dx_unsigned_char_t;  // 16 bit
typedef short int          dxf_short_t;          // 16 bit
typedef unsigned short int dxf_ushort_t; // 16 bit
typedef int                dxf_int_t;            // 32 bit
typedef unsigned int       dxf_uint_t;   // 32 bit
typedef float              dxf_float_t;          // 32 bit
typedef long long          dxf_long_t;           // 64 bit
typedef unsigned long long dxf_ulong_t;  // 64 bit
typedef double             dxf_double_t;         // 64 bit
typedef int                dxf_dayid_t;

/// String
typedef dxf_char_t*        dxf_string_t;

/// Const String
typedef const dxf_char_t*  dxf_const_string_t;

#else /* POSIX? */

#include <stdint.h>

/// Boolean
typedef unsigned char    dxf_bool_t;           // 8 bit

/// Byte
typedef int8_t           dxf_byte_t;           // 8 bit

/// Unsigned byte
typedef uint8_t          dxf_ubyte_t;  // 8 bit

/// Char
typedef wchar_t          dxf_char_t;           // 16 bit
//typedef unsigned wchar_t   dx_unsigned_char_t;  // 16 bit

/// Short
typedef int16_t          dxf_short_t;          // 16 bit

/// Unsigned short
typedef uint16_t         dxf_ushort_t; // 16 bit

/// Int
typedef int32_t          dxf_int_t;            // 32 bit

/// Unsigned int
typedef uint32_t         dxf_uint_t;   // 32 bit

/// Float
typedef float            dxf_float_t;          // 32 bit

/// Long
typedef int64_t          dxf_long_t;           // 64 bit

/// Unsigned long
typedef uint64_t         dxf_ulong_t;  // 64 bit

/// Double
typedef double           dxf_double_t;         // 64 bit

/// DayId
typedef int32_t          dxf_dayid_t;

/// String
typedef dxf_char_t*        dxf_string_t;

/// Const String
typedef const dxf_char_t*  dxf_const_string_t;

#endif /* _WIN32/POSIX */

dxf_int_t dx_symbol_name_hasher (dxf_const_string_t symbol_name) {
  dxf_int_t h = 0;
  size_t len = 0;
  size_t i = 0;

  len = wcslen(symbol_name);

  for (; i < len; ++i) {
    h = 37 * h + towupper(symbol_name[i]);
  }

  return h;
}

int main() {
  std::wifstream is("./symbols.txt");

  if (!is) {
    std::cerr << "Cannot open file\n";

    return 1;
  }

  std::wstring s{};
  std::unordered_map<dxf_int_t, std::vector<std::wstring>> map;

  std::size_t lines = 0;
  while (std::getline(is, s)) {
    if (s.empty()) {
      continue;
    }

    lines++;
    dxf_int_t hash = dx_symbol_name_hasher(s.c_str());

    if (auto found = map.find(hash); found != map.end()) {
      found->second.push_back(s);
    } else {
      map[hash] = {s};
    }
  }

  std::wcout << L"Lines: " << lines << ", Hashes: " << map.size() << L'\n';

  for (auto [k, v] : map) {
    std::wcout << k << L" -> ";

    for (const auto& e : v) {
      std::wcout << e << L' ';
    }

    std::wcout << L'\n';
  }
  return 0;
}
