unsigned long previousMillis_energy_serial_timer = 0;
const long interval_energy_serial_timer = 2000;

void read_Energy_Serial() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_energy_serial_timer >= interval_energy_serial_timer) {
    previousMillis_energy_serial_timer = currentMillis;
    Serial.print("Custom Address:");
    Serial.println(pzem.readAddress(), HEX);

    // Read the data from the sensor
    float voltage = pzem.voltage();
    float current = pzem.current();
    float power = pzem.power();
    float energy = pzem.energy();
    float frequency = pzem.frequency();
    float pf = pzem.pf();

    // Check if the data is valid
    if (isnan(voltage)) {
      Serial.println("Error reading voltage");
      error_code_7 = "1";
    } else if (isnan(current)) {
      Serial.println("Error reading current");
      error_code_8 = "1";
    } else if (isnan(power)) {
      Serial.println("Error reading power");
      error_code_9 = "1";
    } else if (isnan(energy)) {
      Serial.println("Error reading energy");
      error_code_10 = "1";
    } else if (isnan(frequency)) {
      Serial.println("Error reading frequency");
      error_code_11 = "1";
    } else if (isnan(pf)) {
      Serial.println("Error reading power factor");
    } else {

      // Print the values to the Serial console
      sensor_1_value = power/1000;
      sensor_2_value = current;
      sensor_3_value = voltage;
      sensor_4_value = pf;
      
      Serial.println("-------");
      Serial.print("Voltage: ");      Serial.print(voltage);      Serial.println("V");
      Serial.print("Current: ");      Serial.print(current);      Serial.println("A");
      Serial.print("Power: ");        Serial.print(power);        Serial.println("W");
      Serial.print("Energy: ");       Serial.print(energy, 3);     Serial.println("kWh");
      Serial.print("Frequency: ");    Serial.print(frequency, 1); Serial.println("Hz");
      Serial.print("PF: ");           Serial.println(pf);
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
