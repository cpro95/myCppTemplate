#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/lib/mySqlite3.h"
#include "nlohmann/json.hpp"
#include "rapidxml/rapidxml.hpp"
#include <string>

std::string db_filename = "../../../data/MyVideos116.db";

// TEST(myTest, getDBTotal) {
//   ASSERT_GT(getDBTotal(db_filename), 0) << "getDBTotal failed";
// }

// TEST(conanTest, getDBData) {
//   nlohmann::json json_test;
//   json_test = getDBData(db_filename, "star");
//   ASSERT_GT(json_test.size(), 0) << "getDBData failed";
// }

// std::string empty_xml = "";
// std::string poster_xml =
//     R"(<thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/30lM3Uvzs6HOG5l4hzhwxYTWgd3.jpg">http://image.tmdb.org/t/p/original/30lM3Uvzs6HOG5l4hzhwxYTWgd3.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/hndWCYJ8v3PsXnoBCzdPLLrLYgK.jpg">http://image.tmdb.org/t/p/original/hndWCYJ8v3PsXnoBCzdPLLrLYgK.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/ptURGAFktibhk7DEAbMazlmNqWa.jpg">http://image.tmdb.org/t/p/original/ptURGAFktibhk7DEAbMazlmNqWa.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/6bc9TScEkm1JIaxgbdtF8j4D2Nj.jpg">http://image.tmdb.org/t/p/original/6bc9TScEkm1JIaxgbdtF8j4D2Nj.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/1SLJHTAjhxuZAll4iGau7aCOv7a.jpg">http://image.tmdb.org/t/p/original/1SLJHTAjhxuZAll4iGau7aCOv7a.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/kpsgIevHZ4MRfySiDqP3qD3owcO.jpg">http://image.tmdb.org/t/p/original/kpsgIevHZ4MRfySiDqP3qD3owcO.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/XIweajLYpUy1REPrCdRUTl02dc.jpg">http://image.tmdb.org/t/p/original/XIweajLYpUy1REPrCdRUTl02dc.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/5UZISL85XDr9Qnm0QVBmus5SGCm.jpg">http://image.tmdb.org/t/p/original/5UZISL85XDr9Qnm0QVBmus5SGCm.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/ltJKMFWaBUZWb0vMQo5Dtaim4JQ.jpg">http://image.tmdb.org/t/p/original/ltJKMFWaBUZWb0vMQo5Dtaim4JQ.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/sIKbPTGGPkQAGiTpOUYAmFJayTF.jpg">http://image.tmdb.org/t/p/original/sIKbPTGGPkQAGiTpOUYAmFJayTF.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/wYLhXXDL3FZQ3tTHwWvHEUJYRPz.jpg">http://image.tmdb.org/t/p/original/wYLhXXDL3FZQ3tTHwWvHEUJYRPz.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/30lM3Uvzs6HOG5l4hzhwxYTWgd3.jpg">http://image.tmdb.org/t/p/original/30lM3Uvzs6HOG5l4hzhwxYTWgd3.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/hndWCYJ8v3PsXnoBCzdPLLrLYgK.jpg">http://image.tmdb.org/t/p/original/hndWCYJ8v3PsXnoBCzdPLLrLYgK.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/ptURGAFktibhk7DEAbMazlmNqWa.jpg">http://image.tmdb.org/t/p/original/ptURGAFktibhk7DEAbMazlmNqWa.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/6bc9TScEkm1JIaxgbdtF8j4D2Nj.jpg">http://image.tmdb.org/t/p/original/6bc9TScEkm1JIaxgbdtF8j4D2Nj.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/1SLJHTAjhxuZAll4iGau7aCOv7a.jpg">http://image.tmdb.org/t/p/original/1SLJHTAjhxuZAll4iGau7aCOv7a.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/kpsgIevHZ4MRfySiDqP3qD3owcO.jpg">http://image.tmdb.org/t/p/original/kpsgIevHZ4MRfySiDqP3qD3owcO.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/XIweajLYpUy1REPrCdRUTl02dc.jpg">http://image.tmdb.org/t/p/original/XIweajLYpUy1REPrCdRUTl02dc.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/5UZISL85XDr9Qnm0QVBmus5SGCm.jpg">http://image.tmdb.org/t/p/original/5UZISL85XDr9Qnm0QVBmus5SGCm.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/ltJKMFWaBUZWb0vMQo5Dtaim4JQ.jpg">http://image.tmdb.org/t/p/original/ltJKMFWaBUZWb0vMQo5Dtaim4JQ.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/sIKbPTGGPkQAGiTpOUYAmFJayTF.jpg">http://image.tmdb.org/t/p/original/sIKbPTGGPkQAGiTpOUYAmFJayTF.jpg</thumb><thumb aspect="poster" preview="http://image.tmdb.org/t/p/w500/wYLhXXDL3FZQ3tTHwWvHEUJYRPz.jpg">http://image.tmdb.org/t/p/original/wYLhXXDL3FZQ3tTHwWvHEUJYRPz.jpg</thumb>)";

