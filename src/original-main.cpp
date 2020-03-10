#include <iomanip>
#include <iostream>
#include <string>
#include <typeindex>
#include <utility>
#include "myDB_sqlite3.h"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"
#include "tabulate/table.hpp"

int main() {
  std::string query_string;
  std::cout << "Search Movies with..." << '\n';
  std::cin >> query_string;
  // std::cout << query_string.length() << '\n';

  nlohmann::json movies_json = getDBData(query_string);

  tabulate::Table table;

  std::vector<std::string> movie_table_names{"idMovie", "title",     "subtitle",
                                             "summary", "premiered", "rating",
                                             "poster",  "fanart",    "strPath"};

  //   for (auto val : movies_json) {
  //     for (auto val2 : val) {
  //       std::cout << val2 << std::setw(4) << '\n';
  //     }
  //   }

  // even easier with structured bindings (C++17)
  // for (auto &[key, value] : movies_json[0].items()) {
  //    table.add_row({key, value});
  // }

  for (int i = 0; i < movies_json.size(); ++i) {
    table.add_row({"key", "values"});
    for (auto val : movie_table_names) {
      table.add_row({val, movies_json[i][val]});
    }
  }

  // table styling
  for (int i = 0; i < movies_json.size(); ++i) {
    table[i * 10]
        .format()
        .font_background_color(tabulate::Color::blue)
        .font_color(tabulate::Color::white);
  }

  table[0][0].format().width(11);
  table[0][1].format().width(100);

  table.print(std::cout);
  std::cout << '\n' << "Total Count : " << movies_json.size() << '\n';

  // std::cout << movies_json.dump(4) << std::endl;
}