/**
 * @brief Class that represents a queue of events.
 *
 * @file eventQueue.hpp
 *
 */

#include <string_view>
#include <cstdint>
#include "RingBuffer.hpp"

namespace SHAMS::Events
{
    class EventQueue
    {
    public:
        /**
         * @brief Construct a new Event Queue object
         *
         * @param name - The name of the event queue.
         */
        EventQueue(std::string_view name);

        /**
         * @brief Get the Name of the event queue.
         *
         * @return std::string_view - The name of the event queue.
         */
        const std::string_view getName() const;

        /**
         * @brief Get the Id of the event queue.
         *
         * @return uint32_t - The id of the event queue.
         */
        uint32_t getId() const;

    private:
        friend void initialize();

        static uint32_t m_nextId;

        /// @brief The name of the event queue.
        std::string_view m_name;

        /// @brief The id of the event queue.
        uint32_t m_id;

        /// @brief Data structure to store the event IDs.
        RingBuffer<uint32_t> m_queueBuffer;
    };

} // namespace events
