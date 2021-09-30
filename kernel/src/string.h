#pragma once

#include <stdint.h>

#define size_t unsigned long

char *strcpy(char *s1, const char *s2);
char *strncpy(char *s1, const char *s2, size_t n);
uint32_t strcmp(const char *s1, const char *s2);
uint32_t strncmp(const char *s1, const char *s2, size_t n);
uint32_t strlen(const char *str);