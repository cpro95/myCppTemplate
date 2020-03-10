/**
 * @file  myDB_sqlite3.h
 * @brief A few short function about sqlite3 query
 *
 *  how-to use the Sqlite3pp wrapper
 *
 * Distributed under the MIT License (MIT) (See accompanying file LICENSE.txt
 * or copy at http://opensource.org/licenses/MIT)
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "nlohmann/json.hpp"
#include "rapidxml/rapidxml.hpp"
#include "spdlog/spdlog.h"
#include "sqlite3pp/sqlite3pp.h"

std::string getImageUrlFromXML(std::string path, unsigned int depth) {
  //   std::string xml_string = movies_json[0]["c08"];
  //   rapidxml::xml_document<> doc;
  //   doc.parse<0>((char *)xml_string.c_str());
  //   rapidxml::xml_node<> *node = doc.first_node(doc.first_node()->name());
  //   std::cout << "first node's value : " << node->value() << "\n";
  //   for (rapidxml::xml_attribute<> *attr = node->first_attribute(); attr;
  //        attr = attr->next_attribute()) {
  //     std::cout << "Node foobar has attribute " << attr->name() << " ";
  //     std::cout << "with value " << attr->value() << "\n";
  //   }

  // if path which is xml data is empty!!!
  if (path.length() == 0) {
    spdlog::debug("xml is empty : args is {}", path);
    return "No Image";
  } else {
    rapidxml::xml_document<> doc;
    doc.parse<0>((char*)path.c_str());
    rapidxml::xml_node<>* node = doc.first_node();
    if (depth == 1) {
      // std::cout << node->value() << '\n';
      return node->value();
    } else if (depth == 2) {
      node = node->first_node("thumb");
      // std::cout << node->value() << '\n';
      return node->value();
    } else {
      return "No Images";
    }
  }
}

nlohmann::json getDBData(std::string search_query) {
  spdlog::info("Welcome to myCppTemplate {}.{}", 0, 1);

  nlohmann::json movies_json;
  nlohmann::json movie_json;
  nlohmann::json err_json = {
      {"idMovie", ""},  {"title", ""},  {"title", ""},  {"summary", ""},
      {"subtitle", ""}, {"poster", ""}, {"fanart", ""}, {"premiered", ""},
      {"strPath", ""},  {"rating", ""}};

  try {
    sqlite3pp::database db("./MyVideos107.db");

    std::string query_string =
        "select idMovie, c00, c01, c03, c08, c20, premiered, strPath, rating "
        "from movie_view where c00 like '%";
    query_string += search_query;
    query_string += "%'";

    spdlog::info("query: {}", query_string);

    // make query
    sqlite3pp::query qry(db, query_string.c_str());

    // v is query::iterator which is rows inner class
    // int total_count = 0;
    for (auto v : qry) {
      std::string idMovie, c00, c01, c03, c08, c20, premiered, strPath, rating;
      v.getter() >> idMovie >> c00 >> c01 >> c03 >> c08 >> c20 >> premiered >>
          strPath >> rating;

      movie_json["idMovie"] = idMovie;
      movie_json["title"] = c00;
      movie_json["summary"] = c01;
      movie_json["subtitle"] = c03;
      movie_json["poster"] = getImageUrlFromXML(c08, 1);
      movie_json["fanart"] = getImageUrlFromXML(c20, 2);
      movie_json["premiered"] = premiered;
      movie_json["strPath"] = strPath;
      movie_json["rating"] = rating;

      // total_count++;
      movies_json.push_back(movie_json);
    }

    if (movies_json.size() == 0) {
      spdlog::info("No data found");
      movies_json.push_back(err_json);
    }
  } catch (std::exception& e) {
    std::cout << "error" << '\n';
    spdlog::info("SQLite exeception: {}", e.what());
  }

  return movies_json;
}