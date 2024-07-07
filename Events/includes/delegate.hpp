#pragma once

#include <functional>

namespace SHAMS
{

    /**
     * @brief Delegate class that takes an argument.
     *
     * @tparam argType - The type of the argument.
     */
    template <typename argType>
    class ArgumentDelegate
    {
    public:
        ArgumentDelegate() = default;
        virtual ~ArgumentDelegate() = default;
        virtual void onChange(argType arg) = 0;
    };

    /**
     * @brief Delegate class that takes no arguments.
     *
     * Specialization for void arguments, ie. no arguments.
     */
    template <>
    class ArgumentDelegate<void>
    {
    public:
        ArgumentDelegate() = default;
        virtual ~ArgumentDelegate() = default;
        virtual void onChange() = 0;
    };

    /**
     * @brief Delegate class that takes a function with an argument.
     *
     * @tparam argType - The type of the argument.
     */
    template <typename argType>
    class FunctionDelegate : public ArgumentDelegate<argType>
    {
    public:
        /**
         * @brief Construct a new Function Delegate object
         *
         * @param function - The function to call.
         */
        FunctionDelegate(std::function<void(argType)> function) : m_function{function}
        {
        }

        /**
         * @brief Calls the function with the given argument.
         *
         * @param arg - The argument to pass to the function.
         */
        void onChange(argType arg) override
        {
            m_function(arg);
        }

    private:
        std::function<void(argType)> m_function;
    };

    /**
     * @brief Delegate class that takes a function with no arguments.
     *
     * Specialization for void arguments, ie. no arguments.
     */
    template <>
    class FunctionDelegate<void> : public ArgumentDelegate<void>
    {
    public:
        /**
         * @brief Construct a new Function Delegate object
         *
         * @param function - The function to call.
         */
        FunctionDelegate(std::function<void()> function) : m_function{function}
        {
        }

        /**
         * @brief Calls the function with no arguments.
         *
         */
        void onChange() override
        {
            m_function();
        }

    private:
        std::function<void()> m_function;
    };

    /**
     * @brief Delegate class that takes a class method with an argument.
     *
     * @tparam argType - The type of the argument.
     * @tparam classType - The type of the class.
     */
    template <typename argType, class classType>
    class MethodDelegate : public ArgumentDelegate<argType>
    {

    public:
        /**
         * @brief Construct a new Method Delegate object
         *
         * @param instance - The instance of the class.
         * @param method - The method to call.
         */
        MethodDelegate(classType *instance, void (classType::*method)(argType))
            : m_instance{instance}, m_method{method}
        {
        }

        void onChange(argType arg) override
        {
            (m_instance->*m_method)(arg);
        }

    private:
        classType *m_instance;
        void (classType::*m_method)(argType);
    };

    /**
     * @brief Delegate class that takes a class method with no arguments.
     *
     * Specialization for void arguments, ie. no arguments.
     *
     * @tparam classType - The type of the class.
     */
    template <class classType>
    class MethodDelegate<void, classType> : public ArgumentDelegate<void>
    {

    public:
        /**
         * @brief Construct a new Method Delegate object
         *
         * @param instance - The instance of the class.
         * @param method - The method to call.
         */
        MethodDelegate(classType *instance, void (classType::*method)())
            : m_instance{instance}, m_method{method}
        {
        }

        void onChange() override
        {
            (m_instance->*m_method)();
        }

    private:
        classType *m_instance;
        void (classType::*m_method)();
    };

} // namespace SHAMS
