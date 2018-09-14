bool tcpinit( String APN, String SERVER, String PORT )
{
  A6command("AT+CIPSHUT", "OK", ""yy"", 1500, 1);
  A6command("ATZ", "OK", "yy", 1500, 1);
  A6command("ATE0", "OK", "yy", 1500, 1);

  A6command("AT+CNMI=0, 0, 0, 0, 0", "OK", "yy", 1500, 1);
  A6command(AT+CMGF=1, "OK", "yy", 1500, 1);

  A6command("AT+CSTT = " + APN + "," + "\"\"" + "," + "\"\"", "OK", "yy", 1500, 1);//It sets GSM APN
  A6command("AT+CIICR", "OK", "yy", 1500, 1); //bring up wireless connection
  A6command("AT+CIFSR", "OK", ".", 1500, 1); //get local IP adress
  if ( A6command("AT+CIPSTART = TCP," + SERVER + "," + PORT, "OK", "CONNECT", 5000, 2) == "OK")
  {
    return true;
  }
  else
    return false;
}
