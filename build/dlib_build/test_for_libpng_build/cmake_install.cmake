<<<<<<< HEAD
# Install script for directory: /Users/aylab/Documents/Hieu/dlib-19.22/dlib/cmake_utils/test_for_libpng
=======
# Install script for directory: /Users/Hieudo/Documents/SealChipModel/dlib-19.22/dlib/cmake_utils/test_for_libpng
>>>>>>> 5dd89bd5002ef266b0bdcdcd5e900c541033bcf8

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "/Users/aylab/Documents/Hieu/SealChipModel/build/dlib_build/test_for_libpng_build/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/Users/Hieudo/Documents/SealChipModel/build/dlib_build/test_for_libpng_build/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 5dd89bd5002ef266b0bdcdcd5e900c541033bcf8
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
