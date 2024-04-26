unsigned long previousMillis_energy_serial_timer = 0;
const long interval_energy_serial_timer = 2000;

void read_Energy_Serial() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_energy_serial_timer >= interval_energy_serial_timer) {
    previousMillis_energy_serial_timer = currentMillis;
    Serial.print("Custom Address:");
    Serial.println(pzem1.readAddress(), HEX);

    // Read the data from the pzem sensor 1
    voltage_1 = pzem1.voltage();
    current_1 = pzem1.current();
    power_1 = pzem1.power();
    energy_1 = pzem1.energy();
    frequency_1 = pzem1.frequency();
    pf_1 = pzem1.pf();

    // Read the data from the sensorpzem sensor 2
    voltage_2 = pzem2.voltage();
    current_2 = pzem2.current();
    power_2 = pzem2.power();
    energy_2 = pzem2.energy();
    frequency_2 = pzem2.frequency();
    pf_2 = pzem2.pf();

    // Read the data from the pzem sensor 3
    voltage_3 = pzem3.voltage();
    current_3 = pzem3.current();
    power_3 = pzem3.power();
    energy_3 = pzem3.energy();
    frequency_3 = pzem3.frequency();
    pf_3 = pzem3.pf();

    // Check if the data is valid
    if (isnan(voltage_1)) {
      Serial.println("Error reading voltage-1");
      error_code_7 = "1";
      voltage_1 = 0;
    } else if (isnan(current_1)) {
      Serial.println("Error reading current-1");
      error_code_8 = "1";
      current_1 = 0;
    } else if (isnan(power_1)) {
      Serial.println("Error reading power-1");
      error_code_9 = "1";
      power_1 = 0;
    } else if (isnan(energy_1)) {
      Serial.println("Error reading energy-1");
      error_code_10 = "1";
      energy_1 = 0;
    } else if (isnan(frequency_1)) {
      Serial.println("Error reading frequency-1");
      error_code_11 = "1";
      frequency_1 = 0;
    } else if (isnan(pf_1)) {
      Serial.println("Error reading power factor-1");
      pf_1 = 0;
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
    }


    // Check if the data is valid
    if (isnan(voltage_2)) {
      Serial.println("Error reading voltage-2");
      voltage_2 = 0;
    } else if (isnan(current_2)) {
      Serial.println("Error reading current-2");
      current_2 = 0;
    } else if (isnan(power_2)) {
      Serial.println("Error reading power-2");
      power_2 = 0;
    } else if (isnan(energy_2)) {
      Serial.println("Error reading energy-2");
      energy_2 = 0;
    } else if (isnan(frequency_2)) {
      Serial.println("Error reading frequency-2");
      frequency_2 = 0;
    } else if (isnan(pf_2)) {
      Serial.println("Error reading power factor-2");
      pf_2 = 0;
    } else {

      Serial.println("-------");
      Serial.print("Voltage_2: ");      Serial.print(voltage_2);      Serial.println("V");
      Serial.print("Current_2: ");      Serial.print(current_2);      Serial.println("A");
      Serial.print("Power_2: ");        Serial.print(power_2);        Serial.println("W");
      Serial.print("Energy_2: ");       Serial.print(energy_2, 3);     Serial.println("kWh");
      Serial.print("Frequency_2: ");    Serial.print(frequency_2, 1); Serial.println("Hz");
      Serial.print("PF_2: ");           Serial.println(pf_2);
      Serial.println("-------");
      Serial.println(" ");
    }

    // Check if the data is valid
    if (isnan(voltage_3)) {
      Serial.println("Error reading voltage-3");
      voltage_3 = 0;
    } else if (isnan(current_3)) {
      Serial.println("Error reading current-3");
      current_3 = 0;
    } else if (isnan(power_3)) {
      Serial.println("Error reading power-3");
      power_3 = 0;
    } else if (isnan(energy_3)) {
      Serial.println("Error reading energy-3");
      energy_3 = 0;
    } else if (isnan(frequency_3)) {
      Serial.println("Error reading frequency-3");
      frequency_3 = 0;
    } else if (isnan(pf_3)) {
      Serial.println("Error reading power factor-3");
      pf_3 = 0;
    } else {

      Serial.println("-------");
      Serial.print("Voltage_3: ");      Serial.print(voltage_3);      Serial.println("V");
      Serial.print("Current_3: ");      Serial.print(current_3);      Serial.println("A");
      Serial.print("Power_3: ");        Serial.print(power_3);        Serial.println("W");
      Serial.print("Energy_3: ");       Serial.print(energy_3, 3);     Serial.println("kWh");
      Serial.print("Frequency_3: ");    Serial.print(frequency_3, 1); Serial.println("Hz");
      Serial.print("PF_3: ");           Serial.println(pf_3);
      Serial.println("-------");
      Serial.println(" ");
    }

    if (voltage_1 > 200) {
      sensor_1_value = (voltage_1 * current_1) / 1000;
    }
    if (voltage_1 > 200 && voltage_2 > 200 && voltage_3 > 200) {
      sensor_1_value = (voltage_1 * current_1 + voltage_2 * current_2 + voltage_3 * current_3) / 1000;
    }
  }
}
