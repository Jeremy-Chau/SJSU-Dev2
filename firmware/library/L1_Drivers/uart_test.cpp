#include "L0_LowLevel/LPC40xx.h"
#include "L0_LowLevel/SystemFiles/system_LPC407x_8x_177x_8x.h"
#include "L1_Drivers/uart.hpp"
#include "L5_Testing/testing_frameworks.hpp"

TEST_CASE("Testing Uart", "[Uart]")
{
	// Char to be used in multiple tests
    constexpr char T = 'T';

    // Local object of LPC_UART_TypeDef to 
    // observe changes in registers of UART2
    LPC_UART_TypeDef Local_Uart2;  // <- This is wrong. Need the address of LPC_UART2_BASE with it

    // Object that will be used to perform necessary functions
    Uart test;

    // Calling the Initialization of UART 2 so it can be used for all tests
    // Called to be at 9600 bps

    test.Initialize(9600, 2);

    SECTION("Initialize UART 2")
    {
    	constexpr uint8_t DLAB_bit = 7;
        constexpr uint32_t kFCR = 0b111;
        constexpr uint32_t kDiv =
            static_cast<uint32_t>(OSC_CLK / (16.0f * 9600.0f) + 0.5f);
        constexpr uint8_t kDLM = static_cast<uint8_t>(kDiv >> 8);
        constexpr uint8_t kDLL = static_cast<uint8_t>(kDiv >> 0);
        constexpr uint32_t kLCR = 0b11;

        // Check first 3 bits of FCR
        CHECK(kFCR == ((Local_Uart2.FCR) & 0b111));

        // Unlock DLAB
        Local_Uart2.LCR |= (1 << DLAB_bit);

        // Check DLM bits
        CHECK(kDLM == Local_Uart2.DLM);

        // Check DLL bits
        CHECK(kDLL == Local_Uart2.DLL);

        // Lock DLAB
        Local_Uart2.LCR &= ~(1 << DLAB_bit);

        CHECK(kLCR == Local_Uart2.LCR);
    }
    SECTION("Sending Data")
    {
    	constexpr uint8_t TER_bit = 7;
        // Disable Tx enable so test can check bits in register
        Local_Uart2.TER &= ~(1 << TER_bit);

        // Send the letter T
        test.Send('T');

        // Check the transmit holding register if it is holding the letter T
        CHECK(T == Local_Uart2.THR);

        // Enable the FIFO to send the data
        Local_Uart2.TER |= (1 << TER_bit);
    }
    SECTION("Reading Data")
    {
        char output;
        // Inject a T char into the receive buffer
        Local_Uart2.RBR = T;

        // Check the output of the receive function
        CHECK(T == (output = test.Receive()));
    }
}
