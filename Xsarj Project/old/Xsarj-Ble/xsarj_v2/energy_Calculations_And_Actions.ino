//Json To String Coverter Link: https://jsontostring.com/

unsigned long previousMillis_relay_1_timer = 0;
const long interval_relay_1_timer = 1000;

unsigned long previousMillis_plug_timer = 0;
const long interval_plug_timer = 1000;

String server_url = "http://185.114.21.200:8069";

void energy_Analyzer_Relay_1() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis_relay_1_timer >= interval_relay_1_timer) {
    previousMillis_relay_1_timer = currentMillis;
    if (relay_1_cloud_value == "1" && error_code_6 == "0") {
      if (sensor_2_value > 1.5) {
        charge_counter++;
        no_charging_counter = 0;
        sum_of_power += sensor_1_value;
        //      Serial.print("charge counter: ");
        //      Serial.println(charge_counter);
        error_code_1 = "1";
        Serial.print("sum_of_power/charge_counter: ");
        Serial.println(sum_of_power / charge_counter);
      }
      if (sensor_2_value <= 1.5) {
        no_charging_counter++;
      }
    }
    if (relay_1_cloud_value == "1" && relay_1_cloud_value != relay_1_cloud_value_last) {
      no_charging_counter = 0;
      plug_in_but_no_charge_counter = 0;
      error_code_1 = "0";
      error_code_2 = "0";
      error_code_3 = "0";
      error_code_4 = "0";
      error_code_5 = "0";
      error_code_6 = "0";
      error_code_7 = "0";
      error_code_8 = "0";
      error_code_9 = "0";
      error_code_10 = "0";
      error_code_11 = "0";
      error_code_12 = "0";
      error_code_13 = "0";
      error_code_14 = "0";
      error_code_15 = "0";
      error_code_16 = "0";
      error_code_17 = "0";
      relay_11_cloud_value = 1;
      digitalWrite(relay_11, relay_11_cloud_value.toInt());
      delay(100);
      read_Sensors();
      start_Charge_Data();
      charge_counter = 0;
      charge_cost = "0";
      sum_of_power = 0;
      start_charge_data_counter = 0;
      http_Get_Partner_Total_Payment();
      Serial.print("Partner Id: ");
      Serial.print(partner_id);
      Serial.print(" partner_total_payment_from_firebase: ");
      Serial.println(partner_total_payment_from_firebase);
      Serial.println("---- All Datas RESETED AND CHARGE is Started ----");
      error_code_2 = "1";
      relay_1_cloud_value_last = relay_1_cloud_value;
      relay_2_cloud_value_last = relay_2_cloud_value;
      relay_3_cloud_value_last = relay_3_cloud_value;
      if (partner_total_payment_from_firebase.toInt() > 0) {
        wifi_Ntc_Time_Setup();
      }
    }

    
    if (relay_1_cloud_value == "0" && relay_1_cloud_value != relay_1_cloud_value_last) {
      relay_11_cloud_value = "0";
      charge_state_from_module = 0;
      // Arrange Current Of Evse
      control_Relays();
      stop_Charge_Data();
      digitalWrite(relay_11, relay_11_cloud_value.toInt());
      relay_1_cloud_value_last = relay_1_cloud_value;
      relay_2_cloud_value_last = relay_2_cloud_value;
      relay_3_cloud_value_last = relay_3_cloud_value;
      wifi_Ntc_Time_Setup();
      if (charge_counter >= 0) {
        charge_cost = String(((sum_of_power/3600) * (-1 * package_price_1)));
        Serial.println("----------------------charge Finished ------------------------------: ");
        Serial.print("charge_cost: ");
        Serial.println(charge_cost);
        error_code_3 = "1";
        create_New_Sale_Offer();
        //charge_counter = 0;
        relay_16_cloud_value = "4"; //Charge Works Well Value
        sensor_1_value = 0;
        sensor_2_value = 0;
      }
    }
  }
}

