# myCppTemplate

## Useful Cpp Library

- Sqlite3 [https://www.sqlite.org/download.html](https://www.sqlite.org/download.html)
- SQLiteCpp [https://github.com/SRombauts/SQLiteCpp](https://github.com/SRombauts/SQLiteCpp)

## Build
```bash
    ./build.sh
    or
    build.bat
```

## Build to WASM
```bash
    mkdir build2
    cd build2
    emcmake cmake ..
    emmake make
```

### Important Notes for linking wasm in CMakeLists.txt
When linking, library order is important.<br />
Target library is mySqlite3 which depends on SQLiteCpp library, and SQLiteCpp library depends on sqlite3 library.
so, CMakeLists order of target_link_libraries are

```bash
target_link_libraries(${This}
    mySqlite3
    SQLiteCpp
    sqlite3
)
```

## License
- MIT License