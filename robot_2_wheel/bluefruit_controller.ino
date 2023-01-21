
#define READ_BUFSIZE (20)
uint8_t buffer[READ_BUFSIZE + 1];

void bluefruit_setup() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);

  bledfu.begin();
  bleuart.begin();

  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  Bluefruit.Advertising.addService(bleuart);
  Bluefruit.ScanResponse.addName();

  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);
  Bluefruit.Advertising.setFastTimeout(30);  // number of seconds in fast mode
  Bluefruit.Advertising.start(0);
}

void bluefruit_read() {
  uint16_t timeout = 50, replyidx = 0;
  uint16_t origTimeout = timeout;

  memset(buffer, 0, READ_BUFSIZE);

  while (--timeout) {
    if (replyidx >= 20) break;
    if ((buffer[1] == 'A') && (replyidx == 15)) break;
    if ((buffer[1] == 'G') && (replyidx == 15)) break;
    if ((buffer[1] == 'M') && (replyidx == 15)) break;
    if ((buffer[1] == 'Q') && (replyidx == 19)) break;
    if ((buffer[1] == 'B') && (replyidx == 5))  break;
    if ((buffer[1] == 'C') && (replyidx == 6))  break;
    if ((buffer[1] == 'L') && (replyidx == 15)) break;

    while (bleuart.available()) {
      char c =  bleuart.read();
      if (c == '!') {
        replyidx = 0;
      }
      buffer[replyidx] = c;
      replyidx++;
      timeout = origTimeout;
    }
    
    delay(1);
  }

  buffer[replyidx] = 0;

  if (!replyidx) return;
  if (buffer[0] != '!') return;

  // check checksum!
  uint8_t xsum = 0;
  uint8_t checksum = buffer[replyidx-1];
  
  for (uint8_t i=0; i<replyidx-1; i++) {
    xsum += buffer[i];
  }
  xsum = ~xsum;

  // Throw an error message if the checksum's don't match
  if (xsum != checksum)
  {
    Serial.print("Checksum mismatch in packet : ");
    return;
  }

  if (buffer[1] == 'B') {
    uint8_t button = buffer[2] - '0';
    bool pressed = buffer[3] - '0';
    //Serial.print ("Button "); Serial.print(buttnum);
    if (pressed) {
      //Serial.println(" pressed");
      buttons[button] = true;
    } else {
      //Serial.println(" released");
      buttons[button] = false;
    }
  }
}
