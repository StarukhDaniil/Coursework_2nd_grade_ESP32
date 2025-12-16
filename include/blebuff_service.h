#pragma once
#include "main_instances.h"

#define BLEBUFF_SIZE8 4096
#define BLEBUFF_SIZE16 BLEBUFF_SIZE8 / 2
// defines how much POINTS before and after signal recognition will be added to graph
#define SIGNAL_POINTS_OFFSET 20
// defines how much BYTES before and after signal recognition will be added to graph
#define SIGNAL_POINTS_OFFSET_BYTES  SIGNAL_POINTS_OFFSET * 2

class BLEBuff_Service {
private:
    uint8_t p8_BLEBuff[BLEBUFF_SIZE8];
    // pointer for uint16_t representation of BLEBuff
    uint16_t* p16_BLEBuff;
    // to know whether the part before signal recognition is recorded
    bool startSignalRecorded;
    bool signalHandled;
    // index for 16-bit representation
    size_t BLEBuff_idx16;
    size_t endSignalHighCounter;

    const uint8_t* p8_rslts;
    const uint16_t* p16_rslts;
    size_t prev_rslts_pos8;
    size_t prev_rslts_pos16;

public:
    BLEBuff_Service(const HallSignal& hallSignal);
    void handleNewData();

private:
    void handleSignalHigh();
    void handleEndSignalHigh();
    void recordStartSignal();
    // checks if it is time to send data and sends data
    void checkSend();
};