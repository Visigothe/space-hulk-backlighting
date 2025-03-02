#include <Arduino.h>
#include <FastLED.h>

#define LED_PIN     6
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    160
// each strip has 40 LEDs

#define BRIGHTNESS  128
#define OFF_COLOR CRGB::Black
#define DEFAULT_DELAY 500

CRGB leds[NUM_LEDS];

void led_assign(int led_num, CRGB color, int delay_time = DEFAULT_DELAY) {
  leds[led_num] = color;
  FastLED.show();
  delay(delay_time);
}

void led_assign_all(CRGB color, int delay_time = DEFAULT_DELAY) {
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(delay_time);
}

uint8_t hue_max = 255;
uint8_t hue_min = 3;
uint8_t hue_range = hue_max - hue_min;
int fade_steps = 21;
uint8_t fade_step = hue_range / fade_steps;
int fade_range = 5;

void adjacent_fade(int central_led, int adjacent_led_count, uint8_t base_hue) {
    if (adjacent_led_count == 0) return;
    for (int j = 1; j <= adjacent_led_count; j++) {
        uint8_t next_hue = base_hue + j * fade_step;
        if (next_hue > hue_max) next_hue = hue_max;
        leds[central_led + j] = CRGB(next_hue, 0, 0);
        leds[central_led - j] = CRGB(next_hue, 0, 0);
    }
}

void fade_down(int central_led) {
    for (int i = 0; i <= fade_steps; i++) {
        uint8_t base_hue = hue_max - i * fade_step;
        if (base_hue < hue_min) base_hue = hue_min;
        leds[central_led] = CRGB(base_hue, 0, 0);
        int adjacent_led_count = (i > fade_range) ? fade_range : i;
        adjacent_fade(central_led, adjacent_led_count, base_hue);
        FastLED.show();
        delay(50);
    }
}

void fade_up(int central_led) {
    for (int i = fade_steps; i >= 0; i--) {
        uint8_t base_hue = hue_max - i * fade_step;
        if (base_hue > hue_max) base_hue = hue_max;
        leds[central_led] = CRGB(base_hue, 0, 0);
        int adjacent_led_count = (i < fade_range) ? i : fade_range;
        adjacent_fade(central_led, adjacent_led_count, base_hue);
        FastLED.show();
        delay(50);
    }
}

void setup() {
    delay(3000); // sanity delay
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness( BRIGHTNESS );

    led_assign_all(OFF_COLOR);
    FastLED.show(); // display this frame
    delay(1000);

    led_assign_all(CRGB::Red);
    FastLED.show(); // display this frame
    delay(1000);
}

void loop() {
    // int random_led = 5;

    int random_led = random(5, NUM_LEDS - 5);

    fade_down(random_led);
    delay(1000);
    fade_up(random_led);
    delay(1000);
}
