/**
 * @file  mySqlite3.h
 * @brief A few short function about sqlite3 query
 *
 *  how-to use the Sqlite3pp wrapper
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <string>
#include "nlohmann/json.hpp"


// getImageUrlFromXML
// parser for XML
std::string getImageUrlFromXML(std::string path, unsigned int depth);


// getDBTotal
// return total count for DB
int getDBTotal(std::string db_filename);

// getDBData
// return json DB Data
nlohmann::json getDBData(std::string db_filename, std::string search_query);
