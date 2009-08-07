# Copyright (c) 2009, Martin T. Sandsmark <sandsmark@samfundet.no>
# Redistribution and use is allowed according to the terms of the BSD license.
#
# - This module tries to find the ProjectM library
# Once this is done, it will define these CMake variables:
# PROJECTM_FOUND - ProjectM is available
# PROJECTM_INCLUDE_DIR - Include directory for ProjectM
# PROJECTM_LIBRARIES - Link these to use ProjectM

if (PROJECTM_INCLUDE_DIR AND PROJECTM_LIBRARIES)

  # in cache already
  set(PROJECTM_FOUND TRUE)

else (PROJECTM_INCLUDE_DIR and PROJECTM_LIBRARIES)

  find_path(PROJECTM_INCLUDE_DIR projectM.hpp PATH_SUFFIXES cdda PROJECTM)

  find_library(PROJECTM_LIBRARY NAMES projectM)

  if (PROJECTM_LIBRARY)
    set (PROJECTM_LIBRARIES ${PROJECTM_LIBRARY})
  endif (PROJECTM_LIBRARY)

  include (FindPackageHandleStandardArgs)
  find_package_handle_standard_args(PROJECTM DEFAULT_MSG
                                    PROJECTM_LIBRARIES PROJECTM_INCLUDE_DIR)

  mark_as_advanced(PROJECTM_INCLUDE_DIR PROJECTM_LIBRARY)

endif (PROJECTM_INCLUDE_DIR AND PROJECTM_LIBRARIES)
