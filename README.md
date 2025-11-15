# Conmat - Console Formatting Library

A C++ library for adding ANSI string formatting to terminal output. Provides safe, type-safe formatting for colors, styles, and dividers.

## Features

- **Safe String Formatting**: Uses enums to prevent string injection attacks
- **ANSI Color Support**: Full color palette including bright variants
- **Text Styles**: Bold, italic, underline, strikethrough, and more
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
  
  std::cout << colorize("Red text", Color::Red) << std::endl;
  std::cout << colorize("Green text", Color::Green) << std::endl;
  std::cout << colorize("Blue text", Color::Blue) << std::endl;
}
```

### Text Styles

```cpp
std::cout << stylize("Bold text", Style::Bold) << std::endl;
std::cout << stylize("Italic text", Style::Italic) << std::endl;
std::cout << stylize("Underline text", Style::Underline) << std::endl;
```

### Combined Formatting

```cpp
FormatOptions opts(Color::Red, Style::Bold);
std::cout << format("Bold red text", opts) << std::endl;

FormatOptions with_bg(Color::White, Color::Blue);
std::cout << format("White on blue", with_bg) << std::endl;
```

### Dividers

```cpp
// Default divider (80 '=' characters)
std::cout << divider() << std::endl;

// Custom symbol and width
std::cout << divider("-", 40) << std::endl;
std::cout << divider("*", 50) << std::endl;

// Convenience functions
std::cout << horizontal_line(70) << std::endl;  // Uses '-'
std::cout << double_line(80) << std::endl;      // Uses '='

// Colored dividers
FormatOptions cyan(Color::Cyan);
std::cout << divider("=", 80, cyan) << std::endl;
```

### String Safety

```cpp
// Sanitize removes control characters
std::string safe = sanitize("text\x1b[31mwith\x1b[0mcodes");

// Strip ANSI codes
std::string plain = strip_ansi(colorize("colored", Color::Red));
```

## API Reference

### Enums

- **Color**: Default, Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, and Bright variants
- **Style**: Default, Bold, Dim, Italic, Underline, Blink, Reverse, Hidden, Strikethrough

### Functions

- `format(text, options)` - Format text with full options
- `colorize(text, color)` - Apply foreground color
- `stylize(text, style)` - Apply text style
- `divider(symbol, width, options)` - Create divider line
- `horizontal_line(width, options)` - Create horizontal line with '-'
- `double_line(width, options)` - Create double line with '='
- `sanitize(text)` - Remove control characters
- `strip_ansi(text)` - Remove ANSI escape codes

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

Add to your CMakeLists.txt:

```cmake
add_subdirectory(path/to/conmat)
target_link_libraries(your_target PRIVATE conmat)
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
