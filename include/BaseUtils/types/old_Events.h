//
// Created by PetaTookmyKFC on 11/02/2026.
//

#ifndef BASEUTILS_EVENTS_H
#define BASEUTILS_EVENTS_H
#include <functional>
#include <map>
#include <string>
// BaseVectors , SemiDynamicArray and FixedString from https://github.com/PetaTookmyKFC/BaseUtils/ ( this is a new type for an expandable event dispatcher )
#include "BaseVectors.h"
#include "FixedString.h"
#include "SemiDynamicArray.h"


namespace base_utils::old
{
    class Event
    {
        virtual ~Event();
    };

    enum class EventType
    {
        Unknown,
        Resize,
    };

    struct Resize : public Event<Vector2<int>>
    {
    public:
        Resize(Vector2<int> newSize);
    };

    struct EventDispatcher
    {
        std::map<EventType, SemiDynamicArray<std::function<void(Event*)>>> ListenerMap;
        void AddListener(EventType type, std::function<void(Event*)> callback)
        {
            ListenerMap[type].pushBack(callback);
        }

        void Dispatch (EventType et, Event* ev)
        {
            for (auto& callback : ListenerMap[et])
            {
                callback(ev);
            }
        }

    };


}
#endif //BASEUTILS_EVENTS_H