///*
//   EMailSender library for Arduino, esp8266 and esp32
//   Simple esp32 Gmail send example
//
//   https://www.mischianti.org/category/my-libraries/emailsender-send-email-with-attachments/
//
//*/
//uint8_t connection_state = 0;
//uint16_t reconnect_interval = 10000;
//
//EMailSender emailSend(emailsender_mail_adress, emailsender_mail_password);
//
//
//
//void Send_Mail(char* emailtaker_mail_adress, char* mail_header, char* mail_content)
//{
//  if (WiFi.status() == WL_CONNECTED) {
//    EMailSender::EMailMessage message;
//    message.subject = mail_header;
//    message.message = mail_content;
//
//    EMailSender::Response resp = emailSend.send(emailtaker_mail_adress, message);
//
//    Serial.println("Sending status: ");
//
//    Serial.println(resp.status);
//    Serial.println(resp.code);
//    Serial.println(resp.desc);
//  }
//}
