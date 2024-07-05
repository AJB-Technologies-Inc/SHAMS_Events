#pragma once

#include <functional>
#include "StaticBuffer.hpp"
#include "eventHandler.hpp"

namespace SHAMS
{
    template <class argType = void, uint32_t capacity = 10>
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
            for (uint32_t i = 0; i < m_eventHandlers.size(); i++)
            {
                // m_eventHandlers[i](arg);
            }
        }

        /**
         * @brief Calls the event handlers with no arguments.
         *
         * Overload for void arguments.
         *
         */
        void operator()(void)
        {
            for (uint32_t i = 0; i < m_eventHandlers.size(); i++)
            {
                // m_eventHandlers[i]();
            }
        }

        /**
         * @brief Adds an event handler to the event.
         *
         * @param handler - The event handler to add.
         * @return Event& - The event object.
         */
        Event &operator+=(eventHandler &handler)
        {
            m_eventHandlers.insert(handler);
            return *this;
        }

        /**
         * @brief Adds an event function to the event.
         *
         * @param handler - The event function to add.
         * @return Event& - The event object.
         */
        Event &operator+=(std::function<void(argType)> handler)
        {
            // m_eventHandlers.insert(handler); //TODO
            return *this;
        }

        /**
         * @brief Removes an event handler from the event.
         *
         * @param handler - The event handler to remove.
         * @return Event& - The event object.
         */
        Event &operator-=(eventHandler &handler)
        {
            m_eventHandlers.remove(handler);
            return *this;
        }

        /**
         * @brief Removes an event function from the event.
         *
         * @param handler - The event function to remove.
         * @return Event& - The event object.
         */
        Event &operator-=(std::function<void(argType)> handler)
        {
            // m_eventHandlers.remove(handler); //TODO
            return *this;
        }

    private:
        StaticBuffer<eventHandler, capacity> m_eventHandlers;
    };

} // namespace SHAMS
