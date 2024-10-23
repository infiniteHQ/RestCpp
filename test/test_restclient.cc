#include "restclient-cpp/restclient.h"
#include <gtest/gtest.h>
#include <string>

#include "tests.h"

class RestClientTest : public ::testing::Test
{
 protected:

    RestClientTest()
    {
    }

    virtual ~RestClientTest()
    {
    }

    virtual void SetUp()
    {
      RestClient::init();
    }

    virtual void TearDown()
    {
      RestClient::disable();
    }
};

// DELETE Tests
// check return code
TEST_F(RestClientTest, TestRestClientDELETECode)
{
  RestClient::Response res = RestClient::del(RestClient::TestUrl+"/delete");
  EXPECT_EQ(200, res.code);
}

// check for failure
TEST_F(RestClientTest, TestRestClientDELETEFailureCode)
{
  std::string u = RestClient::TestNonExistantUrl;
  RestClient::Response res = RestClient::del(u);
  // 6 = CURLE_COULDNT_RESOLVE_HOST
  EXPECT_EQ(6, res.code);
}

TEST_F(RestClientTest, TestRestClientDELETEHeaders)
{
  RestClient::Response res = RestClient::del(RestClient::TestUrl+"/delete");
  EXPECT_EQ("keep-alive", res.headers["Connection"]);
}

// GET Tests
TEST_F(RestClientTest, TestRestClientGETCode)
{
  RestClient::Response res = RestClient::get(RestClient::TestUrl+"/get");
  EXPECT_EQ(200, res.code);
}

TEST_F(RestClientTest, TestRestClientGETHTTP2Code)
{
  // the endpoint does a redirect now
  RestClient::Response res = RestClient::get("https://http2.golang.org");
  EXPECT_EQ(302, res.code);
}

// check for failure
TEST_F(RestClientTest, TestRestClientGETFailureCode)
{
  std::string u = RestClient::TestNonExistantUrl;
  RestClient::Response res = RestClient::get(u);
  EXPECT_EQ("Couldn't resolve host name", res.body);
  // 6 = CURLE_COULDNT_RESOLVE_HOST
  EXPECT_EQ(6, res.code);
}

TEST_F(RestClientTest, TestRestClientGETHeaders)
{
  RestClient::Response res = RestClient::get(RestClient::TestUrl+"/get");
  EXPECT_EQ("keep-alive", res.headers["Connection"]);
}

// POST Tests
// check return code
TEST_F(RestClientTest, TestRestClientPOSTCode)
{
  RestClient::Response res = RestClient::post(RestClient::TestUrl+"/post", "text/text", "data");
  EXPECT_EQ(200, res.code);
}

// check for failure
TEST_F(RestClientTest, TestRestClientPOSTFailureCode)
{
  std::string u = RestClient::TestNonExistantUrl;
  RestClient::Response res = RestClient::post(u, "text/text", "data");
  // 6 = CURLE_COULDNT_RESOLVE_HOST
  EXPECT_EQ(6, res.code);
}

TEST_F(RestClientTest, TestRestClientPOSTHeaders)
{
  RestClient::Response res = RestClient::post(RestClient::TestUrl+"/post", "text/text", "data");
  EXPECT_EQ("keep-alive", res.headers["Connection"]);
}

// PUT Tests
// check return code
TEST_F(RestClientTest, TestRestClientPUTCode)
{
  RestClient::Response res = RestClient::put(RestClient::TestUrl+"/put", "text/text", "data");
  EXPECT_EQ(200, res.code);
}

// check for failure
TEST_F(RestClientTest, TestRestClientPUTFailureCode)
{
  std::string u = RestClient::TestNonExistantUrl;
  RestClient::Response res = RestClient::put(u, "text/text", "data");
  // 6 = CURLE_COULDNT_RESOLVE_HOST
  EXPECT_EQ(6, res.code);
}

TEST_F(RestClientTest, TestRestClientPUTHeaders)
{
  RestClient::Response res = RestClient::put(RestClient::TestUrl+"/put", "text/text", "data");
  EXPECT_EQ("keep-alive", res.headers["Connection"]);
}

// PATCH Tests
// check return code
TEST_F(RestClientTest, TestRestClientPATCHCode)
{
  RestClient::Response res = RestClient::patch(RestClient::TestUrl+"/patch", "text/text", "data");
  EXPECT_EQ(200, res.code);
}

// check for failure
TEST_F(RestClientTest, TestRestClientPATCHFailureCode)
{
  std::string u = RestClient::TestNonExistantUrl;
  RestClient::Response res = RestClient::patch(u, "text/text", "data");
  // 6 = CURLE_COULDNT_RESOLVE_HOST
  EXPECT_EQ(6, res.code);
}

TEST_F(RestClientTest, TestRestClientPATCHHeaders)
{
  RestClient::Response res = RestClient::patch(RestClient::TestUrl+"/put", "text/text", "data");
  EXPECT_EQ("keep-alive", res.headers["Connection"]);
}

// OPTIONS Tests
// check return code
// Disabled as httpbin does not support options requests for now
TEST_F(RestClientTest, TestRestClientOPTIONSCode)
{
  GTEST_SKIP();
  RestClient::Response res = RestClient::options("https://api.reqbin.com/api/v1/requests");
  EXPECT_EQ(200, res.code);
}

// check for failure
TEST_F(RestClientTest, TestRestClientOPTIONSFailureCode)
{
  std::string u = RestClient::TestNonExistantUrl;
  RestClient::Response res = RestClient::options(u);
  // 6 = CURLE_COULDNT_RESOLVE_HOST
  EXPECT_EQ(6, res.code);
}

TEST_F(RestClientTest, TestRestClientOPTIONSHeaders)
{
  RestClient::Response res = RestClient::options(
      RestClient::TestUrl+"/options");
  EXPECT_EQ("keep-alive", res.headers["Connection"]);
}

TEST_F(RestClientTest, TestRestClientHeadCode)
{
  RestClient::Response res = RestClient::head(RestClient::TestUrl+"/get");
  EXPECT_EQ(200, res.code);
  EXPECT_EQ("", res.body);
}
