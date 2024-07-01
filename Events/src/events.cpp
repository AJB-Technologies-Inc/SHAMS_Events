#include "types/eventQueue.hpp"
#include "StaticBuffer.hpp"
#include "Dictionary.hpp"
#include <any>
#include <cstdint>
#include <mutex>
#include <array>

namespace SHAMS::Events
{
    /****************************************************************************/
    /*                      Constants                                           */
    /****************************************************************************/
    /// @brief The maximum number of events that can be queued.
    static constexpr uint32_t MAX_EVENT_QUEUE_CAPACITY{50};
    /// @brief The maximum number of queues that can be subscribed to a given event.
    static constexpr uint32_t MAX_QUEUES_PER_EVENT{25};
    /// @brief The maximum number of event queues that can be created.
    static constexpr uint32_t MAX_EVENT_QUEUES{25};
    /// @brief The maximum number of event types that can be created.
    static constexpr uint32_t MAX_EVENT_TYPES{50};

    /****************************************************************************/
    /*                      Local Variables                                     */
    /****************************************************************************/
    /// @brief Lock for the event system.
    static std::mutex g_eventMutex{};
    /// @brief The next event ID to be assigned.
    static uint32_t g_nextEventId{0};
    /// @brief Dictionary that maps event IDs to the event messages.
    static Dictionary<uint32_t, std::any> g_eventMsgDictionary{MAX_EVENT_QUEUE_CAPACITY};
    /// @brief Dictionary that maps event names to the queues that are subscribed to them.
    static Dictionary<std::string, StaticBuffer<uint32_t, MAX_QUEUES_PER_EVENT>> g_eventsDictionary{MAX_EVENT_TYPES};
    /// @brief Buffer to store the created event queues.
    static StaticBuffer<std::weak_ptr<EventQueue>, MAX_EVENT_QUEUES> g_eventQueueBuffer{};

    /****************************************************************************/
    /*                      Local Functions                                     */
    /****************************************************************************/

    /****************************************************************************/
    /*                      Public Functions                                    */
    /****************************************************************************/
    void initialize()
    {
        std::lock_guard<std::mutex> lock{g_eventMutex};
        EventQueue::m_nextId = 0;
        g_nextEventId = 0;
        // g_eventMsgDictionary.clear();
        // g_eventsDictionary.clear();
        g_eventQueueBuffer.clear();
    }

    std::shared_ptr<EventQueue> createEventQueue(std::string_view name)
    {
        std::lock_guard<std::mutex> lock{g_eventMutex};

        if (g_eventQueueBuffer.size() >= MAX_EVENT_QUEUES)
        {
            return nullptr;
        }
        auto queue = std::shared_ptr<EventQueue>(new EventQueue{name});
        g_eventQueueBuffer.insert(std::weak_ptr<EventQueue>{queue});
        return queue;
    }
} // namespace SHAMS::Events