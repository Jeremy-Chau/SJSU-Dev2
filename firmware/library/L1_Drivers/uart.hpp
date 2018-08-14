#pragma once

#include <cstdint>

#include "L0_LowLevel/LPC40xx.h"
#include "L0_LowLevel/SystemFiles/system_LPC407x_8x_177x_8x.h"
#include "L1_Drivers/pin_configure.hpp"


class Uart_interface
{
    virtual void SetBaudRate(uint32_t baud_rate) = 0;
    virtual bool Initialize(uint32_t baud_rate, uint32_t mode) = 0;
    virtual void Send(char out, uint32_t time_limit) = 0;
    virtual char Recieve(uint32_t time_limit) = 0;
};

class Uart : public Uart_interface
{
 public:
    LPC_UART_TypeDef * UARTBaseReg;
    LPC_UART1_TypeDef * UARTBaseReg1;
    LPC_UART4_TypeDef * UARTBaseReg4;

    void SetBaudRate(uint32_t baud_rate) override
    {
        if (UARTBaseReg1 ==
            reinterpret_cast<LPC_UART1_TypeDef *>(LPC_UART1_BASE))
        {
            float baudrate = static_cast<float>(baud_rate);

            // Set baud rate
            UARTBaseReg1 -> LCR |= (1 << 7);
            uint32_t div =
                static_cast<uint32_t>(OSC_CLK / (16.0f * baudrate) + 0.5f);
            UARTBaseReg1 -> DLM = static_cast<uint8_t>(div >> 8);
            UARTBaseReg1 -> DLL = static_cast<uint8_t>(div >> 0);
            UARTBaseReg1 -> LCR = 3;
        }
        else if (UARTBaseReg4 ==
            reinterpret_cast<LPC_UART4_TypeDef *>(LPC_UART4_BASE))
        {
            float baudrate = static_cast<float>(baud_rate);

            // Set baud rate
            UARTBaseReg4 -> LCR |= (1 << 7);
            uint32_t div =
                static_cast<uint32_t>(OSC_CLK / (16.0f * baudrate) + 0.5f);
            UARTBaseReg4 -> DLM = static_cast<uint8_t>(div >> 8);
            UARTBaseReg4 -> DLL = static_cast<uint8_t>(div >> 0);
            UARTBaseReg4 -> LCR = 3;
        }
        else
        {
            float baudrate = static_cast<float>(baud_rate);

            // Set baud rate
            UARTBaseReg -> LCR |= (1 << 7);
            uint32_t div =
                static_cast<uint32_t>(OSC_CLK / (16.0f * baudrate) + 0.5f);
            UARTBaseReg -> DLM = static_cast<uint8_t>(div >> 8);
            UARTBaseReg -> DLL = static_cast<uint8_t>(div >> 0);
            UARTBaseReg -> LCR = 3;
        }
    }

    bool Initialize(uint32_t baud_rate, uint32_t mode) override
    {
        switch (mode)
        {
            case 0:
            {
                UARTBaseReg =
                    reinterpret_cast<LPC_UART_TypeDef *>(LPC_UART0_BASE);

                // Set Power bit
                LPC_SC->PCONP &= ~(1 << 3);
                LPC_SC->PCONP |= (1 << 3);

                // Tx object created
                PinConfigure Tx = PinConfigure::CreatePinConfigure<0, 0>();
                Tx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);

                PinConfigure Rx = PinConfigure::CreatePinConfigure<0, 1>();
                Rx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);
                // Will be using pins 0_2(Tx) and 0_3(Rx) for the final version

                // CHeck page 134 for function page
                Tx.SetPinFunction(0b100);
                Rx.SetPinFunction(0b100);

                SetBaudRate(baud_rate);

                // Uart FIFO
                UARTBaseReg->FCR |= (7 << 0);

                return true;
            }
            case 1:
            {
                UARTBaseReg1 =
                    reinterpret_cast<LPC_UART1_TypeDef *>(LPC_UART1_BASE);

                // Set Power bit
                LPC_SC->PCONP &= ~(1 << 4);
                LPC_SC->PCONP |= (1 << 4);

                // Tx object created
                PinConfigure Tx = PinConfigure::CreatePinConfigure<2, 0>();
                Tx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);

