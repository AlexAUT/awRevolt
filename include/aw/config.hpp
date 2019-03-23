#pragma once

#if defined(__unix__)

#if defined(__linux__)

#define AW_DESKTOP
#define AW_USE_GL

#elif defined(__android__)

#define AW_ANDROID
#define AW_MOBILE
#define AW_USE_GLES

#else
#error This unix OS is not supported
#endif

#endif
