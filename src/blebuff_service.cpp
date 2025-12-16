#include "blebuff_service.h"
#include "main_helper.h"

BLEBuff_Service::BLEBuff_Service(const HallSignal& hallSignal) 
    : p16_BLEBuff(reinterpret_cast<uint16_t*>(p8_BLEBuff))
    , startSignalRecorded(false)
    , BLEBuff_idx16(0)
    , prev_rslts_pos16((hallSignal.rslts_pos() == 0) ? NUM_OF_RSLTS - 1 : hallSignal.rslts_pos_bytes() - 1)
    , prev_rslts_pos8(prev_rslts_pos16 * 2)
    , p8_rslts(hallSignal.rslts())
    , p16_rslts(hallSignal.p16_rslts())
    , endSignalHighCounter(0)
    , signalHandled(true)
{

}

void BLEBuff_Service::recordStartSignal() {
    if (hall_signal.rslts_pos_bytes() < SIGNAL_POINTS_OFFSET_BYTES) {
        memcpy(p8_BLEBuff, p8_rslts + (RSLTS_BUFF_SIZE_BYTES - SIGNAL_POINTS_OFFSET_BYTES + hall_signal.rslts_pos_bytes()),
            SIGNAL_POINTS_OFFSET - hall_signal.rslts_pos_bytes());
        memcpy(p8_BLEBuff, p8_rslts, hall_signal.rslts_pos_bytes());
    }
    else {
        memcpy(p8_BLEBuff, p8_rslts + hall_signal.rslts_pos_bytes() - SIGNAL_POINTS_OFFSET_BYTES,
             SIGNAL_POINTS_OFFSET_BYTES);
    }
}

void BLEBuff_Service::handleSignalHigh() {    
    if (!startSignalRecorded) {
        startSignalRecorded = true;
        recordStartSignal();
        BLEBuff_idx16 = SIGNAL_POINTS_OFFSET;
        prev_rslts_pos16 = hall_signal.rslts_pos();
        checkSend();
        return;
    }

    if (prev_rslts_pos16 != hall_signal.rslts_pos()) {
        p16_BLEBuff[BLEBuff_idx16] = hall_signal.p16_rslts()[prev_rslts_pos16];
        ++BLEBuff_idx16;
        prev_rslts_pos16 = hall_signal.rslts_pos();
        checkSend();
    }
}

// handler for the part after the signal is high
void BLEBuff_Service::handleEndSignalHigh() {
    if (prev_rslts_pos16 != hall_signal.rslts_pos()) {
        p16_BLEBuff[BLEBuff_idx16] = hall_signal.p16_rslts()[prev_rslts_pos16];
        ++endSignalHighCounter;
        ++BLEBuff_idx16;
        prev_rslts_pos16 = hall_signal.rslts_pos();
        checkSend();
    }
    
    if (endSignalHighCounter == SIGNAL_POINTS_OFFSET) {
        signalHandled = true;
        endSignalHighCounter = 0;
        sendData(p8_BLEBuff, BLEBuff_idx16 * 2);
        BLEBuff_idx16 = 0;
    }
}

void BLEBuff_Service::checkSend() {
    if (BLEBuff_idx16 == BLEBUFF_SIZE16) {
        sendData(p8_BLEBuff, BLEBUFF_SIZE8);
        BLEBuff_idx16 = 0;
    }
}

void BLEBuff_Service::handleNewData() {
    if (hall_signal.info() & SIGNAL_VALUE) {
        signalHandled = false;
        endSignalHighCounter = 0;
        this->handleSignalHigh();
    }
    else if (!signalHandled) {
        startSignalRecorded = false;
        this->handleEndSignalHigh();
    }
}