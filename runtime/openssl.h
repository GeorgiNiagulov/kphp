#pragma once

#include "runtime/kphp_core.h"

array <string> f$hash_algos (void);

string f$hash (const string &algo, const string &s, bool raw_output = false);

string f$hash_hmac (const string &algo, const string &data, const string &key, bool raw_output = false);

string f$sha1 (const string &s, bool raw_output = false);

string f$md5 (const string &s, bool raw_output = false);

string f$md5_file (const string &file_name, bool raw_output = false);

int f$crc32 (const string &s);

int f$crc32_file (const string &file_name);


bool f$openssl_public_encrypt (const string &data, string &result, const string &key);

bool f$openssl_public_encrypt (const string &data, var &result, const string &key);

bool f$openssl_private_decrypt (const string &data, string &result, const string &key);

bool f$openssl_private_decrypt (const string &data, var &result, const string &key);

OrFalse <string> f$openssl_pkey_get_private (const string &key, const string &passphrase = string());

int f$openssl_verify(const string &data, const string &signature, const string &pub_key_id);

OrFalse <string> f$openssl_random_pseudo_bytes (int length);

void openssl_init_static_once (void);

void openssl_init_static (void);

void openssl_free_static (void);
