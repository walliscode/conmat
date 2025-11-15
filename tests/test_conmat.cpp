#include "conmat.h"
#include <iostream>
#include <cassert>
#include <string>

void test_color_formatting() {
  using namespace conmat;
  
  std::string red = colorize("test", Color::Red);
  assert(red.find("\033[31m") != std::string::npos);
  assert(red.find("test") != std::string::npos);
  assert(red.find("\033[0m") != std::string::npos);
  
  std::cout << "✓ Color formatting test passed" << std::endl;
}

void test_style_formatting() {
  using namespace conmat;
  
  std::string bold = stylize("test", Style::Bold);
  assert(bold.find("\033[1m") != std::string::npos);
  assert(bold.find("test") != std::string::npos);
  
  std::cout << "✓ Style formatting test passed" << std::endl;
}

void test_combined_formatting() {
  using namespace conmat;
  
  FormatOptions opts(Color::Green, Style::Bold);
  std::string result = format("test", opts);
  assert(result.find("\033[1m") != std::string::npos);
  assert(result.find("\033[32m") != std::string::npos);
  assert(result.find("test") != std::string::npos);
  
  std::cout << "✓ Combined formatting test passed" << std::endl;
}

void test_divider() {
  using namespace conmat;
  
  std::string div = divider("=", 10);
  assert(div == "==========");
  
  std::string div2 = divider("-", 5);
  assert(div2 == "-----");
  
  std::string div3 = divider("abc", 10);
  assert(div3 == "abcabcabca");
  
  std::cout << "✓ Divider test passed" << std::endl;
}

void test_horizontal_line() {
  using namespace conmat;
  
  std::string line = horizontal_line(10);
  assert(line == "----------");
  
  std::cout << "✓ Horizontal line test passed" << std::endl;
}

void test_double_line() {
  using namespace conmat;
  
  std::string line = double_line(10);
  assert(line == "==========");
  
  std::cout << "✓ Double line test passed" << std::endl;
}

void test_sanitize() {
  using namespace conmat;
  
  // Test that control characters are removed
  std::string input = "hello\x1b[31mworld";
  std::string output = sanitize(input);
  assert(output.find('\x1b') == std::string::npos);
  assert(output.find("hello") != std::string::npos);
  assert(output.find("world") != std::string::npos);
  
  // Test that normal text is preserved
  std::string normal = "normal text";
  assert(sanitize(normal) == normal);
  
  // Test that whitespace is preserved
  std::string with_ws = "hello\nworld\ttab";
  std::string sanitized_ws = sanitize(with_ws);
  assert(sanitized_ws.find('\n') != std::string::npos);
  assert(sanitized_ws.find('\t') != std::string::npos);
  
  std::cout << "✓ Sanitize test passed" << std::endl;
}

void test_strip_ansi() {
  using namespace conmat;
  
  std::string with_ansi = "\033[31mRed Text\033[0m";
  std::string stripped = strip_ansi(with_ansi);
  assert(stripped == "Red Text");
  
  std::string no_ansi = "Plain text";
  assert(strip_ansi(no_ansi) == no_ansi);
  
  std::cout << "✓ Strip ANSI test passed" << std::endl;
}

void test_background_color() {
  using namespace conmat;
  
  FormatOptions opts(Color::White, Color::Red);
  std::string result = format("test", opts);
  assert(result.find("\033[37m") != std::string::npos); // White foreground
  assert(result.find("\033[41m") != std::string::npos); // Red background
  
  std::cout << "✓ Background color test passed" << std::endl;
}

void test_no_reset() {
  using namespace conmat;
  
  FormatOptions opts;
  opts.foreground = Color::Red;
  opts.reset_after = false;
  std::string result = format("test", opts);
  assert(result.find("\033[0m") == std::string::npos);
  assert(result.find("\033[31m") != std::string::npos);
  
  std::cout << "✓ No reset test passed" << std::endl;
}

void test_empty_divider() {
  using namespace conmat;
  
  std::string empty1 = divider("", 10);
  assert(empty1.empty());
  
  std::string empty2 = divider("=", 0);
  assert(empty2.empty());
  
  std::cout << "✓ Empty divider test passed" << std::endl;
}

int main() {
  std::cout << "Running conmat tests..." << std::endl << std::endl;
  
  test_color_formatting();
  test_style_formatting();
  test_combined_formatting();
  test_divider();
  test_horizontal_line();
  test_double_line();
  test_sanitize();
  test_strip_ansi();
  test_background_color();
  test_no_reset();
  test_empty_divider();
  
  std::cout << std::endl << "All tests passed! ✓" << std::endl;
  
  return 0;
}
