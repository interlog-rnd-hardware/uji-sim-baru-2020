void voice_command()
{
    char c = ' ';
 
  if (deteksirfid == 0)
  {
//    c = 'r';
//    sendMP3Command(c);  
    if (stepp == 0)
    {
      c = '1';
      sendMP3Command(c);
      c = 'm';
      sendMP3Command(c);
      delay(12000);
      stepp = 1;
    }

  }

  if(deteksirfid == 1)
  {
    if (stepp == 1)
//    if (stepp == 1 && tagtrack == )
    {
      c = 'n';
      sendMP3Command(c);
      c = 'm';
      sendMP3Command(c);
      delay(3000);
      stepp = 2;
    }

//    if (stepp == 2 && tagtrack == )
//    if (stepp == 2)
//    {
//      
//    }

  }
}

void sendMP3Command(char c) {
  switch (c) {
    case 'h':
    case '?':
      Serial.println("ini instruksinya!");
      Serial.println(" m = mainkan");
      Serial.println(" b = Pause");
      Serial.println(" n = Lagu selanjutnya");
      Serial.println(" p = Lagu sebelumnya");
      Serial.println(" + = Volume naik");
      Serial.println(" - = Volume turun");
      Serial.println(" 1 = Play folder 1");
      Serial.println(" 2 = Play folder 2");
      Serial.println(" 3 = Play folder 3");
      Serial.println(" 4 = Play folder 4");
      Serial.println(" 5 = Play folder 5");
      Serial.println(" r = Reset_mp3");
      break;
 
    case 'm':
      Serial.println("Putar Lagu");
      kirimperintah(mainkan, 0X0D);
      break;
 
    case 'b':
      Serial.println("Lagu Berhenti");
      kirimperintah(pause_mp3, 0X0E);
      break;
 
    case 'n':
      Serial.println("Lagu berikutnya");
      kirimperintah(lagu_berikutnya, 0X01);
      break;
 
    case 'p':
      Serial.println("Lagu sebelumnya");
      kirimperintah(lagu_sebelumnya, 0X02);
      break;
 
    case '+':
      Serial.println("Volume Naik");
      kirimperintah(volume_naik, 0X04);
      break;
 
    case '-':
      Serial.println("Volume Turun");
      kirimperintah(volume_turun, 0X05);
      break;
 
    case '1':
      Serial.println("Masuk ke folder 1");
      kirimperintah(mainkan_folder, 0x0101);
      break;
      
    case '2':
      Serial.println("Masuk ke folder 2");
      kirimperintah(mainkan_folder, 0x0201);
      break;
 
    case '3':
      Serial.println("Masuk ke folder 3");
      kirimperintah(mainkan_folder, 0x0301);
      break;
 
    case '4':
      Serial.println("Masuk ke folder 4");
      kirimperintah(mainkan_folder, 0x0401);
      break;
 
    case '5':
      Serial.println("Masuk ke folder 5");
      kirimperintah(mainkan_folder, 0x0501);
      break;
 
    case 'r':
      Serial.println("Reset settingan");
      kirimperintah(reset_mp3, 0x00);
      break;
      
  }
}

void kirimperintah(int8_t command, int16_t dat)
{
  delay(20);
  buff_send[0] = 0x7e;
  buff_send[1] = 0xff;
  buff_send[2] = 0x06;
  buff_send[3] = command;
  buff_send[4] = 0x00;   // 0x00 NO, 0x01 feedback
  buff_send[5] = (int8_t)(dat >> 8);
  buff_send[6] = (int8_t)(dat);
  buff_send[7] = 0xef;
  
  for (uint8_t i = 0; i < 8; i++)
  {
//    mp3module.write(buff_send[i]) ;
     Serial2.write(buff_send[i]);
     Serial.print(buff_send[i],HEX);
  }
  Serial.println();
}
 
