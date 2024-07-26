#pragma once

#if defined(_WIN32)
#   define PLATFORM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
#   define PLATFORM_MACOS
#endif
