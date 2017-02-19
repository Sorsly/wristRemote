/*
Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
version 2 as published by the Free Software Foundation.
*/

#ifndef __RF24_H__
#define __RF24_H__

#include "RF24_config.h"

#if defined (RF24_LINUX) || defined (LITTLEWIRE)
#include "utility/includes.h"
#elif defined SOFTSPI
#include <DigitalIO.h>
#endif

typedef enum { RF24_PA_MIN = 0,RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX, RF24_PA_ERROR } rf24_pa_dbm_e ;

typedef enum { RF24_1MBPS = 0, RF24_2MBPS, RF24_250KBPS } rf24_datarate_e;

typedef enum { RF24_CRC_DISABLED = 0, RF24_CRC_8, RF24_CRC_16 } rf24_crclength_e;

class RF24
{
private:
#ifdef SOFTSPI
SoftSPI<SOFT_SPI_MISO_PIN, SOFT_SPI_MOSI_PIN, SOFT_SPI_SCK_PIN, SPI_MODE> spi;
#elif defined (SPI_UART)
SPIUARTClass uspi;
#endif

#if defined (RF24_LINUX) || defined (XMEGA_D3) /* XMEGA can use SPI class */
SPI spi;
#endif
#if defined (MRAA)
GPIO gpio;
#endif

uint8_t ce_pin; 
uint8_t csn_pin; 
uint16_t spi_speed; 
#if defined (RF24_LINUX) || defined (XMEGA_D3)
uint8_t spi_rxbuff[32+1] ; //SPI receive buffer (payload max 32 bytes)
uint8_t spi_txbuff[32+1] ; //SPI transmit buffer (payload max 32 bytes + 1 byte for the command)
#endif  
bool p_variant; /* False for RF24L01 and true for RF24L01P */
uint8_t payload_size; 
bool dynamic_payloads_enabled; 
uint8_t pipe0_reading_address[5]; 
uint8_t addr_width; 
protected:
inline void beginTransaction();

inline void endTransaction();

public:

RF24(uint8_t _cepin, uint8_t _cspin);
//#if defined (RF24_LINUX)

RF24(uint8_t _cepin, uint8_t _cspin, uint32_t spispeed );
//#endif

#if defined (RF24_LINUX)
virtual ~RF24() {};
#endif

bool begin(void);

void startListening(void);

void stopListening(void);

bool available(void);

void read( void* buf, uint8_t len );

bool write( const void* buf, uint8_t len );

void openWritingPipe(const uint8_t *address);

void openReadingPipe(uint8_t number, const uint8_t *address);

void printDetails(void);

bool available(uint8_t* pipe_num);

bool rxFifoFull();

void powerDown(void);

void powerUp(void) ;

bool write( const void* buf, uint8_t len, const bool multicast );

bool writeFast( const void* buf, uint8_t len );

bool writeFast( const void* buf, uint8_t len, const bool multicast );

bool writeBlocking( const void* buf, uint8_t len, uint32_t timeout );

bool txStandBy();

bool txStandBy(uint32_t timeout, bool startTx = 0);

void writeAckPayload(uint8_t pipe, const void* buf, uint8_t len);

bool isAckPayloadAvailable(void);

void whatHappened(bool& tx_ok,bool& tx_fail,bool& rx_ready);

void startFastWrite( const void* buf, uint8_t len, const bool multicast, bool startTx = 1 );

void startWrite( const void* buf, uint8_t len, const bool multicast );

void reUseTX();

uint8_t flush_tx(void);

bool testCarrier(void);

bool testRPD(void) ;

bool isValid() { return ce_pin != 0xff && csn_pin != 0xff; }

void closeReadingPipe( uint8_t pipe ) ;

//#if defined (FAILURE_HANDLING)
bool failureDetected; 
//#endif

void setAddressWidth(uint8_t a_width);

void setRetries(uint8_t delay, uint8_t count);

void setChannel(uint8_t channel);

uint8_t getChannel(void);

void setPayloadSize(uint8_t size);

uint8_t getPayloadSize(void);

uint8_t getDynamicPayloadSize(void);

void enableAckPayload(void);

void enableDynamicPayloads(void);

void enableDynamicAck();

bool isPVariant(void) ;

void setAutoAck(bool enable);

void setAutoAck( uint8_t pipe, bool enable ) ;

void setPALevel ( uint8_t level );

uint8_t getPALevel( void );

bool setDataRate(rf24_datarate_e speed);

rf24_datarate_e getDataRate( void ) ;

void setCRCLength(rf24_crclength_e length);

rf24_crclength_e getCRCLength(void);

void disableCRC( void ) ;

void maskIRQ(bool tx_ok,bool tx_fail,bool rx_ready);

uint32_t txDelay;

uint32_t csDelay=5;

void openReadingPipe(uint8_t number, uint64_t address);

void openWritingPipe(uint64_t address);

private:

void csn(bool mode);

void ce(bool level);

uint8_t read_register(uint8_t reg, uint8_t* buf, uint8_t len);

uint8_t read_register(uint8_t reg);

uint8_t write_register(uint8_t reg, const uint8_t* buf, uint8_t len);

uint8_t write_register(uint8_t reg, uint8_t value);

uint8_t write_payload(const void* buf, uint8_t len, const uint8_t writeType);

uint8_t read_payload(void* buf, uint8_t len);

uint8_t flush_rx(void);

uint8_t get_status(void);

#if !defined (MINIMAL)

void print_status(uint8_t status);

void print_observe_tx(uint8_t value);

void print_byte_register(const char* name, uint8_t reg, uint8_t qty = 1);

void print_address_register(const char* name, uint8_t reg, uint8_t qty = 1);
#endif

void toggle_features(void);

uint8_t spiTrans(uint8_t cmd);

#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
void errNotify(void);
#endif

};


#endif // __RF24_H__

