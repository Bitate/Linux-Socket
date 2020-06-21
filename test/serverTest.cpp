#include <gtest/gtest.h>
#include "server.hpp"

TEST(SocketTest, bindGivenHostAndPort)
{
    Server server;

    ASSERT_TRUE(server.listenAt("localhost", 8080));
}