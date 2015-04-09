project(devicehub_cpp)
cmake_minimum_required(VERSION 2.8)

set(VERSION "0.0.1")

aux_source_directory(devicehub SRC_LIB_LIST)
aux_source_directory(src SRC_LIST)

cmake_policy(SET CMP0016 OLD)

add_definitions(-std=c++11)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${SRC_LIB_LIST})

add_library(devicehub SHARED ${SRC_LIB_LIST})

include_directories("${CMAKE_SOURCE_DIR}/devicehub")

SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

SET(CMAKE_BUILD_TYPE Debug)


find_package(UUID)

if(APPLE)
    cmake_policy(SET CMP0042 OLD)
    add_definitions(-ferror-limit=4)

    option(USE_STATIC_BOOST "Build with static BOOST libraries instead of dynamic" NO)
    set(Boost_USE_MULTITHREADED OFF)
    unset(Boost_INCLUDE_DIR CACHE)
    unset(Boost_LIBRARY_DIRS CACHE)
    set(BOOST_LIBRARYDIR "/usr/local/Cellar/boost/1.57.0/lib")
    set(BOOST_INCLUDE_DIRECTORIES "/usr/local/Cellar/boost/1.57.0/include")
    set(BOOST_ROOT "/usr/local/Cellar/boost/1.57.0/" CACHE PATH "")

    if(USE_STATIC_BOOST)
       unset(Boost_LIBRARIES)
       message(WARNING "Linking against boost static libraries")
       set(Boost_USE_STATIC_LIBS ON)
       find_package(Boost REQUIRED COMPONENTS regex thread-mt program_options system)
    else(USE_STATIC_BOOST)
       unset(Boost_LIBRARIES)
       message(WARNING "Linking against boost dynamic libraries")
       set(Boost_USE_STATIC_LIBS OFF)
       find_package(Boost REQUIRED COMPONENTS regex thread-mt program_options system)
    endif(USE_STATIC_BOOST)
elseif(UNIX)
    option(USE_STATIC_BOOST "Build with static BOOST libraries instead of dynamic" NO)
    set(Boost_USE_MULTITHREADED OFF)
    unset(Boost_INCLUDE_DIR CACHE)
    unset(Boost_LIBRARY_DIRS CACHE)
    set(BOOST_ROOT "/usr/lib/x86_64-linux-gnu" CACHE PATH "")

    if(USE_STATIC_BOOST)
       unset(Boost_LIBRARIES)
       message(WARNING "Linking against boost static libraries")
       set(Boost_USE_STATIC_LIBS ON)
       find_package(Boost REQUIRED COMPONENTS regex thread program_options system)
    else(USE_STATIC_BOOST)
       unset(Boost_LIBRARIES)
       message(WARNING "Linking against boost dynamic libraries")
       set(Boost_USE_STATIC_LIBS OFF)
       find_package(Boost REQUIRED COMPONENTS regex thread program_options system)
    endif(USE_STATIC_BOOST)
    target_link_libraries(${PROJECT_NAME} -luuid)
    target_link_libraries(devicehub -luuid)
endif()

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

find_package(Mosquitto)
if(MOSQUITTO_FOUND)
  include_directories(${MOSQUITTO_INCLUDE_DIRS})
  target_link_libraries (${PROJECT_NAME} ${MOSQUITTO_LIBRARIES})
  target_link_libraries (devicehub ${MOSQUITTO_LIBRARIES})
endif (MOSQUITTO_FOUND)

find_package(Mosquittopp)
if(MOSQUITTOPP_FOUND)
  include_directories(${MOSQUITTOPP_INCLUDE_DIRS})
  target_link_libraries (${PROJECT_NAME} ${MOSQUITTOPP_LIBRARIES})
  target_link_libraries (devicehub ${MOSQUITTOPP_LIBRARIES})
endif (MOSQUITTOPP_FOUND)

find_package(OpenSSL)
if(OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIRS})
  target_link_libraries (${PROJECT_NAME} ${OPENSSL_LIBRARIES})
  target_link_libraries (devicehub ${OPENSSL_LIBRARIES})
endif(OPENSSL_FOUND)

find_package(LibCURL)
if(LIBCURL_FOUND)
 include_directories(${LibCURL_INCLUDE_DIR})
 target_link_libraries(${PROJECT_NAME} ${LibCURL_LIBRARIES})
 target_link_libraries(devicehub ${LibCURL_LIBRARIES})
endif(LIBCURL_FOUND)

INSTALL(TARGETS ${PROJECT_NAME} DESTINATION bin)

if(APPLE)
elseif(UNIX)
    SET(CPACK_GENERATOR "DEB")
endif()
SET(CPACK_PACKAGE_VERSION ${VERSION})
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ionut Cotoi")
SET(CPACK_PACKAGE_VENDOR "devicehub.net")
SET(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_COMPONENTS_ALL applications libraries headers)

INCLUDE(CPack)

