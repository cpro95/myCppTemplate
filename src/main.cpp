#include <iomanip>
#include <iostream>
#include <string>
#include <typeindex>
#include <utility>
#include "CLI/CLI.hpp"
#include "lib/mySqlite3.h"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"
#include "tabulate/table.hpp"

void make_Table(tabulate::Table& table, nlohmann::json& movies_json) {
  const uint movie_table_size = 12;
  std::vector<std::string> movie_table_names{
      "idMovie", "c00",       "c01",     "c03",    "c08",           "c19",
      "c20",     "premiered", "strPath", "rating", "uniqueid_value"};

  // code snippet
  // for (auto val : movies_json) {
  //   for (auto val2 : val) {
  //     std::cout << val2 << std::setw(4) << '\n';
  //   }
  // }

  // even easier with structured bindings (C++17)
  // for (auto& [key, value] : movies_json[0].items()) {
  //   table.add_row({key, value});
  // }

  for (int i = 0; i < movies_json.size(); ++i) {
    table.add_row({"key", "values"});
    for (auto val : movie_table_names) {
      table.add_row({val, movies_json[i][val].dump()});
    }
  }

  // table style
  for (int i = 0; i < movies_json.size(); ++i) {
    table[i * movie_table_size]
        .format()
        .font_background_color(tabulate::Color::blue)
        .font_color(tabulate::Color::white);
  }
  // table width
  table[0][0].format().width(11);
  table[0][1].format().width(100);
}

/*
 *
 *
 *
 main function
 *
 *
 *
 */
int main(int argc, char** argv) {
  CLI::App app;

  std::string query_string;
  std::string output_filename;
  bool search_all{false};
  bool count_all{false};
  std::string db_filename;
  app.add_option("-d", db_filename, "DB File what you want to open")
      ->required();
  app.add_flag("-a", search_all, "Search All Data!");
  app.add_flag("-c", count_all, "Check the total number!");
  app.add_option("-s", query_string, "Input your search query!");
  app.add_option("-f", output_filename, "Export to JSON file");
  CLI11_PARSE(app, argc, argv);

  spdlog::info("Search Movies with...");

  if (count_all) {
    spdlog::info("Total Count : {}", getDBTotal(db_filename));
    exit(0);
  }

  if (search_all) {
    spdlog::info("Search All Data!");
    query_string = "";
  }

  nlohmann::json movies_json = getDBData(db_filename, query_string);

  if (output_filename.length() == 0) {
    tabulate::Table table;
    make_Table(table, movies_json);
    table.print(std::cout);
  } else {
    std::ofstream o(output_filename);
    o << movies_json.dump(2) << std::endl;
    spdlog::info("Exporting to JSON is complete : {}", output_filename);
  }
  spdlog::info("Total Count : {}", movies_json.size());
  // fmt::print("Total Count : {}", movies_json.size());
}