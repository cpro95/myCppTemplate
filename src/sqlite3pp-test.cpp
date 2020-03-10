#include <iostream>
#include <string>
#include "spdlog/spdlog.h"
#include "sqlite3pp/sqlite3pp.h"

int main() {
  spdlog::info("Sqlite3pp test");

  try {
    sqlite3pp::database db("./MyVideos107.db");

    std::string query_string =
        "select idMovie, c00, c01, c03, c08, c20, premiered, strPath, rating "
        "from movie_view where c00 like '%star%' limit 2";

    // sqlite3pp::query qry(db, "select idMovie from movie_view");
    sqlite3pp::query qry(db, query_string.c_str());

    // column name
    // for (int i = 0; i < qry.column_count(); ++i) {
    //   std::cout << qry.column_name(i) << '\t';
    // }

    // iterator  (*i).get<char const*>(j) using
    // for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
    //   for (int j = 0; j < qry.column_count(); ++j) {
    //     std::cout << (*i).get<char const*>(j) << "\t";
    //   }
    //   std::cout << std::endl;
    // }

    //   for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
    //     int id;
    //     char const *name, *phone;
    //     std::tie(id, name, phone) =
    //         (*i).get_columns<int, char const*, char const*>(0, 1, 2);
    //     std::cout << id << "\t" << name << "\t" << phone << std::endl;
    //   }

    // for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
    //   std::string idMovie, c00, c01, c03, c08, c20, premiered, strPath,
    //   rating;
    //   // (*i).getter() >> sqlite3pp::ignore >> idMovie >> c00;
    //   (*i).getter() >> idMovie >> c00 >> c01 >> c03 >> c08 >> c20 >>
    //   premiered
    //   >>
    //       strPath >> rating;
    //   std::cout << idMovie << "\t" << c00 << c08 << c20 << std::endl;
    // }

    // v is query::iterator which is rows inner class
    int total_count = 0;
    for (auto v : qry) {
      std::string idMovie, c00, c01, c03, c08, c20, premiered, strPath, rating;
      v.getter() >> sqlite3pp::ignore >> c00 >> c01;
      std::cout << "\t" << c00 << "\t" << c01 << std::endl;
      total_count++;
    }

    std::cout << "total count : " << total_count << std::endl;
  } catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
}