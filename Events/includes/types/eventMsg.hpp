#pragma once

#include <any>
#include <string>
#include <cstdint>

namespace events
{
    struct EventMsg
    {
        /// @brief The event topic.
        std::string m_eventTopic;

        /// @brief The id of the event.
        uint32_t m_id;

        /// @brief The data of the event.
        std::any m_data;
    };

} // namespace events
