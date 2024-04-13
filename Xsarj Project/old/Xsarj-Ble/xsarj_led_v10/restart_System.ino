void restart_System(){
  sys_reset_value = 1;
  gsm_reset_value = 1;
//  swSer1_Send_Reset_Data();
//  delay(500);
//  swSer1_Send_Reset_Data();
//  delay(500);
//  swSer1_Send_Reset_Data();
//  delay(500);
//  swSer1_Send_Reset_Data();
  delay(500);
  ESP.restart();
  }
