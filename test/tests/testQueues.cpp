#include <gtest/gtest.h>
#include "events.hpp"

using namespace SHAMS::Events;
using namespace testing;

class EventQueueTest : public Test
{
protected:
    void SetUp() override
    {
        initialize();
    }
};

TEST_F(EventQueueTest, Constructor)
{
    EventQueue eventQueue("TestQueue");
    EXPECT_EQ(eventQueue.getName(), "TestQueue");
}

TEST_F(EventQueueTest, GetId)
{
    EventQueue eventQueue("TestQueue");
    EXPECT_EQ(eventQueue.getId(), 0);
}

TEST_F(EventQueueTest, GetNextId)
{
    EventQueue eventQueue("TestQueue");
    EventQueue eventQueue2("TestQueue2");
    EXPECT_EQ(eventQueue2.getId(), 1);
}