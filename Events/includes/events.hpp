#pragma once

#include "types/eventQueue.hpp"
#include <memory>

namespace SHAMS::Events
{

    /**
     * @brief Initialize the events module.
     *
     *  This function initializes the events module. It should be called
     *  before any other function in the module.
     */
    void initialize();

    /**
     * @brief Create a new event queue.
     *
     * @param name - The name of the event queue.
     * @return std::shared_ptr<EventQueue> - Shared pointer to the event queue.
     */
    std::shared_ptr<EventQueue> createEventQueue(std::string_view name);

    /**
     * @brief Subscribe to a given event.
     *
     * @param eventName Event to subscribe to.
     * @param queueId Id of the queue to subscribe to the event, this can be obtained from a EventQueue object.
     * @return bool - True if the subscription was successful, false otherwise.
     */
    bool subscribeToEvent(std::string_view eventName, uint32_t queueId);

    /**
     * @brief Unsubscribe from a given event.
     *
     * @param eventName Event to unsubscribe from.
     * @param queueId Id of the queue to unsubscribe from the event, this can be obtained from a EventQueue object.
     * @return bool - True if the unsubscription was successful, false otherwise.
     */
    bool unsubscribeFromEvent(std::string_view eventName, uint32_t queueId);

} // namespace SHAMS::Events
