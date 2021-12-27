#ifndef RED_BLUE_GRAPH_SOLVER_1_COMPILATION_INFOS_H
#define RED_BLUE_GRAPH_SOLVER_1_COMPILATION_INFOS_H

#include <string>

#ifndef NDEBUG
#define NDEBUG false
#endif
#ifndef DEBUG
#define DEBUG !NDEBUG
#endif

enum class COMPILER_TYPE
{
    GCC,
    CLANG,
    MSVC,
    MINGW,
    MINGW_W64,
    EMSCRIPTEN,
    UNKNOWN
};

#ifdef _MSC_VER
#define COMPILER COMPILER_TYPE::MSVC
#elif defined(__clang__)
#define COMPILER COMPILER_TYPE::CLANG
#elif defined(__GNUC__)
#define COMPILER COMPILER_TYPE::GCC
#elif defined(__MINGW32__)
#define COMPILER COMPILER_TYPE::MINGW
#elif defined(__MINGW64__)
#define COMPILER COMPILER_TYPE::MINGW_W64
#elif defined(__EMSCRIPTEN__)
#define COMPILER COMPILER_TYPE::EMSCRIPTEN
#else
#define COMPILER COMPILER_TYPE::UNKNOWN
#endif

std::string GET_COMPILER_NAME()
{
    switch (COMPILER)
    {
        case COMPILER_TYPE::GCC:
            return "GCC";
        case COMPILER_TYPE::CLANG:
            return "CLANG";
        case COMPILER_TYPE::MSVC:
            return "MSVC";
        case COMPILER_TYPE::MINGW:
            return "MINGW";
        case COMPILER_TYPE::MINGW_W64:
            return "MINGW_W64";
        case COMPILER_TYPE::EMSCRIPTEN:
            return "EMSCRIPTEN";
        default:
            return "UNKNOWN";
    }
}

std::string GET_OS()
{
#ifdef _WIN32
    return "Windows 32-bit";
#elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
#endif
}

std::string GET_BUILD_ARCHITECTURE()
{
#if defined(__x86_64__) || defined(_M_X64)
    return "x86_64";
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
    return "x86_32";
        #elif defined(__ARM_ARCH_2__)
        return "ARM2";
        #elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
        return "ARM3";
        #elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
        return "ARM4T";
        #elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
        return "ARM5"
        #elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
        return "ARM6T2";
        #elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
        return "ARM6";
        #elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        return "ARM7";
        #elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        return "ARM7A";
        #elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
        return "ARM7R";
        #elif defined(__ARM_ARCH_7M__)
        return "ARM7M";
        #elif defined(__ARM_ARCH_7S__)
        return "ARM7S";
        #elif defined(__aarch64__) || defined(_M_ARM64)
        return "ARM64";
        #elif defined(mips) || defined(__mips__) || defined(__mips)
        return "MIPS";
        #elif defined(__sh__)
        return "SUPERH";
        #elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
        return "POWERPC";
        #elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
        return "POWERPC64";
        #elif defined(__sparc__) || defined(__sparc)
        return "SPARC";
        #elif defined(__m68k__)
        return "M68K";
        #else
        return "UNKNOWN";
#endif
}

#endif //RED_BLUE_GRAPH_SOLVER_1_COMPILATION_INFOS_H
