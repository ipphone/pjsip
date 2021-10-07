#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)

#ifndef VERSION_MAJOR
  #define VERSION_MAJOR               1
#endif

#ifndef VERSION_MINOR
  #define VERSION_MINOR               13
#endif

#ifndef VERSION_REVISION
  #define VERSION_REVISION            0
#endif

#ifndef VERSION_BUILD
  #define VERSION_BUILD               0
#endif

#define VER_FILE_DESCRIPTION_STR    "ContactPoint IP Phone SIP client implementation"
#define VER_FILE_VERSION            VERSION_MAJOR, VERSION_MINOR, VERSION_REVISION, VERSION_BUILD
#define VER_FILE_VERSION_STR        STRINGIZE(VERSION_MAJOR)        \
                                    "." STRINGIZE(VERSION_MINOR)    \
                                    "." STRINGIZE(VERSION_REVISION) \
                                    "." STRINGIZE(VERSION_BUILD)    \

#define VER_PRODUCTNAME_STR         "ContactPoint IP Phone"
#define VER_PRODUCT_VERSION         VER_FILE_VERSION
#define VER_PRODUCT_VERSION_STR     VER_FILE_VERSION_STR
#define VER_ORIGINAL_FILENAME_STR   "pjsipDll.dll"
#define VER_INTERNAL_NAME_STR       "pjsipDll.dll"
#define VER_COPYRIGHT_STR           "Copyright (C) ContactPoint 2021"

#ifdef _DEBUG
  #define VER_VER_DEBUG             VS_FF_DEBUG
#else
  #define VER_VER_DEBUG             0
#endif

#define VER_FILEOS                  VOS_NT_WINDOWS32
#define VER_FILEFLAGS               VER_VER_DEBUG
#define VER_FILETYPE                VFT_DLL
