#include "types/eventQueue.hpp"

namespace SHAMS::Events
{

    uint32_t EventQueue::m_nextId = 0;

    EventQueue::EventQueue(std::string_view name)
        : m_name{name},
          m_id{m_nextId++},
          m_queueBuffer{10}
    {
    }

    const std::string_view EventQueue::getName() const
    {
        return m_name;
    }

    uint32_t EventQueue::getId() const
    {
        return m_id;
    }

} // namespace events