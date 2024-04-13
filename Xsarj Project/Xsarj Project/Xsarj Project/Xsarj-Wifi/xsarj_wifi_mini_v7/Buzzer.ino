unsigned long previousMillis_buzzer_timer = 0;
const long interval_buzzer_timer = 300;
int buzzer_counter = 0;

void blink_Buzzer() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_buzzer_timer >= interval_buzzer_timer) {
    previousMillis_buzzer_timer = currentMillis;
    buzzer_counter++;
    if (buzzer_counter % 2 == 0) {
      relay_2_cloud_value = "1";
    }
    if (buzzer_counter % 2 == 1) {
      relay_2_cloud_value = "0";
    }
  }
}
