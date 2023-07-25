/*
 *  Ported on: 02.18.2023
 *      Author: Jonathan Armstrong
 */

#ifndef RC_SWITCH_H
#define RC_SWITCH_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define RCSWITCH_MAX_CHANGES 67

// bucket sniffing constants
//#define MIN_FOOTER_LENGTH	300
//#define MIN_BUCKET_LENGTH	100

//#define PT226x_SYNC_MIN 4500

// sync constants
//#define TOLERANCE_MAX 500
//#define TOLERANCE_MIN 200

//
//#define TOTAL_RF_DATA_BITS 24

// number of repeating by default
//#define RF_TRANSMIT_REPEATS 8



struct RC_SWITCH_T
{
    unsigned long nReceivedValue;
    unsigned int nReceivedBitlength;
    unsigned int nReceivedDelay;
    unsigned int nReceivedProtocol;
    int nReceiveTolerance;
};


/**
 * Description of a single pulse, which consists of a high signal
 * whose duration is "high" times the base pulse length, followed
 * by a low signal lasting "low" times the base pulse length.
 * Thus, the pulse overall lasts (high+low)*pulseLength
 */
struct HighLow
{
    uint8_t high;
    uint8_t low;
};

/**
 * A "protocol" describes how zero and one bits are encoded into high/low
 * pulses.
 */
struct Protocol
{
    /** base pulse length in microseconds, e.g. 350 */
    uint16_t pulseLength;

    struct HighLow syncFactor;
    struct HighLow zero;
    struct HighLow one;
    
    //uint8_t syncFactorHigh;
    //uint8_t syncFactorLow;
    //uint8_t zeroHigh;
    //uint8_t zeroLow;
    //uint8_t oneHigh;
    //uint8_t oneLow;

    /**
     * If true, interchange high and low logic levels in all transmissions.
     *
     * By default, RCSwitch assumes that any signals it sends or receives
     * can be broken down into pulses which start with a high signal level,
     * followed by a a low signal level. This is e.g. the case for the
     * popular PT 2260 encoder chip, and thus many switches out there.
     *
     * But some devices do it the other way around, and start with a low
     * signal level, followed by a high signal level, e.g. the HT6P20B. To
     * accommodate this, one can set invertedSignal to true, which causes
     * RCSwitch to change how it interprets any HighLow struct FOO: It will
     * then assume transmissions start with a low signal lasting
     * FOO.high*pulseLength microseconds, followed by a high signal lasting
     * FOO.low*pulseLength microseconds.
     */
    bool invertedSignal;
};




bool available();
void resetAvailable();

unsigned long getReceivedValue();
unsigned int getReceivedBitlength();
unsigned int getReceivedDelay();
unsigned int getReceivedProtocol();

//void setProtocol(struct Protocol protocol);
//void setProtocol(int nProtocol);
//void setProtocol(int nProtocol, int nPulseLength);

extern __xdata uint16_t timings[RCSWITCH_MAX_CHANGES];
extern __xdata struct RC_SWITCH_T gRCSwitch;
extern const struct Protocol protocols[];


#endif // RC_SWITCH_H