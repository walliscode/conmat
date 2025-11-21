# Conmat - Console Formatting Library

A C++ library for adding ANSI string formatting to terminal output. Provides safe, type-safe formatting for colors, styles, and dividers.

## Features

- **Safe String Formatting**: Uses enums to prevent string injection attacks
- **ANSI Color Support**: Full color palette including bright variants
- **Text Styles**: Bold, italic, underline, strikethrough, and more
- **Header Functions**: Create centered headers with level-specific formatting
- **Divider Functions**: Create customizable dividers and lines
- **CMake Library**: Easy integration into other projects
- **No Direct Output**: Library only formats strings, doesn't print them
- **String Sanitization**: Automatic filtering of control characters

## Building

```bash
cmake --preset Debug
cmake --build build/Debug
```

## Running Tests

```bash
ctest --preset Debug
```

## Running Demo

```bash
./build/Debug/src/conmat_demo
```

## Usage

### Basic Colors

```cpp
#include "conmat.h"
#include <iostream>

int main() {
  using namespace conmat;
  
  std::cout << Colorize("Red text", Color::Red) << std::endl;
  std::cout << Colorize("Green text", Color::Green) << std::endl;
  std::cout << Colorize("Blue text", Color::Blue) << std::endl;
}
```

### Text Styles

```cpp
std::cout << Stylize("Bold text", Style::Bold) << std::endl;
std::cout << Stylize("Italic text", Style::Italic) << std::endl;
std::cout << Stylize("Underline text", Style::Underline) << std::endl;
```

### Combined Formatting

```cpp
FormatOptions opts(Color::Red, Style::Bold);
std::cout << Format("Bold red text", opts) << std::endl;

FormatOptions with_bg(Color::White, Color::Blue);
std::cout << Format("White on blue", with_bg) << std::endl;
```

### Dividers

```cpp
// Default divider (80 characters using CMake-configured default symbol)
std::cout << Divider() << std::endl;

// Custom width with default symbol
std::cout << Divider(40) << std::endl;

// Custom symbol and width (runtime override)
std::cout << Divider("-", 40) << std::endl;
std::cout << Divider("*", 50) << std::endl;

// Colored dividers
FormatOptions cyan(Color::Cyan);
std::cout << Divider("=", 80, cyan) << std::endl;
```

**CMake Configuration**: The default symbol can be configured at compile time:

```bash
# Configure with custom default divider symbol
cmake -DCONMAT_DEFAULT_DIVIDER_SYMBOL="-" ...
```

The default symbol is "=" if not specified. Runtime calls can always override this default.

### Indentation

```cpp
// Level-based indentation (default: 2 spaces per level)
std::cout << Indent(0) << "No indent" << std::endl;
std::cout << Indent(1) << "One level (2 spaces)" << std::endl;
std::cout << Indent(2) << "Two levels (4 spaces)" << std::endl;

// Custom spaces per level
std::cout << Indent(1, 4) << "One level (4 spaces)" << std::endl;
std::cout << Indent(2, 4) << "Two levels (8 spaces)" << std::endl;

// Combine with other formatting
std::cout << Indent(1) << Colorize("Red text", Color::Red) << std::endl;
std::cout << Indent(2) << Stylize("Bold text", Style::Bold) << std::endl;

// Works with any output
std::cout << Indent(1) << 42 << std::endl;
std::cout << Indent(2) << 3.14 << std::endl;
```

### Headers

```cpp
// Create headers with different levels (1-4+)
std::cout << Header("Main Title", 1) << std::endl;        // === Main Title ===
std::cout << Header("Subsection", 2) << std::endl;        // --- Subsection ---
std::cout << Header("Minor Section", 3) << std::endl;     // ~~~ Minor Section ~~~
std::cout << Header("Note", 4) << std::endl;              // ... Note ...

// Custom width (default: 80)
std::cout << Header("Short", 1, 40) << std::endl;

// Colored headers
FormatOptions cyan_header(Color::Cyan, Style::Bold);
std::cout << Header("Important", 1, 80, cyan_header) << std::endl;
```

Headers automatically center text and balance padding characters based on the level:
- Level 1: `=` characters
- Level 2: `-` characters
- Level 3: `~` characters
- Level 4+: `.` characters

### String Safety

```cpp
// Sanitize removes control characters
std::string safe = Sanitize("text\x1b[31mwith\x1b[0mcodes");

// Strip ANSI codes
std::string plain = StripAnsi(Colorize("colored", Color::Red));
```

## API Reference

### Enums

- **Color**: Default, Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, and Bright variants
- **Style**: Default, Bold, Dim, Italic, Underline, Blink, Reverse, Hidden, Strikethrough

### Functions

- `Format(text, options)` - Format text with full options
- `Colorize(text, color)` - Apply foreground color
- `Stylize(text, style)` - Apply text style
- `Indent(level, spaces_per_level)` - Generate indentation for given level (default: 2 spaces per level)
- `Header(value, level, width, options)` - Create centered header with level-specific padding character (default width: 80)
- `Divider(symbol, width, options)` - Create divider line with custom symbol (runtime override)
- `Divider(width, options)` - Create divider line with CMake-configured default symbol
- `Sanitize(text)` - Remove control characters
- `StripAnsi(text)` - Remove ANSI escape codes

### CMake Options

- `CONMAT_DEFAULT_DIVIDER_SYMBOL` - Configure the default symbol for Divider function (default: "=")

### FormatOptions

```cpp
struct FormatOptions {
  Color foreground = Color::Default;
  Color background = Color::Default;
  Style style = Style::Default;
  bool reset_after = true;  // Auto-append reset sequence
};
```

## Integration

### Using CMake FetchContent (Recommended)

Add to your CMakeLists.txt:

```cmake
include(FetchContent)

FetchContent_Declare(
  conmat
  GIT_REPOSITORY https://github.com/walliscode/conmat.git
  GIT_TAG main  # or specify a tag/commit
)

FetchContent_MakeAvailable(conmat)

target_link_libraries(your_target PRIVATE conmat::conmat)
```

### Using add_subdirectory

If you have conmat as a subdirectory in your project:

```cmake
add_subdirectory(path/to/conmat)
target_link_libraries(your_target PRIVATE conmat::conmat)
```

## Design Principles

1. **Type Safety**: Enums prevent string injection and typos
2. **No Direct Output**: Library only formats, you control output
3. **Security**: Automatic sanitization of control characters
4. **Defaults**: Sensible defaults for all parameters
5. **Composable**: Mix colors, styles, and backgrounds freely

## Requirements

- C++23 or later
- CMake 3.31 or later
- Compiler with C++23 support (Clang, GCC, MSVC)

## License

See LICENSE file for details.
