cmake_minimum_required(VERSION 3.8)

set(This myTest)

set(Sources 
    myTest.cpp
)

# set(Headers ../src/xxx.h)

add_executable(${This} ${Sources} ${Headers})

target_link_libraries(${This} PUBLIC
    gtest_main
    SQLiteCpp
    sqlite3
    mySqlite3
)

add_test(
    NAME ${This}
    COMMAND ${This}
)