/*
 * Copyright (c) , Majenko Technologies
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 * 
 *  1. Redistributions of source code must retain the above copyright notice, 
 *     this list of conditions and the following disclaimer.
 * 
 *  2. Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 * 
 *  3. Neither the name of Majenko Technologies nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without 
 *     specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, 
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#ifndef _MCP23S17_H
#define _MCP23S17_H

#if (ARDUINO >= 100) 
# include <Arduino.h>
#else
# include <WProgram.h>
#endif

#ifdef __PIC32MX__
#include <DSPI.h>
#else
#include <SPI.h>
#endif

class MCP23S17 {
    private:
#ifdef __PIC32MX__
        DSPI *_spi; /*! This points to a valid SPI object created from the chipKIT DSPI library. */
#else
        SPIClass *_spi; /*! This points to a valid SPI object created from the Arduino SPI library. */
#endif
        uint8_t _cs;    /*! Chip select pin */
        uint8_t _addr;  /*! 3-bit chip address */
    
        uint8_t _reg[22];   /*! Local mirrors of the 22 internal registers of the MCP23S17 chip */

        enum {
            MCP_IODIRA,     MCP_IODIRB,
            MCP_IPOLA,      MCP_IPOLB,
            MCP_GPINTENA,   MCP_GPINTENB,
            MCP_DEFVALA,    MCP_DEFVALB,
            MCP_INTCONA,    MCP_INTCONB,
            MCP_IOCONA,     MCP_IOCONB,
            MCP_GPPUA,      MCP_GPPUB,
            MCP_INTFA,      MCP_INTFB,
            MCP_INTCAPA,    MCP_INTCAPB,
            MCP_GPIOA,      MCP_GPIOB,
            MCP_OLATA,      MCP_OLATB
        };

        void readRegister(uint8_t addr); 
        void writeRegister(uint8_t addr);
        void readAll();
        void writeAll();
    
    public:
#ifdef __PIC32MX__
        MCP23S17(DSPI *spi, uint8_t cs, uint8_t addr);
        MCP23S17(DSPI &spi, uint8_t cs, uint8_t addr);
#else
        /**
         * @brief Construct a new MCP23S17 object
         * 
         * @param spi SPI Object
         * @param cs CS Pin
         * @param addr Address
         */
        MCP23S17(SPIClass *spi, uint8_t cs, uint8_t addr);

        /**
         * @brief Construct a new MCP23S17 object
         * 
         * @param spi SPI Object
         * @param cs CS Pin
         * @param addr Address
         */
        MCP23S17(SPIClass &spi, uint8_t cs, uint8_t addr);
#endif
        void begin();

        /**
         * @brief Overload Method for begin()
         * 
         * @param clockPin - clock Pin of the target SPI bus
         * @param misoPin - miso Pin of the target SPI bus
         * @param mosiPin - mosi Pin of the target SPI bus
         * @param chipSelect chip select Pin of the target SPI bus
         */
        void begin(uint8_t clockPin, uint8_t misoPin, uint8_t mosiPin, uint8_t chipSelect);
        
        void pinMode(uint8_t pin, uint8_t mode);
        void digitalWrite(uint8_t pin, uint8_t value);
        uint8_t digitalRead(uint8_t pin);

        uint8_t readPort(uint8_t port);
        uint16_t readPort();
        void writePort(uint8_t port, uint8_t val);
        void writePort(uint16_t val);
        void enableInterrupt(uint8_t pin, uint8_t type);
        void disableInterrupt(uint8_t pin);
        void setMirror(boolean m);
        uint16_t getInterruptPins();
        uint16_t getInterruptValue();
        void setInterruptLevel(uint8_t level);
        void setInterruptOD(boolean openDrain);
        uint8_t getInterruptAPins();
        uint8_t getInterruptAValue();
        uint8_t getInterruptBPins();
        uint8_t getInterruptBValue();
        SPIClass* getSPI();
};
#endif
