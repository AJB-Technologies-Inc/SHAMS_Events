#include <gtest/gtest.h>
#include <shams/event.hpp>

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

TEST(ShamsEvents, SingleVoidEventWithoutBind)
{
    Event event;
    bool called = false;
    event += [&called]()
    { called = true; };
    event();
    ASSERT_TRUE(called);
}

TEST(ShamsEvents, SingleIntEventWithoutBind)
{
    Event<int> event;
    int value = 0;
    event += [&value](int arg)
    { value = arg; };
    event(10);
    ASSERT_EQ(value, 10);
}

TEST(ShamsEvents, MultipleVoidEventsWitAndWithoutBind)
{
    Event event;
    int count = 0;
    auto func = [&count]()
    { count++; };

    event += Functions::bind(func);
    event += func;
    event += Functions::bind(func);
    event();
    ASSERT_EQ(count, 3);
}

TEST(ShamsEvents, MultipleIntEventsWitAndWithoutBind)
{
    Event<int> event;
    int value = 0;
    auto func = [&value](int arg)
    { value += arg; };

    event += Functions::bind<int>(func);
    event += func;
    event += Functions::bind<int>(func);
    event(10);
    ASSERT_EQ(value, 30);
}

TEST(ShamsEvents, VerifyDefaultCapacity)
{
    Event<int> event;
    ASSERT_EQ(event.maxCapacity(), 5);
}

TEST(ShamsEvents, VerifyChangingCapacity)
{
    Event<int, 10> event;
    ASSERT_EQ(event.maxCapacity(), 10);
}

TEST(ShamsEvents, VerifyStartingSize)
{
    Event<int> event;
    ASSERT_EQ(event.size(), 0);
}

TEST(ShamsEvents, VerifySize)
{
    Event<int> event;
    event += [](int test)
    { (void)test; };
    ASSERT_EQ(event.size(), 1);
}

TEST(ShamsEvents, VerifyMaxSize)
{
    Event<int, 2> event;
    auto func = [](int test)
    { (void)test; };
    event += func;
    event += func;
    event += func;
    ASSERT_EQ(event.size(), 2);
}