void charge_Time_plug_Out_Status() {
  if (relay_1_cloud_value == "1" && sensor_2_value < 1.5 && no_charging_counter > 60) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis_plug_timer >= interval_plug_timer) {
      previousMillis_plug_timer = currentMillis;
      plug_in_but_no_charge_counter++;
      if (plug_in_but_no_charge_counter == 60) {
        relay_16_cloud_value = "3"; //Plug in But No Charge
        Serial.print("Charge Alert: ");
        Serial.println("Plug is open but there is no charge");
        relay_1_cloud_value = "0";
        relay_2_cloud_value = "0";
        relay_3_cloud_value = "0";
      }
      if (plug_in_but_no_charge_counter == 180) {
        wifi_Ntc_Time_Setup();
        if (charge_counter >= 0) {
          charge_cost = String(((sum_of_power/3600) * (-1 * package_price_1)));
          http_Put_Request_Change_Partner_Payment();
          http_Post_Request_Create_New_Charge_Cost();
          Serial.print("charge_cost: ");
          Serial.println(charge_cost);
          error_code_4 = "1";
          //charge_counter = 0;
          sensor_1_value = 0;
          sensor_2_value = 0;
          plug_in_but_no_charge_counter = 0;
        }
      }
    }
  }
  if (relay_1_cloud_value == "1" && sensor_2_value > 1) {
    error_code_5 = "1";
    relay_16_cloud_value = "4"; //Charge Works Well Value
  }
}

void check_Money_Finish() {
  if (charge_counter > 0) {
    charge_cost = String(((sum_of_power/3600) * (-1 * package_price_1)));
    if (-1*charge_cost.toFloat() >= (partner_total_payment - package_price_1 - 2)) {
      relay_1_cloud_value = "0";
      relay_2_cloud_value = "0";
      relay_3_cloud_value = "0";
      control_Relays();
      error_code_6 = "1";
      Serial.println("-------------------------money_finished---------------------------"); 
    }
  }
}

void http_Get_Partner_Total_Payment() {
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;
    http.begin(server_url + "/api/sale.order/?query={id,partner_id,name,invoice_status,amount_total}&filter=[[\"partner_id\",\"=\"," + partner_id + "]]"); //Specify the URL

    http.addHeader("Cookie", auth_session_id);
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.addHeader("Accept", "*/*");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Connection", "keep-alive");

    int httpCode = http.GET();

    if (httpCode > 0) { //Check for the returning code
      String payload = http.getString();
      parse_Partner_Payment_Json(String(payload));
      Serial.println(httpCode);
      Serial.println(payload);
    }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end(); //Free the resources
  }
}

void http_Put_Request_Change_Partner_Payment() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    //9cbad2a3c975a8942985b8abc1cf53a37e35fe98
    http.begin(server_url + "/api/sale.order/");
    http.addHeader("Cookie", auth_session_id);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.addHeader("Accept", "*/*");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Connection", "keep-alive");

    int httpResponseCode = http.PUT("{\"params\":{\"filter\":[[\"id\",\"=\"," + String(last_payment_id) + "]],\"data\":{\"amount_total\":" + String(charge_cost) + "}}}");

    if (httpResponseCode > 0) {

      String response = http.getString();

      Serial.println(httpResponseCode);
      Serial.println(response);

    } else {

      Serial.print("Error on sending PUT Request: ");
      Serial.println(httpResponseCode);

    }

    http.end();

  } else {
    Serial.println("Error in WiFi connection");
  }
}

