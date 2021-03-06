/**
 * @file  main.cpp
 * @brief A few short examples in a row.
 *
 *  Demonstrates how-to use the SQLite++ wrapper
 *
 * Copyright (c) 2012-2020 Sebastien Rombauts (sebastien.rombauts@gmail.com)
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "SQLiteCpp/SQLiteCpp.h"

// #ifdef SQLITECPP_ENABLE_ASSERT_HANDLER
// namespace SQLite
// {
// /// definition of the assertion handler enabled when
// SQLITECPP_ENABLE_ASSERT_HANDLER is defined in the project (CMakeList.txt)
// void assertion_failed(const char* apFile, const long apLine, const char*
// apFunc, const char* apExpr, const char* apMsg)
// {
//     // Print a message to the standard error output stream, and abort the
//     program. std::cerr << apFile << ":" << apLine << ":" << " error:
//     assertion failed (" << apExpr << ") in " << apFunc << "() with message
//     \"" << apMsg << "\"\n"; std::abort();
// }
// }
// #endif

int main() {
  std::cout << "Search Movies with..." << '\n';
  std::string search_string;
  std::cin >> search_string;
  // std::cout << query_string.length() << '\n';

  // Using SQLITE_VERSION would require #include <sqlite3.h> which we want to
  // avoid: use SQLite::VERSION if possible.
  //  std::cout << "SQlite3 version " << SQLITE_VERSION << std::endl;
  std::cout << "SQlite3 version " << SQLite::VERSION << " ("
            << SQLite::getLibVersion() << ")" << std::endl;
  std::cout << "SQliteC++ version " << SQLITECPP_VERSION << std::endl;

  ////////////////////////////////////////////////////////////////////////////
  // Simple batch queries example :
  try {
    // Open a database file in create/write mode
    SQLite::Database db("../data/MyVideos107.db", SQLite::OPEN_READONLY);
    std::cout << "SQLite database file '" << db.getFilename().c_str()
              << "' opened successfully\n";

    // Check the results : expect two row of result

    std::string query_string =
        "select idMovie, c00, c01, c03, c08, c20, premiered, strPath, rating "
        "from movie_view where c00 like '%";
    query_string += search_string;
    query_string += "%'";

    SQLite::Statement query(db, query_string);
    while (query.executeStep()) {
      std::cout << "row (" << query.getColumn(0).getType() << ", \"" << query.getColumn(1).getType()
                << "\")\n";
    }

  } catch (std::exception& e) {
    std::cout << "SQLite exception: " << e.what() << std::endl;
    return EXIT_FAILURE;  // unexpected error : exit the example program
  }

  std::cout << "everything ok, quitting\n";

  return EXIT_SUCCESS;
}
