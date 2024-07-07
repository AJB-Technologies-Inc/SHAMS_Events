#pragma once

#include <functional>
#include "StaticBuffer.hpp"
#include "delegate.hpp"

namespace SHAMS
{
    /**
     * @brief Event class that takes an argument.
     *
     * This class allows users to register delegates that take an argument.
     * When the event is called, all the registered delegates are called with the given argument.
     *
     * @tparam argType - The type of the argument.
     * @tparam capacity - The capacity of the event handlers.
     */
    template <class argType, uint32_t capacity>
    class Event final
    {
    public:
        Event() = default;
        ~Event() = default;

        /**
         * @brief Calls the event handlers with the given arguments.
         *
         * @param arg - The argument to pass to the event handlers.
         */
        void operator()(argType arg)
        {
            for (const auto &handler : m_eventHandlers)
            {
                handler(arg);
            }
        }

        /**
         * @brief Adds an event handler to the event.
         *
         * @param handler - The event handler to add.
         * @return Event& - The event object.
         */
        Event &operator+=(DelegateBase &handler)
        {
            m_eventHandlers.insert(handler);
            return *this;
        }

        /**
         * @brief Removes an event handler from the event.
         *
         * @param handler - The event handler to remove.
         * @return Event& - The event object.
         */
        Event &operator-=(DelegateBase &handler)
        {
            m_eventHandlers.remove(handler);
            return *this;
        }

    private:
        StaticBuffer<DelegateBase, capacity> m_eventHandlers;
    };

    /**
     * @brief Event class that takes no arguments.
     *
     * This class allows users to register delegates that take no arguments.
     * When the event is called, all the registered delegates are called.
     *
     * @tparam capacity - The capacity of the event handlers.
     */
    template <uint32_t capacity>
    class Event<void, capacity> final
    {
    public:
        Event() = default;
        ~Event() = default;

        /**
         * @brief Calls the event handlers with the given arguments.
         */
        void operator()()
        {
            for (const auto &handler : m_eventHandlers)
            {
                handler();
            }
        }

        /**
         * @brief Adds an event handler to the event.
         *
         * @param handler - The event handler to add.
         * @return Event& - The event object.
         */
        Event &operator+=(DelegateBase &handler)
        {
            m_eventHandlers.insert(handler);
            return *this;
        }

        /**
         * @brief Removes an event handler from the event.
         *
         * @param handler - The event handler to remove.
         * @return Event& - The event object.
         */
        Event &operator-=(DelegateBase &handler)
        {
            m_eventHandlers.remove(handler);
            return *this;
        }

    private:
        StaticBuffer<DelegateBase, capacity> m_eventHandlers;
    };

    template <typename argType>
    FunctionDelegate<argType> bind(std::function<void(argType)> function)
    {
        return FunctionDelegate<argType>(function);
    }

} // namespace SHAMS
