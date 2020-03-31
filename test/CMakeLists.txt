cmake_minimum_required(VERSION 3.8)

set(This myTest)

set(Sources 
    myTest.cpp
)

set(Headers catch.hpp)

add_executable(${This} ${Sources} ${Headers})
set_target_properties(${This} PROPERTIES LINK_FLAGS "-s DISABLE_EXCEPTION_CATCHING=0")

# When linking, library order is important.
# mySqlite3 <- SQLiteCpp <- sqlite3
target_link_libraries(${This} PUBLIC
    mySqlite3
    SQLiteCpp
    sqlite3
)

add_test(
    NAME ${This}
    COMMAND ${This}
)