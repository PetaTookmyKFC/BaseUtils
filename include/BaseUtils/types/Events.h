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
        Unknown_Event,
        Example_Vector2_event,
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
    struct Unknown_Event : public Event {};

    struct Example_Vector2_event : public Event
    {
    public:
        Vector2<int> Example_v2_data;
        Example_Vector2_event(Vector2<int> data) : Example_v2_data(data) {}
    };

}


#endif //BASEUTILS_EVENTS_H