void http_Post_Request_Create_New_Charge_Cost() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    //9cbad2a3c975a8942985b8abc1cf53a37e35fe98
    http.begin(server_url + "/web/dataset/call_kw/purchase.order/create");
    http.addHeader("Cookie", auth_session_id);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.addHeader("Accept", "*/*");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Connection", "keep-alive");

    int httpResponseCode = http.POST("{\"jsonrpc\":\"2.0\",\"method\":\"call\",\"params\":{\"args\":[{\"currency_id\":31,\"date_order\":\"2021-10-18 12:30:29\",\"company_id\":1,\"picking_type_id\":1,\"user_id\":9,\"partner_id\":" + partner_id + ",\"partner_ref\":false,\"origin\":false,\"order_line\":[[0,\"virtual_177\",{\"display_type\":false,\"sequence\":10,\"product_id\":12,\"name\":\"Elektrik Şarj Harcaması\",\"date_planned\":\"2021-10-18 12:30:29\",\"account_analytic_id\":false,\"product_qty\":1,\"qty_received_manual\":0,\"qty_received\":0,\"product_uom\":1,\"price_unit\":" + String((charge_cost.toFloat() / 118) * 100) + ",\"taxes_id\":[[6,false,[2]]]}]],\"notes\":false,\"date_planned\":false,\"dest_address_id\":false,\"incoterm_id\":false,\"payment_term_id\":false,\"fiscal_position_id\":false,\"message_attachment_count\":0}],\"model\":\"purchase.order\",\"method\":\"create\",\"kwargs\":{\"context\":{\"lang\":\"tr_TR\",\"tz\":\"Europe/Istanbul\",\"uid\":9,\"allowed_company_ids\":[1],\"quotation_only\":true}}},\"id\":131834807}");

    if (httpResponseCode > 0) {

      String response = http.getString();

      Serial.println(httpResponseCode);
      Serial.println(response);

    } else {

      Serial.print("Error on sending Post Create Request: ");
      Serial.println(httpResponseCode);

    }

    http.end();

  } else {
    Serial.println("Error in WiFi connection");
  }
}

void parse_Partner_Payment_Json(String response) {
  DynamicJsonBuffer  jsonBuffer(200);
  JsonObject& root = jsonBuffer.parseObject(response);
  if (!root.success()) {
    Serial.println("parseObject() failed");
  }
  int count = root["count"];
  partner_total_payment = 0.0;
  for (int i = 0; i < count; i++) {
    String invoice_status = root["result"][i]["invoice_status"];
    if (invoice_status != "no") {
      last_payment_id = root["result"][i]["id"];
      String partner_payment = root["result"][i]["amount_total"];
      last_invoice_payment = root["result"][i]["amount_total"];
      partner_total_payment = partner_payment.toFloat() + partner_total_payment;
    }
  }
  Serial.print("partner_total_payment:");
  Serial.println(partner_total_payment);
  Serial.print(" last_payment_id:");
  Serial.println(last_payment_id);
  Serial.print(" last_invoice_payment:");
  Serial.println(last_invoice_payment);
}

void finish_Charge_Because_Of_Money() {
  String realtime_money_at_customer = String(partner_total_payment + (charge_counter * -0.004166));
  if (realtime_money_at_customer.toFloat() == 10.0 && relay_1_cloud_value == "1") {
    relay_15_cloud_value = "2"; //Money is going down alert
  }
  if (realtime_money_at_customer.toFloat() == 0.00 && relay_1_cloud_value == "1") {
    relay_15_cloud_value = "3"; //Money finished
    relay_1_cloud_value == "0";
    relay_2_cloud_value == "0";
    relay_3_cloud_value == "0";
  }
}

