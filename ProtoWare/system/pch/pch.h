#pragma once
#define UNICODE
#define _CRT_SECURE_NO_WARNING
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS 
#define DIRECTINPUT_VERSION 0x0800
#define NOMINMAX

#include <windows.h>
#include <iostream>
#include <fstream>

#include <dinput.h>
#include <chrono>

typedef char  sbyte;
typedef unsigned char  byte;
typedef __int16  int16;
typedef unsigned __int16  uint16;
typedef int  int32;
typedef unsigned int  uint32;
typedef unsigned __int64  uintptr;
typedef __int64  intptr;

#define deffor(iterator_name, count) for(int iterator_name = 0; iterator_name < count; iterator_name++)
#define revfor(iterator_name, count) for(int iterator_name = count - 1; iterator_name >= 0; iterator_name--)
#define simple_thread(method, stack_size) CreateThread(0, stack_size, (LPTHREAD_START_ROUTINE)method, 0, 0, 0);
#define isptrvalid(ptr) (ptr > 0x3000000 && ptr < 0x7FFFFFFFFFFF)
#define isptrinvalid(ptr) (ptr <= 0x3000000 || ptr >= 0x7FFFFFFFFFFF)