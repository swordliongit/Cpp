unsigned long previousMillis_redled_timer = 0;
const long interval_redled_timer = 500;
int red_led_counter = 0;

unsigned long previousMillis_greenled_timer = 0;
const long interval_greenled_timer = 500;
int green_led_counter = 0;

unsigned long previousMillis_whiteled_timer = 0;
const long interval_whiteled_timer = 500;
int white_led_counter = 0;

unsigned long previousMillis_yellowled_timer = 0;
const long interval_yellowled_timer = 500;
int yellow_led_counter = 0;

void led_blink() {
  unsigned long currentMillis = millis();
  if (led_ligth_color == "red") {
    leds[0] = CRGB::Red;
    FastLED.show();
  }
  if (led_ligth_color == "green") {
    if (currentMillis - previousMillis_greenled_timer >= interval_greenled_timer) {
      previousMillis_greenled_timer = currentMillis;
      green_led_counter++;
    }
    if (green_led_counter % 2 == 0) {
      // Turn the LED on, then pause
      leds[0] = CRGB::Green;
      FastLED.show();
    }
    if (green_led_counter % 2 == 1) {
      // Now turn the LED off, then pause
      leds[0] = CRGB::Black;
      FastLED.show();
    }
    if (green_led_counter == 100) {
      green_led_counter = 0;
    }
  }
  if (led_ligth_color == "white") {
    if (currentMillis - previousMillis_whiteled_timer >= interval_whiteled_timer) {
      previousMillis_whiteled_timer = currentMillis;
      white_led_counter++;
    }
    if (white_led_counter % 2 == 0) {
      // Turn the LED on, then pause
      leds[0] = CRGB::White;
      FastLED.show();
    }
    if (white_led_counter % 2 == 1) {
      // Now turn the LED off, then pause
      leds[0] = CRGB::Black;
      FastLED.show();
    }
    if (white_led_counter == 100) {
      white_led_counter = 0;
    }
  }

  if (led_ligth_color == "yellow") {
    if (currentMillis - previousMillis_yellowled_timer >= interval_yellowled_timer) {
      previousMillis_yellowled_timer = currentMillis;
      yellow_led_counter++;
    }
    if (yellow_led_counter % 2 == 0) {
      // Turn the LED on, then pause
      leds[0] = CRGB::Yellow;
      FastLED.show();
    }
    if (yellow_led_counter % 2 == 1) {
      // Now turn the LED off, then pause
      leds[0] = CRGB::Black;
      FastLED.show();
    }
    if (yellow_led_counter == 100) {
      yellow_led_counter = 0;
    }
  }
}
