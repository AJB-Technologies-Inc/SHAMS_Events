#include <gtest/gtest.h>
#include "events.hpp"

TEST(EventQueue, Constructor)
{
    SHAMS::Events::initialize();
    SHAMS::Events::EventQueue eventQueue("TestQueue");
    EXPECT_EQ(eventQueue.getName(), "TestQueue");
}

TEST(EventQueue, GetId)
{
    SHAMS::Events::initialize();
    SHAMS::Events::EventQueue eventQueue("TestQueue");
    EXPECT_EQ(eventQueue.getId(), 0);
}

TEST(EventQueue, GetNextId)
{
    SHAMS::Events::initialize();
    SHAMS::Events::EventQueue eventQueue("TestQueue");
    SHAMS::Events::EventQueue eventQueue2("TestQueue2");
    EXPECT_EQ(eventQueue2.getId(), 1);
}