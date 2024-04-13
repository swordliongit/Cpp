unsigned long previousMillis_energy_serial_timer = 0;
const long interval_energy_serial_timer = 2000;

void read_Energy_Serial() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_energy_serial_timer >= interval_energy_serial_timer) {
    previousMillis_energy_serial_timer = currentMillis;
    Serial.print("Custom Address:");
    Serial.println(pzem1.readAddress(), HEX);

    // Read the data from the pzem sensor 1
    float voltage_1 = pzem1.voltage();
    float current_1 = pzem1.current();
    float power_1 = pzem1.power();
    float energy_1 = pzem1.energy();
    float frequency_1 = pzem1.frequency();
    float pf_1 = pzem1.pf();

    // Read the data from the sensorpzem sensor 2
    float voltage_2 = pzem2.voltage();
    float current_2 = pzem2.current();
    float power_2 = pzem2.power();
    float energy_2 = pzem2.energy();
    float frequency_2 = pzem2.frequency();
    float pf_2 = pzem2.pf();

    // Read the data from the pzem sensor 3
    float voltage_3 = pzem3.voltage();
    float current_3 = pzem3.current();
    float power_3 = pzem3.power();
    float energy_3 = pzem3.energy();
    float frequency_3 = pzem3.frequency();
    float pf_3 = pzem3.pf();

    // Check if the data is valid
    if (isnan(voltage_1)) {
      Serial.println("Error reading voltage");
      error_code_7 = "1";
    } else if (isnan(current_1)) {
      Serial.println("Error reading current");
      error_code_8 = "1";
    } else if (isnan(power_1)) {
      Serial.println("Error reading power");
      error_code_9 = "1";
    } else if (isnan(energy_1)) {
      Serial.println("Error reading energy");
      error_code_10 = "1";
    } else if (isnan(frequency_1)) {
      Serial.println("Error reading frequency");
      error_code_11 = "1";
    } else if (isnan(pf_1)) {
      Serial.println("Error reading power factor");
    } else {

      // Print the values to the Serial console
      if (voltage_1 > 200) {
        sensor_1_value = (voltage_1 * current_1) / 1000;
      }
      if (voltage_1 > 200 && voltage_2 > 200 && voltage_3 > 200) {
        sensor_1_value = (voltage_1 * current_1 + voltage_2 * current_2 + voltage_3 * current_3) / 1000;
      }
      if (sensor_1_value < 0) {
        sensor_1_value = 0;
      }
      sensor_2_value = current_1;
      sensor_3_value = voltage_1;
      sensor_4_value = pf_1;

      Serial.println("-------");
      Serial.print("Voltage_1: ");      Serial.print(voltage_1);      Serial.println("V");
      Serial.print("Current_1: ");      Serial.print(current_1);      Serial.println("A");
      Serial.print("Power_1: ");        Serial.print(power_1);        Serial.println("W");
      Serial.print("Energy_1: ");       Serial.print(energy_1, 3);     Serial.println("kWh");
      Serial.print("Frequency_1: ");    Serial.print(frequency_1, 1); Serial.println("Hz");
      Serial.print("PF_1: ");           Serial.println(pf_1);
      Serial.println("-------");
      Serial.println(" ");

      Serial.println("-------");
      Serial.print("Voltage_2: ");      Serial.print(voltage_2);      Serial.println("V");
      Serial.print("Current_2: ");      Serial.print(current_2);      Serial.println("A");
      Serial.print("Power_2: ");        Serial.print(power_2);        Serial.println("W");
      Serial.print("Energy_2: ");       Serial.print(energy_2, 3);     Serial.println("kWh");
      Serial.print("Frequency_2: ");    Serial.print(frequency_2, 1); Serial.println("Hz");
      Serial.print("PF_2: ");           Serial.println(pf_2);
      Serial.println("-------");
      Serial.println(" ");

      Serial.println("-------");
      Serial.print("Voltage_3: ");      Serial.print(voltage_3);      Serial.println("V");
      Serial.print("Current_3: ");      Serial.print(current_3);      Serial.println("A");
      Serial.print("Power_3: ");        Serial.print(power_3);        Serial.println("W");
      Serial.print("Energy_3: ");       Serial.print(energy_3, 3);     Serial.println("kWh");
      Serial.print("Frequency_3: ");    Serial.print(frequency_3, 1); Serial.println("Hz");
      Serial.print("PF_3: ");           Serial.println(pf_3);
      Serial.println("-------");
      Serial.println(" ");

      Serial.print("Charge Counter: ");
      Serial.println(charge_counter);
      Serial.print("No Charging Counter: ");
      Serial.println(no_charging_counter);
      Serial.print("plug_in_but_no_charge_counter: ");
      Serial.println(plug_in_but_no_charge_counter);
      Serial.print("charge_cost: ");
      Serial.println(charge_cost);
      Serial.print("partner_total_payment: ");
      Serial.println(partner_total_payment);
      Serial.println("-------");

    }
  }
}
