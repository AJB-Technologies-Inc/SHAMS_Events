#pragma once

#include "delegate.hpp"
#include "ShamsStaticBuffer.hpp"
#include <functional>
#include <memory>

namespace SHAMS::Functions
{
    template <typename argType>
    inline auto bind(std::function<void(argType)> function) -> std::unique_ptr<ArgumentDelegate<argType>>
    {
        return std::make_unique<FunctionDelegate<argType>>(function);
    }

    inline auto bind(std::function<void()> function) -> std::unique_ptr<ArgumentDelegate<void>>
    {
        return std::make_unique<FunctionDelegate<void>>(function);
    }

    template <typename argType, class classType>
    inline auto bind(void (classType::*function)(argType), classType *instance) -> std::unique_ptr<ArgumentDelegate<argType>>
    {
        return std::make_unique<MethodDelegate<argType, classType>>(instance, function);
    }

    template <class classType>
    inline auto bind(void (classType::*function)(), classType *instance) -> std::unique_ptr<ArgumentDelegate<void>>
    {
        return std::make_unique<MethodDelegate<void, classType>>(instance, function);
    }
} // namespace SHAMS::Functions

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
    template <class argType = void, uint32_t capacity = 5>
    class Event final
    {
    public:
        Event() = default;
        ~Event() = default;

        // Delete copy and assignment constructors
        Event(const Event &) = delete;
        Event &operator=(const Event &) = delete;

        // Delete Move constructors
        Event(Event &&) = delete;
        Event &operator=(Event &&) = delete;

        uint32_t maxCapacity() const
        {
            return capacity;
        }

        uint32_t size() const
        {
            return m_eventHandlers.size();
        }

        /**
         * @brief Calls the event handlers with the given arguments.
         *
         * @param arg - The argument to pass to the event handlers.
         */
        void operator()(argType arg)
        {
            for (const auto &handler : m_eventHandlers)
            {
                handler->onChange(arg);
            }
        }

        /**
         * @brief Adds an event handler to the event.
         *
         * @param handler - The event handler to add.
         * @return Event& - The event object.
         */
        Event &operator+=(std::unique_ptr<ArgumentDelegate<argType>> &&handler)
        {
            m_eventHandlers.insert(std::move(handler));
            return *this;
        }

        /**
         * @brief Adds an event handler function to the event.
         *
         * @param handler - The event handler function to add.
         * @return Event& - The event object.
         */
        Event &operator+=(std::function<void(argType)> &&handler)
        {
            auto &&handlerDelegate = Functions::bind<argType>(handler);
            m_eventHandlers.insert(std::move(handlerDelegate));
            return *this;
        }

    private:
        StaticBuffer<std::unique_ptr<ArgumentDelegate<argType>>, capacity> m_eventHandlers;
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
    class Event<void, capacity>
    {
    public:
        Event() = default;
        ~Event() = default;

        // Delete copy and assignment constructors
        Event(const Event &) = delete;
        Event &operator=(const Event &) = delete;

        // Delete Move constructors
        Event(Event &&) = delete;
        Event &operator=(Event &&) = delete;

        uint32_t maxCapacity() const
        {
            return capacity;
        }

        uint32_t size() const
        {
            return m_eventHandlers.size();
        }

        /**
         * @brief Calls the event handlers with the given arguments.
         */
        void operator()()
        {
            for (auto &handler : m_eventHandlers)
            {
                handler->onChange();
            }
        }

        /**
         * @brief Adds an event handler to the event.
         *
         * @param handler - The event handler to add.
         * @return Event& - The event object.
         */
        Event &operator+=(std::unique_ptr<ArgumentDelegate<void>> &&handler)
        {
            m_eventHandlers.insert(std::move(handler));
            return *this;
        }

        /**
         * @brief Adds an event handler function to the event.
         *
         * @param handler - The event handler function to add.
         * @return Event& - The event object.
         */
        Event &operator+=(std::function<void()> &&handler)
        {
            auto &&handlerDelegate = Functions::bind(handler);
            m_eventHandlers.insert(std::move(handlerDelegate));
            return *this;
        }

    private:
        StaticBuffer<std::unique_ptr<ArgumentDelegate<void>>, capacity> m_eventHandlers;
    };

} // namespace SHAMS
