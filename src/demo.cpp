#include "conmat.h"
#include <iostream>

int main() {
  using namespace conmat;
  
  std::cout << "=== Conmat Library Demo ===" << std::endl << std::endl;
  
  // Test basic colors
  std::cout << "Basic Colors:" << std::endl;
  std::cout << colorize("Red text", Color::Red) << std::endl;
  std::cout << colorize("Green text", Color::Green) << std::endl;
  std::cout << colorize("Blue text", Color::Blue) << std::endl;
  std::cout << colorize("Yellow text", Color::Yellow) << std::endl;
  std::cout << colorize("Magenta text", Color::Magenta) << std::endl;
  std::cout << colorize("Cyan text", Color::Cyan) << std::endl;
  std::cout << std::endl;
  
  // Test bright colors
  std::cout << "Bright Colors:" << std::endl;
  std::cout << colorize("Bright Red", Color::BrightRed) << std::endl;
  std::cout << colorize("Bright Green", Color::BrightGreen) << std::endl;
  std::cout << colorize("Bright Blue", Color::BrightBlue) << std::endl;
  std::cout << std::endl;
  
  // Test styles
  std::cout << "Text Styles:" << std::endl;
  std::cout << stylize("Bold text", Style::Bold) << std::endl;
  std::cout << stylize("Italic text", Style::Italic) << std::endl;
  std::cout << stylize("Underline text", Style::Underline) << std::endl;
  std::cout << stylize("Strikethrough text", Style::Strikethrough) << std::endl;
  std::cout << std::endl;
  
  // Test combined formatting
  std::cout << "Combined Formatting:" << std::endl;
  FormatOptions bold_red(Color::Red, Style::Bold);
  std::cout << format("Bold Red Text", bold_red) << std::endl;
  
  FormatOptions green_on_black(Color::Green, Color::Black);
  std::cout << format("Green on Black", green_on_black) << std::endl;
  
  FormatOptions bold_cyan_on_blue(Color::BrightCyan, Color::Blue, Style::Bold);
  std::cout << format("Bold Cyan on Blue", bold_cyan_on_blue) << std::endl;
  std::cout << std::endl;
  
  // Test dividers
  std::cout << "Dividers:" << std::endl;
  std::cout << divider() << std::endl;
  std::cout << divider("-", 40) << std::endl;
  std::cout << divider("*", 50) << std::endl;
  std::cout << divider("=-", 60) << std::endl;
  std::cout << horizontal_line(70) << std::endl;
  std::cout << double_line(80) << std::endl;
  std::cout << std::endl;
  
  // Test colored dividers
  std::cout << "Colored Dividers:" << std::endl;
  FormatOptions cyan_divider(Color::Cyan);
  std::cout << divider("=", 80, cyan_divider) << std::endl;
  
  FormatOptions bold_green_divider(Color::Green, Style::Bold);
  std::cout << divider("-", 80, bold_green_divider) << std::endl;
  std::cout << std::endl;
  
  // Test sanitization
  std::cout << "String Sanitization:" << std::endl;
  std::string unsafe = "Safe text\033[31mInjected\033[0m";
  std::cout << "Original: " << unsafe << std::endl;
  std::cout << "Sanitized: " << sanitize(unsafe) << std::endl;
  std::cout << std::endl;
  
  // Test ANSI stripping
  std::cout << "ANSI Stripping:" << std::endl;
  std::string with_ansi = colorize("Colored text", Color::Red);
  std::cout << "With ANSI: " << with_ansi << std::endl;
  std::cout << "Stripped: " << strip_ansi(with_ansi) << std::endl;
  std::cout << std::endl;
  
  std::cout << format("Demo completed successfully!", FormatOptions(Color::Green, Style::Bold)) << std::endl;
  
  return 0;
}
