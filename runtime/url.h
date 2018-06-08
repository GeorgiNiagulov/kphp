#pragma once

#include "runtime/integer_types.h"
#include "runtime/kphp_core.h"

OrFalse <string> f$base64_decode (const string &s, bool strict = false);

string f$base64_encode (const string &s);

ULong f$base64url_decode_ulong (const string &s);

string f$base64url_encode_ulong (ULong val);

ULong f$base64url_decode_ulong_NN (const string &s);

string f$base64url_encode_ulong_NN (ULong val);


template <class T>
string f$http_build_query (const array <T> &a);

void parse_str_set_value (var &arr, const string &key, const string &value);

void f$parse_str (const string &str, var &arr);

var f$parse_url (const string &s, int component = -1);

string f$rawurldecode (const string &s);

string f$rawurlencode (const string &s);

string f$urldecode (const string &s);

string f$urlencode (const string &s);

/*
 *
 *     IMPLEMENTATION
 *
 */

template <class T>
string http_build_query_get_param_array (const string &key, const array<T> &a) {
  string result;
  int first = 1;
  for (typename array <T>::const_iterator p = a.begin(); p != a.end(); ++p) {
    if (!first) {
      result.push_back ('&');
    }
    first = 0;
    result.append (http_build_query_get_param ((static_SB.clean() << key << '[' << p.get_key() << ']').str(), p.get_value()));
  }
  return result;
}


template <class T>
string http_build_query_get_param (const string &key, const T &a) {
  if (f$is_array (a)) {
    return http_build_query_get_param_array (key, f$arrayval (a));
  } else {
    string key_encoded = f$urlencode(key);
    string value_encoded = f$urlencode(f$strval(a));
    return (static_SB.clean() << key_encoded << '=' << value_encoded).str();
  }
}


template <class T>
string f$http_build_query (const array <T> &a) {
  string result;
  int first = 1;
  for (typename array <T>::const_iterator p = a.begin(); p != a.end(); ++p) {
    string param = http_build_query_get_param (f$strval (p.get_key()), p.get_value());
    if (param.size()) {
      if (!first) {
        result.push_back ('&');
      }
      first = 0;

      result.append (param);
    }
  }

  return result;
}
