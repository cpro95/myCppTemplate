#include <SQLiteCpp/SQLiteCpp.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <typeindex>
#include <utility>
#include "myDB_sqlite3.h"
#include "nativefiledialog/include/nfd.h"
#include "nlohmann/json.hpp"
#include "rapidxml/rapidxml.hpp"
#include "spdlog/spdlog.h"
#include "tabulate/table.hpp"

template <class T>
constexpr std::string_view type_name() {
  using namespace std;
#ifdef __clang__
  string_view p = __PRETTY_FUNCTION__;
  return string_view(p.data() + 34, p.size() - 34 - 1);
#elif defined(__GNUC__)
  string_view p = __PRETTY_FUNCTION__;
#if __cplusplus < 201402
  return string_view(p.data() + 36, p.size() - 36 - 1);
#else
  return string_view(p.data() + 49, p.find(';', 49) - 49);
#endif
#elif defined(_MSC_VER)
  string_view p = __FUNCSIG__;
  return string_view(p.data() + 84, p.size() - 84 - 7);
#endif
}

int main() {
  // create a JSON object
    json j = {{"pi", 3.141},
              {"happy", true},
              {"name", "Niels"},
              {"이름", "김만기"},
              {"nothing", nullptr},
              {"answer", {{"everything", 42}}},
              {"list", {1, 0, 2}},
              {"object", {{"currency", "USD"}, {"value", 42.99}}}};

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

  // nfdchar_t *outPath = NULL;
  // nfdresult_t result = NFD_OpenDialog(NULL, "./data", &outPath);

  // if (result == NFD_OKAY) {
  //   spdlog::info("Opening file is success!");
  //   spdlog::info("Selected file : {}", outPath);
  //   free(outPath);
  // } else if (result == NFD_CANCEL) {
  //   spdlog::warn("User pressed cancel.");
  //   return EXIT_FAILURE;
  // } else {
  //   spdlog::critical("Error: {}\n", NFD_GetError());
  //   return EXIT_FAILURE;
  // }

  nlohmann::json movies_json = getDBData("star");

  // even easier with structured bindings (C++17)
  // for (auto &[key, value] : movies_json[0].items()) {
  std::vector<std::string> movie_struct{"idMovie", "title",     "subtitle",
                                        "summary", "premiered", "rating",
                                        "poster",  "fanart",    "strPath"};
  tabulate::Table table;
  table.add_row({"key", "values"});

  for (auto val : movie_struct) {
    table.add_row({val, movies_json[0][val]});
  }

  // for (auto &el : movies_json[0].items()) {
  // table.add_row({el.key(), el.value()});
  // }

  table[0]
      .format()
      .font_background_color(tabulate::Color::blue)
      .font_color(tabulate::Color::white);
  table[0][0].format().width(20);
  table[0][1].format().width(100);

  table.print(std::cout);
  std::cout << '\n';
  // std::string s = movies_json[0].dump();
  // std::cout << s << std::endl;

  // std::variant<int, float> v, w;
  // v = 12;  // v contains int
  // auto i = std::get<int>(v);
  // w = std::get<int>(v);
  // w = std::get<0>(v);  // same effect as the previous line
  // w = v;               // same effect as the previous line
  // auto ii = std::get<int>(w);
  //  std::get<double>(v); // error: no double in [int, float]
  //  std::get<3>(v);      // error: valid index values are 0 and 1
}