void create_New_Sale_Offer() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    //9cbad2a3c975a8942985b8abc1cf53a37e35fe98
    http.begin(server_url + "/web/dataset/call_kw/sale.order/create");
    http.addHeader("Cookie", auth_session_id);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.addHeader("Accept", "*/*");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Connection", "keep-alive");

    int httpResponseCode = http.POST("{\"jsonrpc\":\"2.0\",\"method\":\"call\",\"params\":{\"args\":[{\"sale_order_template_id\":false,\"validity_date\":false,\"date_order\":\"2021-11-03 14:26:38\",\"note\":\"\",\"user_id\":9,\"team_id\":2,\"company_id\":1,\"require_signature\":false,\"require_payment\":false,\"warehouse_id\":1,\"picking_policy\":\"direct\",\"partner_id\":" + partner_id + ",\"partner_invoice_id\":" + partner_id + ",\"partner_shipping_id\":" + partner_id + ",\"pricelist_id\":1,\"payment_term_id\":false,\"order_line\":[[0,\"virtual_5715\",{\"sequence\":10,\"display_type\":false,\"product_uom_qty\":1,\"qty_delivered\":0,\"qty_delivered_manual\":0,\"customer_lead\":0,\"product_packaging\":false,\"price_unit\":" + charge_cost + ",\"discount\":0,\"product_id\":12,\"product_template_id\":96,\"name\":\"ElektrikŞarjHarcaması\",\"route_id\":false,\"product_uom\":1,\"tax_id\":[[6,false,[1]]]}]],\"cart_recovery_email_sent\":false,\"client_order_ref\":false,\"fiscal_position_id\":false,\"analytic_account_id\":false,\"incoterm\":false,\"commitment_date\":false,\"origin\":false,\"opportunity_id\":false,\"campaign_id\":false,\"medium_id\":false,\"source_id\":false,\"signed_by\":false,\"signed_on\":false,\"signature\":false,\"__last_update\":false,\"message_attachment_count\":0}],\"model\":\"sale.order\",\"method\":\"create\",\"kwargs\":{\"context\":{\"lang\":\"tr_TR\",\"tz\":false,\"uid\":9,\"allowed_company_ids\":[1]}}},\"id\":361643890}");

    if (httpResponseCode > 0) {

      String response = http.getString();
      Serial.println("----------Create New Sale Offer-----------");
      Serial.println(httpResponseCode);
      Serial.println(response);

      if (response.indexOf("jsonrpc") > 0 && response.indexOf("result") > 0 ) {
        DynamicJsonBuffer  jsonBuffer(200);
        JsonObject& root = jsonBuffer.parseObject(response);
        if (!root.success()) {
          Serial.println("parseObject() failed");
        }
        unsigned long result = root["result"];
        Serial.print(" result: ");
        Serial.println(result);
        validate_New_Sale_Offer(result);
      }

    } else {

      Serial.print("Error on sending Post Create Request: ");
      Serial.println(httpResponseCode);

    }

    http.end();

  } else {
    Serial.println("Error in WiFi connection");
  }
}

void validate_New_Sale_Offer(unsigned long result) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    //9cbad2a3c975a8942985b8abc1cf53a37e35fe98
    http.begin(server_url + "/web/dataset/call_button");
    http.addHeader("Cookie", auth_session_id);
    http.addHeader("Content-Type", "application/json");
    http.addHeader("User-Agent", "PostmanRuntime/7.26.8");
    http.addHeader("Accept", "*/*");
    http.addHeader("Accept-Encoding", "gzip, deflate, br");
    http.addHeader("Connection", "keep-alive");

    int httpResponseCode = http.POST("{\"jsonrpc\":\"2.0\",\"method\":\"call\",\"params\":{\"args\":[[" + String(result) + "]],\"kwargs\":{\"context\":{\"lang\":\"tr_TR\",\"tz\":false,\"uid\":9,\"allowed_company_ids\":[1],\"params\":{\"action\":381,\"cids\":1,\"menu_id\":251,\"model\":\"sale.order\",\"view_type\":\"list\"}}},\"method\":\"action_confirm\",\"model\":\"sale.order\"},\"id\":987933804}");

    if (httpResponseCode > 0) {

      String response = http.getString();

      Serial.println(httpResponseCode);
      Serial.println(response);

    } else {

      Serial.print("Error on sending Post Create Request: ");
      Serial.println(httpResponseCode);

    }

    http.end();

  } else {
    Serial.println("Error in WiFi connection");
  }
}
