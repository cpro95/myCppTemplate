# Example CMake file for compiling & linking a project with the the SQLiteCpp wrapper
#
# Copyright (c) 2012-2020 Sebastien Rombauts (sebastien.rombauts@gmail.com)
#
# Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
# or copy at http://opensource.org/licenses/MIT) 
cmake_minimum_required(VERSION 3.1) # for "CMAKE_CXX_STANDARD" version
project(myCppTemplate VERSION 2.0)

set(This myCppTemplate)

set(CMAKE_BUILD_TYPE Debug)

# SQLiteC++ 3.x now requires C++11 compiler
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# add_subdirectory(googletest)


# add library sqlite3
add_library(sqlite3 STATIC
    ${CMAKE_SOURCE_DIR}/external/sqlite3/sqlite3.c
    ${CMAKE_SOURCE_DIR}/external/sqlite3/sqlite3.h
)

# list of sources files of the library
set(SQLITECPP_SRC
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/src/Backup.cpp
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/src/Column.cpp
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/src/Database.cpp
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/src/Exception.cpp
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/src/Statement.cpp
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/src/Transaction.cpp
)

# list of header files of the library
set(SQLITECPP_INC
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/SQLiteCpp.h
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/Assertion.h
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/Backup.h
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/Column.h
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/Database.h
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/Exception.h
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/Statement.h
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/Transaction.h
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/VariadicBind.h
 ${PROJECT_SOURCE_DIR}/external/SQLiteCpp/include/SQLiteCpp/ExecuteMany.h
)

# add sources of the wrapper as a "SQLiteCpp" static library
add_library(SQLiteCpp STATIC ${SQLITECPP_SRC} ${SQLITECPP_INC})
target_include_directories(SQLiteCpp PUBLIC 
    ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/include
    ${CMAKE_SOURCE_DIR}/external/sqlite3
)

# Native File Dialog
# list of sources files of the library
# set(NATIVEFILEDIALOG_SRC
#     ${PROJECT_SOURCE_DIR}/external/nativefiledialog/nfd_common.c
#     ${PROJECT_SOURCE_DIR}/external/nativefiledialog/nfd_cocoa.m
# )
# list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/external/nativefiledialog/nfd_win.cpp)
# list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/external/nativefiledialog/nfd_cocoa.m)
# list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/external/nativefiledialog/nfd_gtk.c)
# message(FATAL_ERROR "Cannot detect your system, please report to https://github.com/aarcangeli/nativefiledialog-cmake/issues")
# source_group(src FILES ${NATIVEFILEDIALOG_SRC})

# list of header files of the library
# set(NATIVEFILEDIALOG_INC
#  ${PROJECT_SOURCE_DIR}/external/nativefiledialog/common.h
#  ${PROJECT_SOURCE_DIR}/external/nativefiledialog/nfd_common.h
# )
# source_group(include FILES ${NATIVEFILEDIALOG_INC})

# add sources of the wrapper as a "NativeFileDialog" static library
# add_library(nfd STATIC ${NATIVEFILEDIALOG_SRC} ${NATIVEFILEDIALOG_INC})


# add library mySqlite3
add_library(mySqlite3 STATIC
    ${CMAKE_SOURCE_DIR}/src/lib/mySqlite3.cpp
)

target_include_directories(mySqlite3
    PUBLIC
    ${PROJECT_SOURCE_DIR}/src/lib
    ${CMAKE_SOURCE_DIR}/external/SQLiteCpp/include
    ${CMAKE_SOURCE_DIR}/external
)

# Add main.cpp example source code to the executable
add_executable(${CMAKE_PROJECT_NAME} src/main.cpp)

set_target_properties(${This} PROPERTIES LINK_FLAGS "-s DISABLE_EXCEPTION_CATCHING=0")
# Link SQLiteCpp_example1 with SQLiteCpp
# When linking, library order is important.
# mySqlite3 <- SQLiteCpp <- sqlite3
target_link_libraries(${This}
    mySqlite3
    SQLiteCpp
    sqlite3
#     # nfd
#     # "-framework Foundation -framework AppKit"
)

add_subdirectory(test)