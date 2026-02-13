# BaseUtils

---
A zero-overhead, compile-time utility library for C++ focusing on efficient formatting and basic types.

--- 
## Features
- **[Formatting](#formatting)**: Zero-runtime-cost string formatting including colors, prefixes, and suffixes.
- **[Debug System](#debug-field)**: Compile-time toggleable debug logs using lambdas.
- **[Semi-Dynamic Array](#semi-dynamic-array)**: A flexible array type with controllable growth.
- **[Vector Types](#vector-types)**: Simple `Vector2` and `Vector3` structures.
- **[Event Handling](#events)**: A simple event hander for triggering lamda functions.
---

## Formatting

The formatting system is designed to perform as much work as possible at compile time, minimizing runtime overhead and executable size.

### FixedString
`FixedString` is the backbone of the compile-time formatting system. It's a wrapper around a `char` array with a template-defined size.

**Usage:**
```c++
#include "BaseUtils/ColouredFormatting.h"

// Explicitly
constexpr auto myString = base_utils::fmt::FixedString("Example");

// Or using deduction guide
constexpr base_utils::fmt::FixedString another = "Another Example";
```

**Key Features:**
- `c_str()`: Returns the underlying `const char*`.
- `size()`: Returns the length of the string.
- `operator std::string_view()`: Implicit conversion for easy use with standard functions.
- `operator<<`: Integration with `std::ostream`.
- `operator+`: Compile-time concatenation of `FixedString` objects.

---

### Debug Field
The debug system allows you to wrap code in `Debug()` calls that can be completely stripped from the final build by defining `NO_DEBUG`.

**Single Line:**
```c++
base_utils::fmt::Debug(std::cout << "This only shows in debug builds" << std::endl);
```

**Multi-Line (using Lambda):**
```c++
base_utils::fmt::Debug([] {
    std::cout << "Complex debug logic here..." << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "Step " << i << std::endl;
    }
});
```

To disable all debug output, define `NO_DEBUG` before including the library:
```c++
#define NO_DEBUG
#include "BaseUtils/All.h"
```

---

### Styled Text
ANSI color and style formatting that can be disabled globally via `#define NO_COLOUR`.

**Pre-defined Styles:**
```c++
std::cout << base_utils::fmt::Red("This is red text") << std::endl;
std::cout << base_utils::fmt::Bold(base_utils::fmt::Green("Bold Green")) << std::endl;
```

**Custom Composed Styles:**
Use `Compose<Styles...>()` to create reusable style functions.
```c++
using namespace base_utils::fmt;
inline constexpr auto MyStyle = Compose<BOLD_CODE, FG_BRIGHT_MAGENTA_CODE, UNDERLINE_CODE>();

std::cout << MyStyle("Styled message") << std::endl;
```

---

### Prefixed and Suffixed Text
Add consistent prefixes or suffixes to your messages with optional styling.

**Prefix Example:**
```c++
inline constexpr auto Success = base_utils::fmt::ComPrefix<base_utils::fmt::BOLD_CODE, base_utils::fmt::FG_BRIGHT_GREEN_CODE>(
    base_utils::fmt::FixedString("SUCCESS: ")
);

std::cout << Success("Operation completed.") << std::endl;
// Output: SUCCESS: Operation completed. (in bold green)
```

**Suffix Example:**
```c++
inline constexpr auto Affixed = base_utils::fmt::ComSuffix<base_utils::fmt::FG_RED_CODE>(
    base_utils::fmt::FixedString(" [IMPORTANT]")
);

std::cout << Affixed("Check this") << std::endl;
// Output: Check this [IMPORTANT] (in red)
```

**Full Formatting (Prefix + Suffix):**
```c++
inline constexpr auto Alert = base_utils::fmt::ComFormatted<base_utils::fmt::FG_BRIGHT_RED_CODE>(
    base_utils::fmt::FixedString("[! "), 
    base_utils::fmt::FixedString(" !]")
);

std::cout << Alert("SYSTEM CRITICAL") << std::endl;
// Output: [! SYSTEM CRITICAL !] (in bright red)
```

---

## Semi-Dynamic Array
`SemiDynamicArray<T>` is a wrapper around a dynamic array that grows by a fixed increment when it reaches capacity.

**Basic Usage:**
```c++
#include "BaseUtils/types/SemiDynamicArray.h"

// Create with increment size of 5 and initial capacity 0
base_utils::types::SemiDynamicArray<int> arr(5);

arr.pushBack(10);
arr.pushMultiple(20, 30, 40);

std::cout << "Size: " << arr.size() << std::endl;
std::cout << "Capacity: " << arr.CurrentCapacity() << std::endl;
```

**Methods:**
- `pushBack(const T& value)`: Adds an element, resizing if needed.
- `pushMultiple(Vals&&... values)`: Adds multiple elements at once.
- `setIncrementSize(size_t size)`: Changes how much the array grows by.
- `size()`: Number of elements currently in the array.
- `CurrentCapacity()`: Total allocated space.
- `AvailableSpace()`: Remaining space before next resize.
- `operator[]`: Standard index-based access (with bounds checking).
- `begin()` / `end()`: Iteration support.

---

## Vector Types
Simple template structures for 2D and 3D vectors.

```c++
#include "BaseUtils/types/BaseVectors.h"

base_utils::types::Vector2<float> pos(10.0f, 20.0f);
base_utils::types::Vector3<int> color(255, 128, 0);
```

## Events
#### Event Types
The event type doesn't have any included EventTypes pre-registere execpt for the `Unknown_Event` and `Example_Vector2_Event` event.
The Enum EventType is just an enum to try and track events easier. `Unknown_Event` returns a blank class as the event object, The `Example_Vector2_Event` just returns a struct with a property of `Example_v2_data` containing a `Vector2<int>`, this was just for an example an for texting.

EventTypes are enums of a struct / class that is used as the event parameter. The Enum is just used for organisation.
```c++

struct A_Basic_Event_Example : public Event
{
    public:
        std::string Data;
        A_Basic_Event_Example(std::string data) : Data(data) {}
};

```
This creates a basic event class, this is fully customisable as long as it extends `Event` just for the type safety.

### Event Dispacther
This is the class that is used to register the events and trigger the events. The event is registered by running the `AddListener` function. This function requires a template parameter for the event class that is returned when the event is triggered, but is also used as the ID for the event, meaning that the data type should be saved available to both the creation and execution of the event ( easiest in a const or Event )
```c++
// Creating a Dispactcher
import "BaseUtils/types/Events.h"
EventDispatcher dispactcher;
dispatcher.AddListener<A_Basic_Event_Example>( [] ( A_Basic_Event_Example* params)
{
    std::cout << "Event Triggered " << params.data << std::endl;
} ) )
...
...
A_Basic_Event_Example ev(5);
dispatcher.Dispatch(&ev)

```




---

## Configuration Macros
Define these before including the headers to change behavior:
- `NO_COLOUR`: Disables ANSI escape codes in output.
- `NO_FORMAT`: Disables prefixes and suffixes in `PrefixedText`, `SuffixedText`, and `FormattedText`.
- `NO_DEBUG`: Strips all `base_utils::fmt::Debug()` calls from the binary.