# Base Utils

---
This is a basic library that contains functions that I find useful while programming. This includes a basic formatting system that should not add any runtime costs including a way to auto remove any logs that are not desired upon the final build, reducing runtime costs and executable size.

--- 
## Current Systems
- [Formatting](##Formatting) : Automaticaly adds colours, prefixes and suffixes created by the user at compile time. Ensuring a minimal effect upon runtime. No more checking console formatting options via if statements at runtime, it just modifies the actual strings at compile time.

## Formatting

There are 3.5 types of formatting included in this library. Styled Text, Prefixed Text, Suffix Text.
- [FixedString](###Fixed String) : This is a static string.
- [Debug](###Debug Field) : This will include or exclude a function (this function needs to be a lamda)
- [Styled Text](###Styled Text) : This changes the colour and basic console styles using ASNI codes

### Fixed String
Fixed string is a string class used at compile time with a known size and is used within the Styles and prefix/suffix modules. It is a wrapper around a char array, using template size to ensure it is completely compile time.  
It is made via `FixedString( "string_example" )` and this will generate the necessary data for the string, in this example it would expand to `FixedString<14>{data=['s', 't', 'r', 'i', …]}`, template size is required for compile time execution.
The FixedString type has some basic features built in. Including `c_str()` that will return the char array. Operator `std::string_view()` that is triggered when the program wants to get a string view of the FixedString, for example when outputing to console. And the `size()` function that returns a `std::size_t` of the contained string. This also has the `operator<<` implemented for `std::ostream` allowing for easy output.
<br>--- Example
```c++
    inline constexpr FixedString StatisStringExample = "EXAMPLE CODE"
    int main () {
        const auto a = FixedString("Example String  ")    
    }
```


### Debug Field

The debug field can be disabled by defining `NO_DEBUG`. This will cause any lamda to not run. There are two different methods included, single line and multiline. Multi lines are detected by the input being `invocable`.
Both use `std::forward` to run the function.
```c++
#define NO_DEBUG
int main () {
    BaseUtils::fmt::Debug(
        std::cout << "only showed if NO_DEBUG is not set" << std::endl
    );
}
```
The above code will not output anything.
```c++
// Single Line
int main () {
    base_utils::fmt::Debug(std::cout << "Hello World! from singular" << std::endl);
}
// Multi - Line

int main () {
    base_utils::fmt::Debug( [] {
        std::cout << "Hello World! from multiple" << std::endl;
        for (int i = 0; i < 5; i++) {
            std::cout << "Counting " << i << " items" << std::endl;
        }
    } );
}
```
### Styled Text
The Styled text is used for format text using ASNI style codes.
This can be disabled via using 
```c++ 
#define NO_COLOUR
```
All styling is ran at compile time to help prevent any runtime overhead or filesize.

#### Defining A Style
Styles are created using the template `ComPrefix` if a style doesn't exist within the existing modules it can be added by creating a `FixedString`

```c++
    inline constexpr auto Strikethrough(std::string_view str) {
        return StyledText<STRIKETHROUGH_CODE.size()>(STRIKETHROUGH_CODE, str);
    }
    constexpr inline auto LI = ListItem<BG_BRIGHT_GREEN_CODE, FG_BLACK_CODE, BOLD_CODE>;
    inline constexpr auto Success = ComPrefix<
    BOLD_CODE,
    FG_BRIGHT_GREEN_CODE>(FixedString( "SUCCESS : " ));
    
    inline constexpr auto customstyle = Compose<BOLD_CODE, FG_BRIGHT_GREEN_CODE>();
    
```


# Dynamic Array

Auto Increments the size of an array when it fills up, Minimum Increment size is 1

- resize ( size_t newSize ) >> 
Resizes the dropping any data at the end of the array if the array is smaller

- setIncrementSize(size_t incrementSize ) >> Changes the amount it increments when needing resizing. 
- pushBack( const T& value) >> Add the variable to the end of the array expanding is required
- size_t size() >> Returns the number of occupied spots in the array
- size_t CurrentCapacity() >> Returns the maximum size of the array before resizing
- size_t AvailableSpace () >> Returns the number of slots before needing to resize.