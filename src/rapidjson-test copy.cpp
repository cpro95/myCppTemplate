#include <cstdio>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

using namespace rapidjson;
using namespace std;

int main(int, char* []) {
  // 1. Parse a JSON text string to a document
  const char json[] =
      " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, "
      "\"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
  printf("Original JSON:\n %s\n", json);

  Document document;  // Default template uses UTF8 and MemoryPoolAllocator

#if 0
    // "normal" parsing, decode strings to new buffers. Can use other input stream via ParseStream().
    if (document.Parse(json).HasParseError())
        return 1;
#else
  // In-situ parsing, decode strings directly in the source string. Source must
  // be string.
  char buffer[sizeof(json)];
  memcpy(buffer, json, sizeof(json));
  if (document.ParseInsitu(buffer).HasParseError()) return 1;
#endif

  printf("\nParsing to document succeeded.\n");

  ////////////////////////////////////////////////////////////////////////////
  // 2. Access values in document.

  printf("\nAccess values in document:\n");
  assert(document.IsObject());
  assert(document.HasMember("hello"));
  assert(document["hello"].IsString());
  printf("hello = %s\n", document["hello"].GetString());

  // Since version 0.2, you can use single lookup to check the exisitin of member and its value
  Value::MemberIterator hello = document.FindMember("hello");
  assert(hello != document.MemberEnd());
  assert(hello->value.IsString());
  assert(strcmp("world", hello->value.GetString()) == 0);
  (void)hello;

  assert(document["t"].IsBool());
  printf("t = %s\n", document["t"].GetBool() ? "true" : "false");
}