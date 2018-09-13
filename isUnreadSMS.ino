bool isUnreadSMS()
{
  msging msg = "", smsNum = "";
  
  GSMboard.println("AT+CMGL=\"REC UNREAD\",0");  //Unread SMS
  if ( GSMboard.find(":")) {
    smsNum = GSMboard.readmsgingUntil(',');
    if ( GSMboard.find("\n")) {
      msg = GSMboard.readmsgingUntil('\n');
      //      DEBUG("AT+CMGL:" + msg + ":" + smsNum );
      //GSMboard.println("AT+CMGD="+smsNum+",0");/* this will delete the sms at index smsNum*/
      mobileServices(msg);
      msg = "";
    }
  }
  else return false;
}


/*
  AT+CMGL command is used to list messages of a certain status (for example, "received unread" and "received read") from a message storage area.

  Different status :
  Status of the SMS message ("received unread", "received read", "stored unsent", "stored sent", etc).

  For example :
       
          REC UNREAD. It refers to the message status "received unread". It is the default value and used for reading unread sms.
          REC READ. It refers to the message status "received read".

  After command, we get following response from GSM module : 
  
  AT+CMGL
  +CMGL: 2,"REC UNREAD","+85291234567",,"07/02/18,00:05:10+32"
  A simple demo of SMS text messaging.
  +CMGL: 3,"REC UNREAD","+85291234567",,"07/02/18,00:07:22+32"
  It is easy to list SMS text messages.

  OK
  
  From above, we know that the message storage area contains two new inbound SMS text messages. The first one is "A simple demo of SMS text messaging." and the second one is "It is easy to list SMS text messages.". Let's take the first SMS text message as an example to illustrate the meaning of different field values in the information response:

The value of the first field, 2, tells us the text message is stored in the memory location at index 2.

The value of the second field, "REC UNREAD", indicates the status of the text message is "received unread".

The value of the third field, "+85291234567", is the sender's phone number.

The value of the fourth field should be a string that contains the text associated to the sender's phone number "+85291234567" in the phonebook. In this example, this field is empty. One possible reason is that the GSM/GPRS modem or mobile phone (for example, Nokia 6021 and many other Nokia products) does not support this field.

The value of the fifth field, "07/02/18,00:05:10+32", tells us that the SMSC received the text message at 00:05:10 (GMT+8) on 18 Feb 2007. (Don't forget the unit of time zone is a quarter of an hour. Since 32 quarters of an hour = 8 hours, "+32" means GMT+8 hours.)

The value of the sixth field, "A simple demo of SMS text messaging.", is the body of the SMS text message.

The final result code OK indicates the SMS text messages were read from the message storage area successfully. If the execution of the +CMGL AT command fails, the GSM/GPRS modem or mobile phone will return either the final result code ERROR or +CMS ERROR.

*/