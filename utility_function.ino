
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
