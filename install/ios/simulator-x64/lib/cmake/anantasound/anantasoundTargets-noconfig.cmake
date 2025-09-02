#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "anantasound::anantasound_core" for configuration ""
set_property(TARGET anantasound::anantasound_core APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(anantasound::anantasound_core PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libanantasound_core.a"
  )

list(APPEND _cmake_import_check_targets anantasound::anantasound_core )
list(APPEND _cmake_import_check_files_for_anantasound::anantasound_core "${_IMPORT_PREFIX}/lib/libanantasound_core.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
