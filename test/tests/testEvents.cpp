#include <gtest/gtest.h>
#include "event.hpp"

using namespace SHAMS;

TEST(ShamsEvents, SingleVoidEvent)
{
    Event event;
    bool called = false;
    event += Functions::bind([&called]()
                             { called = true; });
    event();
    ASSERT_TRUE(called);
}

TEST(ShamsEvents, SingleIntEvent)
{
    Event<int> event;
    int value = 0;
    event += Functions::bind<int>([&value](int arg)
                                  { value = arg; });
    event(10);
    ASSERT_EQ(value, 10);
}

TEST(ShamsEvents, MultipleVoidEvent)
{
    Event event;
    int count = 0;
    auto func = [&count]()
    { count++; };

    event += Functions::bind(func);
    event += Functions::bind(func);
    event += Functions::bind(func);
    event();
    ASSERT_EQ(count, 3);
}

TEST(ShamsEvents, MultipleIntEvent)
{
    Event<int> event;
    int value = 0;
    auto func = [&value](int arg)
    { value += arg; };

    event += Functions::bind<int>(func);
    event += Functions::bind<int>(func);
    event += Functions::bind<int>(func);
    event(10);
    ASSERT_EQ(value, 30);
}