#include <Arduino.h>
#include <FastLED.h>
#include <map>
#include <vector>

#define DATA_PIN 6
// #define NUM_LEDS 300
#define NUM_LEDS 20

// define the LED strip
CRGB leds[NUM_LEDS];
int first_led = 0;
int last_led = NUM_LEDS - 1;

// setup defaults
int setup_delay = 2000;
uint8_t default_brightness = 50;

// define the default delay time
int default_delay = 500;

// define the default off color
CRGB default_off_color = CRGB::Black;

// define the min/max hue values
uint8_t min_hue = 0;
uint8_t max_hue = 255;

void led_assign(int led_num, CRGB color, int delay_time = default_delay) {
  leds[led_num] = color;
  FastLED.show();
  delay(delay_time);
}

void led_blink(int led_num, CRGB on_color, CRGB off_color = default_off_color, int delay_time = default_delay) {
  led_assign(led_num, on_color, delay_time);
  led_assign(led_num, off_color, delay_time);
}

void led_assign_all(CRGB color, int delay_time = default_delay) {
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(delay_time);
}

void led_blink_all(CRGB on_color, CRGB off_color = default_off_color, int delay_time = default_delay) {
  led_assign_all(on_color, delay_time);
  led_assign_all(off_color, delay_time);
}

void led_scan_forward(CRGB on_color, CRGB off_color = default_off_color, int delay_time = default_delay) {
  for (int i = first_led; i <= last_led; i++) {
    led_assign(i, on_color, delay_time);
    leds[i] = off_color;
  }
}

void led_scan_backward(CRGB on_color, CRGB off_color = default_off_color, int delay_time = default_delay) {
  for (int i = last_led; i >= first_led; i--) {
    led_assign(i, on_color, delay_time);
    leds[i] = off_color;
  }
}

void led_scanner(CRGB on_color, CRGB off_color = default_off_color, int delay_time = default_delay / 5) {
  led_scan_forward(on_color, off_color, delay_time);
  led_scan_backward(on_color, off_color, delay_time);
}

void led_chase_forward(CRGB on_color, CRGB off_color = default_off_color, int delay_time = default_delay) {
  for (int i = first_led; i <= last_led; i++) {
    led_assign(i, on_color, delay_time);
  }
}

void led_chase_backward(CRGB on_color, CRGB off_color = default_off_color, int delay_time = default_delay) {
  for (int i = last_led; i >= first_led; i--) {
    led_assign(i, on_color, delay_time);
  }
}

void led_chaser(std::vector<CRGB> colors, int delay_time = default_delay / 5) {
  for (size_t color_index = 0; color_index < colors.size(); color_index++) {
    if (color_index % 2 == 0) {
      led_chase_forward(colors[color_index], default_off_color, delay_time);
    } else {
      led_chase_backward(colors[color_index], default_off_color, delay_time);
    }
  }
}

void led_gradient(CRGB color1, CRGB color2, CRGB color3, CRGB color4, int delay_time = default_delay) {
  fill_gradient_RGB (leds, NUM_LEDS, color1, color2, color3, color4);
  FastLED.show();
  delay(delay_time);
}

void led_rainbow(uint8_t initial_hue = min_hue, uint8_t final_hue = max_hue, int delay_time = default_delay * 2) {
  // initial_hue and final_hue should not be the same
  fill_rainbow(leds, NUM_LEDS, initial_hue, final_hue);
  FastLED.show();
  delay(delay_time);
}

void test_led_assign() {
  std::map<int, CRGB> led_colors = {
    {0, CRGB::Red},
    {1, CRGB::Green},
    {2, CRGB::Blue},
    {3, CRGB::Yellow},
    {4, CRGB::Cyan},
    {5, CRGB::Magenta},
    {6, CRGB::White},
    {7, CRGB::Orange},
    {8, CRGB::Purple}
  };
  for (auto const& [led_num, color] : led_colors) {
    led_assign(led_num, color);
  }

  for (auto const& [led_num, color] : led_colors) {
    led_assign(led_num, default_off_color);
  }
}

void test_led_blink() {
  std::map<int, CRGB> led_colors = {
    {0, CRGB::Red},
    {1, CRGB::Green},
    {2, CRGB::Blue},
    {3, CRGB::Yellow},
    {4, CRGB::Cyan},
    {5, CRGB::Magenta},
    {6, CRGB::White},
    {7, CRGB::Orange},
    {8, CRGB::Purple},
    {9, CRGB::Pink}
  };
  for (auto const& [led_num, color] : led_colors) {
    led_blink(led_num, color);
  }
}

void test_led_assign_all() {
  std::vector<CRGB> colors = {
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue,
    default_off_color
  };
  for (const auto& color : colors) {
    led_assign_all(color);
  }
}

void test_led_blink_all() {
  std::vector<CRGB> colors = {
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue,
    CRGB::Magenta
  };
  for (const auto& color : colors) {
    led_blink_all(color);
  }
}

void test_led_scanner() {
  CRGB on_color = CRGB::Red;
  CRGB off_color = default_off_color;

  led_scanner(on_color, off_color);
}

void test_led_chaser(int delay_time = 0) {
  std::vector<CRGB> colors = {
    CRGB::Red,
    CRGB::Green,
    CRGB::Blue,
    default_off_color
  };
  led_chaser(colors);
}

void test_led_gradient() {
  std::vector<std::vector<CRGB>> color_lists = {
    {CRGB::Red, CRGB::Green, CRGB::Blue, CRGB::Cyan},
    {CRGB::Cyan, CRGB::Magenta, CRGB::Yellow, CRGB::White},
    {CRGB::Orange, CRGB::Purple, CRGB::Pink, CRGB::Cyan},
    {CRGB::White, CRGB::Gray, CRGB::BlueViolet, CRGB::Black}
  };

  for (const auto& colors : color_lists) {
    if (colors.size() == 4) {
      led_gradient(colors[0], colors[1], colors[2], colors[3]);
    }
  }

  led_assign_all(default_off_color);
}

void setup() {
  // GRB indicates the ordering of the colors in the LEDs
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(default_brightness);
  delay(setup_delay);

  // test_led_assign();
  // test_led_blink();

  // test_led_assign_all();
  // test_led_blink_all();

  // test_led_scanner();

  // test_led_chaser();

  // test_led_gradient();

  // led_rainbow();

  int led_num = 0;
  leds[led_num] = CRGB::Red;
  FastLED.show();

  delay(1000);

  // int fade_counter = 60;

  // for (int i = 0; i <= 60; i++) {
  //   leds[led_num].maximizeBrightness(fade_counter);
  //   FastLED.show();
  //   delay(500);
  //   fade_counter--;
  // }


  // leds[led_num].maximizeBrightness();
  // leds[led_num].fadeLightBy(200);
  // leds[led_num].nscale8_video(255 - i);
  // FastLED.show();
  // delay(500);


  // for (int i = 125; i <= 200; i++) {
  //   // leds[led_num].maximizeBrightness();
  //   leds[led_num].fadeLightBy(i);
  //   // leds[led_num].nscale8_video(255 - i);
  //   FastLED.show();
  //   delay(500);
  // }

  // for (int i = 128; i >= 60; i--) {
  //   led.maximizeBrightness();
  //   led.fadeLightBy(i);
  //   // leds[led_num].nscale8_video(255 - i);
  //   FastLED.show();
  //   delay(500);
  // }
}

void loop() {
  // code to iterate over goes here
}
