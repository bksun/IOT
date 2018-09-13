bool isUnreadSMS()
{
  msging msg = "", smsNum = "";
  
  GSMboard.println("AT+CMGL=\"REC UNREAD\",0");  //Unread SMS
  if ( GSMboard.find(":")) {
    smsNum = GSMboard.readmsgingUntil(',');
    if ( GSMboard.find("\n")) {
      msg = GSMboard.readmsgingUntil('\n');
      //      DEBUG("AT+CMGL:" + msg + ":" + smsNum );
      GSMboard.find("!"); wait(300);
      //    GSMboard.println("AT+CMGD="+smsNum+",0");
      mobileServices(msg);
      msg = "";
    }
  }
  else return false;
}


