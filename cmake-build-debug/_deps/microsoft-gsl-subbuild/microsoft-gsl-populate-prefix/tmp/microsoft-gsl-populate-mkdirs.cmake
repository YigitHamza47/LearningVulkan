# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/yigit/Desktop/projeler/C++/LearningVulkan/cmake-build-debug/_deps/microsoft-gsl-src"
  "C:/Users/yigit/Desktop/projeler/C++/LearningVulkan/cmake-build-debug/_deps/microsoft-gsl-build"
  "C:/Users/yigit/Desktop/projeler/C++/LearningVulkan/cmake-build-debug/_deps/microsoft-gsl-subbuild/microsoft-gsl-populate-prefix"
  "C:/Users/yigit/Desktop/projeler/C++/LearningVulkan/cmake-build-debug/_deps/microsoft-gsl-subbuild/microsoft-gsl-populate-prefix/tmp"
  "C:/Users/yigit/Desktop/projeler/C++/LearningVulkan/cmake-build-debug/_deps/microsoft-gsl-subbuild/microsoft-gsl-populate-prefix/src/microsoft-gsl-populate-stamp"
  "C:/Users/yigit/Desktop/projeler/C++/LearningVulkan/cmake-build-debug/_deps/microsoft-gsl-subbuild/microsoft-gsl-populate-prefix/src"
  "C:/Users/yigit/Desktop/projeler/C++/LearningVulkan/cmake-build-debug/_deps/microsoft-gsl-subbuild/microsoft-gsl-populate-prefix/src/microsoft-gsl-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/yigit/Desktop/projeler/C++/LearningVulkan/cmake-build-debug/_deps/microsoft-gsl-subbuild/microsoft-gsl-populate-prefix/src/microsoft-gsl-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/yigit/Desktop/projeler/C++/LearningVulkan/cmake-build-debug/_deps/microsoft-gsl-subbuild/microsoft-gsl-populate-prefix/src/microsoft-gsl-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
