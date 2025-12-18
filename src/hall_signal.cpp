#include "hall_signal.h"
#include <Arduino.h>

HallSignal::HallSignal()
    : filter_m(0)
    , rslts_pos_m(0)
    , info_m(0x00) {
    for (uint16_t i = 0; i < NUM_OF_RSLTS; ++i) {
        rslts_m[i] = 0;
    }
}

void HallSignal::check_signal() {
    if ((info_m & THRESHOLD_SET) &&
        (filter_m > threshold_top_m || filter_m < threshold_bottom_m)) {
        info_m |= SIGNAL_VALUE;
    }
    else {
        info_m &= ~SIGNAL_VALUE;
    }
}

const uint8_t* HallSignal::rslts() const {
    return reinterpret_cast<const uint8_t*>(rslts_m);
}

size_t HallSignal::rslts_pos() const {
    return rslts_pos_m;
}

void HallSignal::add_value(uint16_t value) {
    if (!(info_m & FILTER_FILLED)) {
        filter_m = value;
    }
    else {
        filter_m = filter_m * (1.0 - FILTER_COEF) + value * FILTER_COEF;
    }

    this->add_rslt();
    this->check_signal();
}

uint8_t HallSignal::info() const {
    return info_m;
}

void HallSignal::add_rslt() {
    if (!(info_m & FILTER_FILLED)) {
        info_m |= FILTER_FILLED;
    }

    rslts_m[rslts_pos_m] = filter_m;

    if (rslts_pos_m == NUM_OF_RSLTS - 1) {
        rslts_pos_m = 0;
    }
    else {
        ++rslts_pos_m;
    }

    if (!(info_m & THRESHOLD_SET) && rslts_pos_m == 64) {
        info_m |= THRESHOLD_SET;

        uint32_t sum = 0;
        for (size_t i = 0; i < 64; ++i) {
            sum += rslts_m[i];
        }

        threshold_bottom_m = (sum / 64) - THRESHOLD_OFFSET;
        threshold_top_m = (sum / 64) + THRESHOLD_OFFSET;
    }
}

void HallSignal::update_trshld() {
    if (!(info_m & SIGNAL_VALUE) && info_m & FILTER_FILLED) {
        threshold_top_m = filter_m + THRESHOLD_OFFSET;

        if (filter_m < THRESHOLD_OFFSET) {
            threshold_bottom_m = 0;
        }
        else {
            threshold_bottom_m = filter_m - THRESHOLD_OFFSET;
        }
    }
}

uint16_t HallSignal::filter_value() const {
    return filter_m;
}

size_t HallSignal::rslts_pos_bytes() const {
    return rslts_pos_m * 2;
}

void HallSignal::add_values(const uint16_t* data, size_t size_vals) {    
    for (size_t i = 0; i < size_vals; ++i) {
        this->add_value(data[i]);
    }
}

const uint16_t* HallSignal::p16_rslts() const {
    return rslts_m;
}