void mobileServices( String cmd )
{
  if (cmd.indexOf("CS") >= 0 )
  {
    ip = SERVER;
    message  = "";
    message  = "Command:" + msg + "->";
    message += "IP:" + ip;
    message += ",Port:" + port;
    sendMessage( message );
  }
  else if (cmd.indexOf("RESET") >= 0 )
  {
    message  = "";
    message  = "RESET DONE";
    sendMessage( message );
    resetGSM();// this function will reset the GSM
  }
}

void resetGSM()
{
  A6board.println("ATZ");
}

/*
If cmd is "CS" then it mean user want to know IP and Port details.
If cmd is "RESET" then it mean user want to RESET the GSM Module only, may be due to signal problem or any other issue.
ATZ is the AT command to reset the GSM.
*/