                PinConfigure Rx = PinConfigure::CreatePinConfigure<2, 1>();
                Rx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);

                // Check page 134 for function page
                Tx.SetPinFunction(0b010);
                Rx.SetPinFunction(0b010);

                SetBaudRate(baud_rate);

                // Uart FIFO
                UARTBaseReg1->FCR |= (7 << 0);

                return true;
            }
            case 2:
            {
                UARTBaseReg =
                    reinterpret_cast<LPC_UART_TypeDef *>(LPC_UART2_BASE);

                // Set Power bit
                LPC_SC->PCONP &= ~(1 << 24);
                LPC_SC->PCONP |= (1 << 24);

                // Tx object created
                PinConfigure Tx = PinConfigure::CreatePinConfigure<2, 8>();

                Tx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);

                PinConfigure Rx = PinConfigure::CreatePinConfigure<2, 9>();
                Rx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);

                // CHeck page 134 for function page
                Tx.SetPinFunction(0b010);
                Rx.SetPinFunction(0b010);

                SetBaudRate(baud_rate);

                // Uart FIFO
                UARTBaseReg->FCR |= (7 << 0);

                return true;
            }
            case 3:
            {
                UARTBaseReg =
                    reinterpret_cast<LPC_UART_TypeDef *>(LPC_UART0_BASE);

                // Set Power bit
                LPC_SC->PCONP &= ~(1 << 25);
                LPC_SC->PCONP |= (1 << 25);

                // Tx object created
                PinConfigure Tx = PinConfigure::CreatePinConfigure<4, 28>();

                Tx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);

                PinConfigure Rx = PinConfigure::CreatePinConfigure<4, 29>();
                Rx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);

                // CHeck page 134 for function page
                Tx.SetPinFunction(0b010);
                Rx.SetPinFunction(0b010);

                SetBaudRate(baud_rate);

                // Uart FIFO
                UARTBaseReg->FCR |= (7 << 0);

                return true;
            }
            case 4:
            {
                UARTBaseReg4 =
                    reinterpret_cast<LPC_UART4_TypeDef *>(LPC_UART4_BASE);

                // Set Power bit
                LPC_SC->PCONP &= ~(1 << 8);
                LPC_SC->PCONP |= (1 << 8);

                // PinConfigure Tx(1,29);
                PinConfigure Tx = PinConfigure::CreatePinConfigure<1, 29>();
                Tx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);

                // PinConfigure Rx(2,9);
                PinConfigure Rx = PinConfigure::CreatePinConfigure<2, 9>();
                Rx.SetPinMode(PinConfigureInterface::PinMode::kPullUp);

                // CHeck page 134 for function page
                Tx.SetPinFunction(0b101);
                Rx.SetPinFunction(0b011);

                SetBaudRate(baud_rate);

                // Uart FIFO
                UARTBaseReg4->FCR |= (7 << 0);

                return true;
            }
            default:
            {
                return false;
            }
        }
    }

    void Send(char out, uint32_t time_limit) override
    {
        uint32_t counter = 0;
        if (UARTBaseReg1 ==
            reinterpret_cast<LPC_UART1_TypeDef *>(LPC_UART1_BASE))
        {
            UARTBaseReg1->THR = out;
            while (counter > time_limit)
            {
                if (!(UARTBaseReg1->LSR & (1 << 5))) {counter++;}
                else {break;}
            }
        }
        else if (UARTBaseReg4 ==
            reinterpret_cast<LPC_UART4_TypeDef *>(LPC_UART4_BASE))
        {
            UARTBaseReg4->THR = out;
            while (counter > time_limit)
            {
                if (!(UARTBaseReg4->LSR & (1 << 5))){counter++;}
                else {break;}
            }
        }
        else
        {
            UARTBaseReg->THR = out;
            while (counter > time_limit)
            {
                if (!(UARTBaseReg->LSR & (1 << 5))){counter++;}
                else {break;}
            }
        }
    }

    char Recieve(uint32_t time_limit) override
    {
        char mychar;
        uint32_t counter = 0;
        if (UARTBaseReg1 ==
            reinterpret_cast<LPC_UART1_TypeDef *>(LPC_UART1_BASE))
        {
            while (counter > time_limit)
            {
                if (!(UARTBaseReg1->LSR & (1 << 0))){counter++;}
                else
                {
                    mychar = static_cast<char>(UARTBaseReg1->RBR);
                    return mychar;
                }
            }
        }
       else if (UARTBaseReg4 ==
            reinterpret_cast<LPC_UART4_TypeDef *>(LPC_UART4_BASE))
        {
            while (counter > time_limit)
            {
                if (!(UARTBaseReg4->LSR & (1 << 0))){counter++;}
                else
                {
                    mychar = static_cast<char>(UARTBaseReg4->RBR);
                    return mychar;
                }
            }
       }
        else
        {
            while (counter > time_limit)
            {
                if (!(UARTBaseReg->LSR & (1 << 0))){counter++;}
                else
                {
                    mychar = static_cast<char>(UARTBaseReg->RBR);
                    return mychar;
                }
            }
        }
        return 0;
    }
};
