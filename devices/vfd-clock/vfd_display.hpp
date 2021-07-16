#include "esphome.h"

namespace vfd {
constexpr auto num_tubes = 8;

constexpr auto latch_pin = D8;
constexpr auto clock_pin = D3;
constexpr auto data_pin = D4;

constexpr uint8_t font_table[95] = {
    0x00, // space
    0x82, // !
    0x22, // "
    0x00, // #
    0x00, // $
    0x00, // %
    0x00, // &
    0x02, // '
    0x39, // (
    0x0F, // )
    0x00, // *
    0x00, // +
    0x04, // ,
    0x40, // -
    0x80, // .
    0x00, // /
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x00, // :
    0x00, // ;
    0x00, // <
    0x09, // =
    0x00, // >
    0x53, // ?
    0x00, // @
    0x77, // A
    0x7C, // B
    0x39, // C
    0x5E, // D
    0x79, // E
    0x71, // F
    0x3D, // G
    0x76, // H
    0x06, // I
    0x1E, // J
    0x00, // K
    0x38, // L
    0x00, // M
    0x37, // N
    0x3F, // O
    0x73, // P
    0x67, // Q
    0x50, // R
    0x6D, // S
    0x78, // T
    0x3E, // U
    0x00, // V
    0x00, // W
    0x00, // X
    0x6E, // Y
    0x00, // Z
    0x39, // [
    0x01, //
    0x0F, // ]
    0x00, // ^
    0x08, // _
    0x02, // `
    0x5F, // a
    0x7C, // b
    0x58, // c
    0x5E, // d
    0x7B, // e
    0x71, // f
    0x6F, // g
    0x74, // h
    0x04, // i
    0x1E, // j
    0x00, // k
    0x38, // l
    0x00, // m
    0x54, // n
    0x5C, // o
    0x73, // p
    0x67, // q
    0x50, // r
    0x6D, // s
    0x78, // t
    0x1C, // u
    0x00, // v
    0x00, // w
    0x00, // x
    0x6E, // y
    0x00, // z
    0x39, // {
    0x30, // |
    0x0F, // }
};

uint8_t char_to_register(char const c) {
  return font_table[static_cast<int>(c - ' ')];
}

uint8_t chars_to_register(char const c1, char const c2) {
  auto r = char_to_register(c1);
  if (c2 == '.') {
    r |= char_to_register(c2);
  }
  return r;
}

std::array<uint8_t, num_tubes> format_string(std::string const s) {
  std::array<uint8_t, num_tubes> tubes;
  auto i = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    char const c1 = *it;
    char c2 = ' ';
    if (it + 1 != s.end() && *(it + 1) == '.') {
      c2 = *(++it);
    }
    tubes[i++] = chars_to_register(c1, c2);
    if (i >= 8) {
      break;
    }
  }
  return tubes;
}

void write(std::array<uint8_t, num_tubes> const data) {
  digitalWrite(latch_pin, LOW);
  for (int tube = num_tubes - 1; tube >= 0; --tube) {
    shiftOut(data_pin, clock_pin, MSBFIRST, data[tube]);
  }
  digitalWrite(latch_pin, HIGH);
}

void clear() { write({0, 0, 0, 0, 0, 0, 0, 0}); }

void write_string(const std::string s) { write(format_string(s)); }

void init() {
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);

  clear();
}
} // namespace vfd

enum class Mode {
  blank,
  text,
  time,
};

class VfdRegisterOutput : public Component, public CustomAPIDevice {
public:
  VfdRegisterOutput() : Component(), CustomAPIDevice(), m_mode(Mode::time) {}

  void setup() override {
    vfd::init();

    register_service(&VfdRegisterOutput::clear, "clear");
    register_service(&VfdRegisterOutput::show_time, "show_time");
    register_service(&VfdRegisterOutput::show_text, "show_text", {"text"});
  }

  void loop() {
    switch (m_mode) {
    case Mode::time:
      static auto last_t = id(device_time).now();
      auto const t = id(device_time).now();
      if (last_t.second != t.second) {
        char s[9];
        snprintf(s, 9, "%.2d %.2d %.2d", t.hour, t.minute, t.second);
        vfd::write_string(std::string(s));
        last_t = t;
      }
      break;
    }
  }

  void clear() { vfd::clear(); }

  void show_time() { m_mode = Mode::time; }

  void show_text(std::string const t) {
    m_mode = Mode::text;
    vfd::write_string(t);
  }

private:
  Mode m_mode;
};