// std::string fanart_xml =
//     R"(<fanart><thumb preview="http://image.tmdb.org/t/p/w780/wZsX7160l5feO646shRx3liMutx.jpg">http://image.tmdb.org/t/p/original/wZsX7160l5feO646shRx3liMutx.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/73lUS8WhDBTl9KUpZlmiiWYAH38.jpg">http://image.tmdb.org/t/p/original/73lUS8WhDBTl9KUpZlmiiWYAH38.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/a0iChedBCvYLGslDOVi1EbVjEN2.jpg">http://image.tmdb.org/t/p/original/a0iChedBCvYLGslDOVi1EbVjEN2.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/dK2HTiYwfm8OcXVdfEPT55fuyVb.jpg">http://image.tmdb.org/t/p/original/dK2HTiYwfm8OcXVdfEPT55fuyVb.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/oCWHk50Rq4UBNGXf20eX7JaXEgO.jpg">http://image.tmdb.org/t/p/original/oCWHk50Rq4UBNGXf20eX7JaXEgO.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/c553Nx5BeqE66nhEDGSl0LN5uX6.jpg">http://image.tmdb.org/t/p/original/c553Nx5BeqE66nhEDGSl0LN5uX6.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/8K2VflPQhTF7p79WC3fvl8E5oxe.jpg">http://image.tmdb.org/t/p/original/8K2VflPQhTF7p79WC3fvl8E5oxe.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/1Aru22f1LsfyMxVSmb3WNT7U3kf.jpg">http://image.tmdb.org/t/p/original/1Aru22f1LsfyMxVSmb3WNT7U3kf.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/aWRt2Hus3yoXm9POw0sf3zezVBo.jpg">http://image.tmdb.org/t/p/original/aWRt2Hus3yoXm9POw0sf3zezVBo.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/c7b10A62GySpUOfywtJGYzxhkU9.jpg">http://image.tmdb.org/t/p/original/c7b10A62GySpUOfywtJGYzxhkU9.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/zY6doHesGZCSMU23bIMEe26isqZ.jpg">http://image.tmdb.org/t/p/original/zY6doHesGZCSMU23bIMEe26isqZ.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/mmSb7ZdXpjocxqYCL4idseVhY4P.jpg">http://image.tmdb.org/t/p/original/mmSb7ZdXpjocxqYCL4idseVhY4P.jpg</thumb><thumb preview="http://image.tmdb.org/t/p/w780/ArQezJLkwHnHzuNOrBomgBAwVlj.jpg">http://image.tmdb.org/t/p/original/ArQezJLkwHnHzuNOrBomgBAwVlj.jpg</thumb></fanart>)";

// TEST(conanTest, rapidXmlTest) {
//   ASSERT_EQ(getImageUrlFromXML(empty_xml, 1), "");
//   ASSERT_EQ(getImageUrlFromXML(empty_xml, 2), "");
//   ASSERT_NE(getImageUrlFromXML(poster_xml, 1), "");
//   ASSERT_NE(getImageUrlFromXML(fanart_xml, 2), "");
// }

TEST_CASE("myCppTemplate Test 1", "getDBTotal")
{
    REQUIRE(getDBTotal(db_filename) > 0);
}

TEST_CASE("myCppTemplate Test 2", "getDBData")
{
    nlohmann::json json_test;
    json_test = getDBData(db_filename, "star");
    REQUIRE(json_test.size() > 0);
}