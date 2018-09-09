bool sendSMS(String message)
{
  String str = "";
  if ( GSMCommand("at+cmgf=1", "OK", "yy", 3000, 3) == OK)
    if ( GSMCommand("at+cmgs=" + MOBILE, ">", "yy", 4000, 3) == OK ) { // MIBILE is mobile number
      /////////i.e. AT+CMGS=\"+918460512345\"  
      GSMBoard.println(message); //message to be sent 
      GSMBoard.println(char(0x1a)); //CTRL+Z for end of message
    }

  unsigned long prev = millis();
  while ( millis() - prev < 3000 )
  {
    if (GSMBoard.available())
    {
      str = GSMBoard.readString();
      if ( str.indexOf("OK") >= 0 || str.indexOf("SEND") >= 0 )
      {
        return true;
      }
    }
  }
  GSMBoard.println(char(0x1A));
}

byte GSMCommand(String command, String response1, String response2, int timeOut, int repetitions) {
  byte returnValue = NOTOK;
  byte count = 0;
  while (count < repetitions && returnValue != OK)
  { 
    GSMBoard.println(command);
   //GSMwaitFor() will wait until timeout occurs 
    if (GSMwaitFor(response1, response2, timeOut) == OK) {
      returnValue = OK;
    } else returnValue = NOTOK;
    count++;
  }
  return returnValue;
}

byte GSMwaitFor(String response1, String response2, int timeOut)
{
  unsigned long entry = millis();
  byte  count = 0;
  String reply;
  byte retVal = 99;
  do {
    reply = GSMread(); //reads from GSM SERIAL 
    if (reply != "") {
      DEBUG(reply);
    }

    if ( reply.indexOf("CSQ") > -1 )
    {
      signal = reply.substring(reply.indexOf(":") + 2, reply.indexOf(","));
      return OK;
    }
  } while ((reply.indexOf(response1) + reply.indexOf(response2) == -2) && millis() - entry < timeOut );

  if ((millis() - entry) >= timeOut) {
    retVal = TIMEOUT;
  } else {
    if (reply.indexOf(response1) + reply.indexOf(response2) > -2) 
	retVal = OK;
    else 
	retVal = NOTOK;
  }
  return retVal;
}

String GSMread() {
  String reply = "";
  if (GSMboard.available())  {
    reply = GSMboard.readString();
  }
  return reply;
}
