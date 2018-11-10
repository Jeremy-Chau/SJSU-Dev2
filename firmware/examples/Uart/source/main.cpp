#include <project_config.hpp>

#include <cstdio>

#include "L1_Drivers/uart.hpp"
#include "L2_Utilities/log.hpp"
#include "L2_Utilities/time.hpp"

int main(void)
{
  DEBUG_PRINT("Uart application starting.");
  DEBUG_PRINT(
      "The aplication uses a loopback test. Please connect pins P2.8 and P2.9"
      "together using a wire for this test.");
  Uart uart2(Uart::Channels::kUart2);
  DEBUG_PRINT("Initializing UART port 2 with a baud rate of 38400 bps");
  uart2.Initialize(38400);
  // While loop to constantly send the array of data
  while (true)
  {
    DEBUG_PRINT(
        "A char array containing the characters 'Hello World' will"
        "now be sent from the Tx pin to the Rx pin");
    char message[] = "Hello World!";
    DEBUG_PRINT("Sending characters now.");
    for (size_t i = 0; message[i] != '\0'; i++)
    {
      uart2.Send(message[i]);
    }
    DEBUG_PRINT(
        "Recieving characters that arrived at Rx pin and printing them");
    for (size_t i = 0; i < SJ2_ARRAY_LENGTH(message) - 1; i++)
    {
      char receive = uart2.Receive();
      putchar(receive);
    }
    putchar('\n');
    Delay(1000);
  }
  return 0;
}
