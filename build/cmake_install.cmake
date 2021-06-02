<<<<<<< HEAD
# Install script for directory: /Users/aylab/Documents/Hieu/SealChipModel
=======
# Install script for directory: /Users/Hieudo/Documents/SealChipModel
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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Library/Developer/CommandLineTools/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
<<<<<<< HEAD
  include("/Users/aylab/Documents/Hieu/SealChipModel/build/dlib_build/cmake_install.cmake")
=======
  include("/Users/Hieudo/Documents/SealChipModel/build/dlib_build/cmake_install.cmake")
>>>>>>> 5dd89bd5002ef266b0bdcdcd5e900c541033bcf8

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "/Users/aylab/Documents/Hieu/SealChipModel/build/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "/Users/Hieudo/Documents/SealChipModel/build/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> 5dd89bd5002ef266b0bdcdcd5e900c541033bcf8
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
