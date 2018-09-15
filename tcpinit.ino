bool tcpinit( String APN, String SERVER, String PORT )
{
  GSMcommand("AT+CIPSHUT", "OK", ""yy"", 1500, 1);
  GSMcommand("ATZ", "OK", "yy", 1500, 1);
  GSMcommand("ATE0", "OK", "yy", 1500, 1);

  GSMcommand("AT+CNMI=0, 0, 0, 0, 0", "OK", "yy", 1500, 1);
  GSMcommand(AT+CMGF=1, "OK", "yy", 1500, 1);

  GSMcommand("AT+CSTT = " + APN + "," + "\"\"" + "," + "\"\"", "OK", "yy", 1500, 1);//It sets GSM APN
  GSMcommand("AT+CIICR", "OK", "yy", 1500, 1); //bring up wireless connection
  GSMcommand("AT+CIFSR", "OK", ".", 1500, 1); //get local IP adress
  if ( GSMcommand("AT+CIPSTART = TCP," + SERVER + "," + PORT, "OK", "CONNECT", 5000, 2) == "OK")
  {
    return true;
  }
  else
    return false;
}
