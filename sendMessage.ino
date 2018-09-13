#define GSMBoard ss
#define OK 1
#define NOTOK 2
#define TIMEOUT 3
#define CIPSTATUS_ERROR   11
#define statusCountLimit  5

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