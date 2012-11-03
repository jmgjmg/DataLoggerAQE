/* nanode SD vars and functions */

unsigned long timer = 60000;

//for counting how long it's been since last successful connection:
unsigned long lastResponseTime = 0;

//----- setup
void nanodeSetup(){
  Serial.println("\nSD Card logger");
  timer = 65; //initial wait time in seconds
  
  pinMode(10, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

//----- check time, sendData if we've hit timer
boolean transmitTime(){
  if (currTime > timer) { //we've hit our transmit timer limit
    //tranmsitting = true;
    nanodeSendData();      //send out all curr data!
    timer = currTime + (transmitFrequency*1000); //reset timer
    return true;
  } 
  else { 
    return false;
  }
}

//----- send data!
void nanodeSendData(){

  Serial.println("-----BEGIN ATTEMPT SEND DATA-----");
  Serial.print("Current time     =");
  Serial.println(currTime);
  Serial.print("sending No2      = ");
  Serial.println(currNo2);
  Serial.print("sending CO       = ");
  Serial.println(currCo);
  Serial.print("sending Quality  = ");
  Serial.println(currQuality);
  Serial.print("sending Humidity = ");
  Serial.println(currHumidity);
  Serial.print("sending Temp     = ");
  Serial.println(currTemp);
  Serial.print("sending Button   = ");
  Serial.println(currButton);
  Serial.println("--------------------------------");
  
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
      dataFile.print("Current time,");
      dataFile.println(currTime);
      
      dataFile.print("NO2,");
      dataFile.println((word)currNo2);

      dataFile.print("CO,");
      dataFile.println((word)currCo);
    
      dataFile.print("airQuality,");
      dataFile.println((word)currQuality);
    
      dataFile.print("humidity,");
      dataFile.println((word)currHumidity);
    
      dataFile.print("temperature,");
      dataFile.println((word)currTemp);
    
      dataFile.print("button,");
      dataFile.println((word)currButton);
      dataFile.println();
      dataFile.println();
      dataFile.close();
        // print to the serial port too:
  } else {
    Serial.println("error opening datalog.txt");
  } 
  
/*
  //byte to hold stringIDs and data
  byte sd = stash.create();

  stash.print("NO2,");
  stash.println((word)currNo2);

  stash.print("CO,");
  stash.println((word)currCo);

  stash.print("airQuality,");
  stash.println((word)currQuality);

  stash.print("humidity,");
  stash.println((word)currHumidity);

  stash.print("temperature,");
  stash.println((word)currTemp);

  stash.print("button,");
  stash.println((word)currButton);

  stash.save();

  // generate the header with payload - note that the stash size is used,
  // and that a "stash descriptor" is passed in as argument using "$H"
  Stash::prepare(PSTR("PUT http://$F/v2/feeds/$F.csv HTTP/1.0" "\r\n"
    "Host: $F" "\r\n"
    "X-PachubeApiKey: $F" "\r\n"
    "Content-Length: $D" "\r\n"
    "\r\n"
    "$H"),
  website, PSTR(FEED), website, PSTR(APIKEY), stash.size(), sd);

  // send the packet - this also releases all stash buffers once done
  ether.tcpSend();
*/
  //flashStatusLed();
}

void nanodeReset(){
  digitalWrite(resetterPin, LOW);
}





