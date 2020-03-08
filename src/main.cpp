#include <SQLiteCpp/SQLiteCpp.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "nativefiledialog/include/nfd.h"
#include "nfd.h"
#include "nlohmann/json.hpp"
#include "rapidxml/rapidxml.hpp"

using json = nlohmann::json;

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

  rapidxml::xml_document<> doc;
  doc.parse<0>((char *)path.c_str());
  rapidxml::xml_node<> *node = doc.first_node();
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

int main() {
  // create a JSON object
  //   json j = {{"pi", 3.141},
  //             {"happy", true},
  //             {"name", "Niels"},
  //             {"이름", "김만기"},
  //             {"nothing", nullptr},
  //             {"answer", {{"everything", 42}}},
  //             {"list", {1, 0, 2}},
  //             {"object", {{"currency", "USD"}, {"value", 42.99}}}};

  //   auto j2 = R"({
  //         "id": 1,
  //         "test": "test.com",
  //         "pi": 3.141
  //     })"_json;

  //   // add new values
  //   j["new"]["key"]["value"] = {"another", "list"};

  //   // count elements
  //   auto s = j.size();
  //   j["size"] = s;

  //   // pretty print with indent of 4 spaces
  //   std::cout << std::setw(4) << j << '\n';
  //   std::cout << j["answer"]["everything"] << '\n';
  //   std::cout << j["이름"] << '\n';

  //   std::cout << std::setw(4) << j2 << '\n';

  //   std::string s2 = j2.dump();

  //   std::cout << s2 << std::setw(4) << std::endl;

  //   // store a string in a JSON value
  //   json j_string = "제이슨 본 이즈 백";

  //   // retrieve the string value
  //   auto cpp_string = j_string.get<std::string>();
  //   // retrieve the string value (alternative when an variable already
  //   exists)
  //   std::string cpp_string2; j_string.get_to(cpp_string2);

  //   // retrieve the serialized value (explicit JSON serialization)
  //   std::string serialized_string = j_string.dump();

  //   // output of original string
  //   std::cout << cpp_string << " == " << cpp_string2
  //             << " == " << j_string.get<std::string>() << '\n';
  //   // output of serialized value
  //   std::cout << j_string << " == " << serialized_string << std::endl;

  // create an array using push_back
  //   json j;
  //   j.push_back("foo");
  //   j.push_back(1);
  //   j.push_back(true);

  //   // also use emplace_back
  //   j.emplace_back(1.78);

  //   // iterate the array
  //   for (json::iterator it = j.begin(); it != j.end(); ++it) {
  //     std::cout << *it << '\n';
  //   }

  //   // range-based for
  //   for (auto& element : j) {
  //     std::cout << element << '\n';
  //   }

  //   // getter/setter
  //   const auto tmp = j[0].get<std::string>();
  //   j[1] = 42;
  //   bool foo = j.at(2);

  //   // comparison
  //   if (j == "[\"foo\", 42, true]"_json) printf("true");  // true

  //   // other stuff
  //   j.size();   // 3 entries
  //   j.empty();  // false
  //   j.type();   // json::value_t::array
  //   j.clear();  // the array is empty again

  //   // convenience type checkers
  //   j.is_null();
  //   j.is_boolean();
  //   j.is_number();
  //   j.is_object();
  //   j.is_array();
  //   j.is_string();

  //   create an object
  //   json o;
  //   o["foo"] = 23;
  //   o["bar"] = false;
  //   o["baz"] = 3.141;

  //   also use emplace
  //   o.emplace("weather", "sunny");

  //   special iterator member functions for objects
  //   for (json::iterator it = o.begin(); it != o.end(); ++it) {
  //     std::cout << it.key() << " : " << it.value() << "\n";
  //   }

  // the same code as range for
  //   for (auto& el : o.items()) {
  //     std::cout << el.key() << " : " << el.value() << "\n";
  //   }

  // even easier with structured bindings (C++17)
  //   for (auto& [key, value] : o.items()) {
  //     std::cout << key << " : " << value << "\n";
  //   }

  // find an entry
  //   if (o.find("foo") != o.end()) {
  //     std::cout << o["foo"] << std::endl;
  //     // there is an entry with key "foo"
  //   }

  // or simpler using count()
  //   int foo_present = o.count("foo");  // 1
  //   int fob_present = o.count("fob");  // 0

  // delete an entry
  //   o.erase("foo");

  //   std::cout << o << std::setw(4) << '\n';

  ////////////////////////////////////////////////////////////////////////////
  // Native Dialog example :
  // NativeDialog::MessageDialog("Notice", "Hello World!", {"Close"}).show();

  nfdchar_t *outPath = NULL;
  nfdresult_t result = NFD_OpenDialog(NULL, "./data", &outPath);

  if (result == NFD_OKAY) {
    puts("Success!");
    puts(outPath);
    free(outPath);
  } else if (result == NFD_CANCEL) {
    puts("User pressed cancel.");
    return EXIT_FAILURE;
  } else {
    printf("Error: %s\n", NFD_GetError());
    return EXIT_FAILURE;
  }

  json movies_json;
  json movie_json;

  std::cout << "SQlite3 version " << SQLite::VERSION << " ("
            << SQLite::getLibVersion() << ")" << std::endl;
  std::cout << "SQliteC++ version " << SQLITECPP_VERSION << std::endl;

  ////////////////////////////////////////////////////////////////////////////
  // Simple batch queries example :
  try {
    // Open a database file in create/write mode
    SQLite::Database db(outPath, SQLite::OPEN_READONLY);
    std::cout << "SQLite database file '" << db.getFilename().c_str()
              << "' opened successfully\n";

    // Check the results : expect two row of result
    SQLite::Statement query(db,
                            "select idMovie, c00, c01, c03, c08, c20, "
                            "premiered, strPath, rating from "
                            "movie_view where c00 like '%star%' limit 2");
    std::cout << "select idMovie, c00, c01, c03, c08, c20, premiered, strPath, "
                 "rating from "
                 "movie_view where c00 like '%star%' limit 2 \n";
    while (query.executeStep()) {
      movie_json["idMovie"] = query.getColumn(0);
      movie_json["title"] = query.getColumn(1);
      movie_json["summary"] = query.getColumn(2);
      movie_json["subtitle"] = query.getColumn(3);
      movie_json["poster"] = getImageUrlFromXML(query.getColumn(4), 1);
      movie_json["fanart"] = getImageUrlFromXML(query.getColumn(5), 2);
      movie_json["premiered"] = query.getColumn(6);
      movie_json["strPath"] = query.getColumn(7);
      movie_json["rating"] = query.getColumn(8);
      movies_json.push_back(movie_json);
    }

  } catch (std::exception &e) {
    std::cout << "SQLite exception: " << e.what() << std::endl;
    return EXIT_FAILURE;  // unexpected error : exit the example program
  }

  std::cout << movies_json.dump(4) << '\n';
}