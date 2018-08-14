#include <project_config.hpp>

#include <cstdint>
#include <cstdio>

#include "L0_LowLevel/delay.hpp"
#include "L0_LowLevel/LPC40xx.h"
#include "L1_Drivers/uart.hpp"
#include "L2_Utilities/debug_print.hpp"


int main(void)
{
    // This example code uses a loop back test to display its
    // capabilities. Please connect TxD2 and RxD2 together on
    // your board before running.

    // Create an object to access the UART functions
    Uart test;
    char receive;
    char input [] = "Hello World!";

    // Activates the initialize function with a baud rate of 38400 bits
    // per second and activates UART 2. If this
    // function fails, Fail will be printed out

    if (test.Initialize(38400, 2) == 0)
    {
        printf("Fail!");
    }

    while (1)
    {
        // The for loop will loop until it hits the null character
        // in the array. This ensures the full message will be sent
        // without needing to know the length of the array.
        for (int i=0; input[i] != '\0'; i++) test.Send(input2[i], 10);

        // This loop uses the length of the input array to determine
        // how long it will be running. The receive variable is grabbing
        // the return data from the Receive function.

        for (int j=0; input[j] != '\0'; j++)  // 12
        {
            receive = test.Recieve(10);
            printf("%c", receive);
        }
            printf("\n");
        // Delay(1000);
    }
    return 0;
}
