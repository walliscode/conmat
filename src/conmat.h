#pragma once

#include <concepts>
#include <sstream>
#include <string>
#include <string_view>

namespace conmat {

////////////////////////////////////////////////////////////
/// \brief Concept for types that can be streamed to ostream
///
////////////////////////////////////////////////////////////
template <typename T>
concept Streamable = requires(std::ostream &os, T value) {
  { os << value } -> std::same_as<std::ostream &>;
};

namespace detail {
/// \brief Convert any streamable type to string
template <Streamable T> std::string to_string(const T &value) {
  if constexpr (std::is_same_v<T, std::string> ||
                std::is_same_v<T, std::string_view> ||
                std::is_same_v<T, const char *>) {
    return std::string(value);
  } else {
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }
}
} // namespace detail

////////////////////////////////////////////////////////////
/// \brief ANSI color codes enum
///
////////////////////////////////////////////////////////////
enum class Color {
  Default,
  Black,
  Red,
  Green,
  Yellow,
  Blue,
  Magenta,
  Cyan,
  White,
  BrightBlack,
  BrightRed,
  BrightGreen,
  BrightYellow,
  BrightBlue,
  BrightMagenta,
  BrightCyan,
  BrightWhite
};

////////////////////////////////////////////////////////////
/// \brief ANSI text style codes enum
///
////////////////////////////////////////////////////////////
enum class Style {
  Default,
  Bold,
  Dim,
  Italic,
  Underline,
  Blink,
  Reverse,
  Hidden,
  Strikethrough
};

////////////////////////////////////////////////////////////
/// \brief Format options for text formatting
///
////////////////////////////////////////////////////////////
struct FormatOptions {
  Color foreground = Color::Default;
  Color background = Color::Default;
  Style style = Style::Default;
  bool reset_after = true; // Automatically append reset sequence

  FormatOptions() = default;
  FormatOptions(Color fg) : foreground(fg) {}
  FormatOptions(Color fg, Style s) : foreground(fg), style(s) {}
  FormatOptions(Color fg, Color bg) : foreground(fg), background(bg) {}
  FormatOptions(Color fg, Color bg, Style s)
      : foreground(fg), background(bg), style(s) {}
};

////////////////////////////////////////////////////////////
/// \brief Format a string with ANSI codes (internal implementation)
/// \param text The text to format
/// \param options Format options (default: no formatting)
/// \return Formatted string with ANSI codes
///
////////////////////////////////////////////////////////////
std::string FormatImpl(std::string_view text,
                       const FormatOptions &options = {});

////////////////////////////////////////////////////////////
/// \brief Format any streamable value with ANSI codes
/// \param value The value to format (can be any type streamable to cout)
/// \param options Format options (default: no formatting)
/// \return Formatted string with ANSI codes
///
////////////////////////////////////////////////////////////
template <Streamable T>
std::string Format(const T &value, const FormatOptions &options = {}) {
  return FormatImpl(detail::to_string(value), options);
}

////////////////////////////////////////////////////////////
/// \brief Format any streamable value with just a foreground color
/// \param value The value to format (can be any type streamable to cout)
/// \param color The foreground color
/// \return Formatted string with color
///
////////////////////////////////////////////////////////////
template <Streamable T> std::string Colorize(const T &value, Color color) {
  FormatOptions options;
  options.foreground = color;
  return FormatImpl(detail::to_string(value), options);
}

////////////////////////////////////////////////////////////
/// \brief Format any streamable value with a style
/// \param value The value to format (can be any type streamable to cout)
/// \param style The text style
/// \return Formatted string with style
///
////////////////////////////////////////////////////////////
template <Streamable T> std::string Stylize(const T &value, Style style) {
  FormatOptions options;
  options.style = style;
  return FormatImpl(detail::to_string(value), options);
}

////////////////////////////////////////////////////////////
/// \brief Create a divider line with explicit symbol
/// \param symbol The symbol to use
/// \param width The width of the divider (default: 80)
/// \param options Format options for the divider
/// \return Formatted divider string
///
////////////////////////////////////////////////////////////
std::string Divider(std::string_view symbol, size_t width = 80,
                    const FormatOptions &options = {});

////////////////////////////////////////////////////////////
/// \brief Create a divider line with default symbol from CMake configuration
/// \param width The width of the divider (default: 80)
/// \param options Format options for the divider
/// \return Formatted divider string
///
////////////////////////////////////////////////////////////
std::string Divider(size_t width = 80, const FormatOptions &options = {});

////////////////////////////////////////////////////////////
/// \brief Escape and sanitize input string to prevent injection
/// \param text The text to sanitize
/// \return Sanitized string safe for terminal output
///
////////////////////////////////////////////////////////////
std::string Sanitize(std::string_view text);

////////////////////////////////////////////////////////////
/// \brief Strip ANSI codes from a string
/// \param text The text to strip codes from
/// \return Plain text without ANSI codes
///
////////////////////////////////////////////////////////////
std::string StripAnsi(std::string_view text);

/////////////////////////////////////////////////
/// @brief Return a yellow progress dots
/////////////////////////////////////////////////
std::string TestInProgress();

/////////////////////////////////////////////////
/// @brief Return a green check mark symbol
/////////////////////////////////////////////////
std::string TestPassed();

/////////////////////////////////////////////////
/// @brief Return a red cross mark symbol
/////////////////////////////////////////////////
std::string TestFailed();

////////////////////////////////////////////////////////////
/// \brief Generate indentation string for given level
///
/// Creates a string of spaces for the specified indentation level.
/// Each level adds spaces_per_level spaces to the output.
///
/// \param level Indentation level (0 = no indent, 1 = one level, etc.)
/// \param spaces_per_level Number of spaces per indentation level (default: 2)
/// \return String containing appropriate number of spaces
///
/// \example
/// std::string indent = Indent(0);  // "" (no spaces)
/// std::string indent = Indent(1);  // "  " (2 spaces)
/// std::string indent = Indent(2);  // "    " (4 spaces)
///
////////////////////////////////////////////////////////////
std::string Indent(size_t level, size_t spaces_per_level = 2);

////////////////////////////////////////////////////////////
/// \brief Generate a header with centered text and padding
///
/// Creates a header with the given text centered and surrounded by
/// padding characters. The padding character varies based on the level:
/// - Level 1: '=' characters
/// - Level 2: '-' characters  
/// - Level 3: '~' characters
/// - Level 4+: '.' characters
///
/// The total width is fixed at 80 characters by default. The text is
/// centered with padding characters filling the remaining space.
/// At least 3 padding characters appear on each side.
///
/// \param value The text to display in the header
/// \param level Header level (1-4+, affects padding character)
/// \param width Total width of the header line (default: 80)
/// \param options Format options for the header
/// \return Formatted header string with centered text
///
/// \example
/// std::string h1 = Header("test", 1);     // "=== test ==="
/// std::string h2 = Header("title", 2);    // "--- title ---"
/// std::string h3 = Header("section", 3);  // "~~~ section ~~~"
///
////////////////////////////////////////////////////////////
std::string Header(std::string_view value, size_t level, size_t width = 80,
                   const FormatOptions &options = {});

} // namespace conmat
