#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "anantasound::anantasound_core" for configuration "Release"
set_property(TARGET anantasound::anantasound_core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(anantasound::anantasound_core PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libanantasound_core.2.1.0.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libanantasound_core.2.dylib"
  )

list(APPEND _cmake_import_check_targets anantasound::anantasound_core )
list(APPEND _cmake_import_check_files_for_anantasound::anantasound_core "${_IMPORT_PREFIX}/lib/libanantasound_core.2.1.0.dylib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
