//
// Created by PetaTookmyKFC on 11/02/2026.
//

#ifndef BASEUTILS_EVENTS_H
#define BASEUTILS_EVENTS_H
#include <functional>
#include <typeindex>
#include <unordered_map>

#include "BaseVectors.h"
#include "SemiDynamicArray.h"

namespace base_utils::types
{
    class Event
    {
    public:
        virtual ~Event() = default;
    };

    enum class EventType
    {
        Unknown,
        Resize,
    };

    struct Resize : public Event
    {
        Vector2<int> newSize;
        Resize(Vector2<int> newSize): newSize(newSize) {};
    };

    struct EventDispatcher
    {
        std::unordered_map<std::type_index,
            std::vector<std::function<void(Event*)>>> listeners;

        template<typename T>
        void AddListener(std::function<void(T*)> callback)
        {
            listeners[typeid(T)].push_back(
                [callback](Event* e)
                {
                    callback(static_cast<T*>(e));
                });
        }

        template<typename T>
        void Dispatch(T* ev)
        {
            auto it = listeners.find(typeid(T));
            if (it != listeners.end())
            {
                for (auto& cb : it->second)
                    cb(ev);
            }
        }
    };

}


#endif //BASEUTILS_EVENTS_H