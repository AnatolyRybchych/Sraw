#pragma once
#ifndef UNICODE
    #define REQUIRED_UNICODE_UNDEF
    #define UNICODE
#endif
#include <Windows.h>
#ifdef REQUIRED_UNICODE_UNDEF
    #undef REQUIRED_UNICODE_UNDEF
    #undef UNICODE
#endif