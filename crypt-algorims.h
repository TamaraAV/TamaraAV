#ifndef  CRYPT_ALGORITHMS_H
#define CRYPT_ALGORITHMS_H
#include <string>

#pragma once


#pragma warning(disable : 4996)


#include <stdio.h>
#include <cstring>

int RowColumn(char* input, char* output);
std::string RLE_enc(std::string);
std::string RLE_dec(std::string);
int Shablon(const char*, const char*, char*, char*);

#endif
