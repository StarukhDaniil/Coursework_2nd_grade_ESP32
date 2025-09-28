#include "hall_signal.h"

HallSignal::HallSignal() 
  : filter_m(0)
  , rslts_pos_m(0)
  , filter_cnt_m(0)
  , info_m(0x00) {
  for (uint16_t i = 0; i < RSLTS_SIZE; ++i) {
    rslts_m[i] = 0;
  }
}

void HallSignal::check_signal() {
  if (filter_m > threshold_top_m || filter_m < threshold_bottom_m) {
    info_m |= SIGNAL_VALUE;
  }
  else {
    info_m &= ~SIGNAL_VALUE;
  }
}

const uint16_t* HallSignal::rslts() const {
  return const_cast<const uint16_t*>(rslts_m);
}

uint16_t HallSignal::rslts_pos() const {
  return rslts_pos_m;
}

void HallSignal::add_value(uint16_t value) {
  if (!(info_m & FILTER_FILLED)) {
    filter_m = ((filter_m * filter_cnt_m) + value) / (filter_cnt_m + 1);
  }
  else {
    filter_m = filter_m * (1.0 - FILTER_COEF) + value * FILTER_COEF;
  }

  ++filter_cnt_m;
  
  if (filter_cnt_m == FILTER_SIZE) {
    this->add_rslt();
    this->check_signal();
    filter_cnt_m = 0;
  }
}

uint8_t HallSignal::info() const {
  return info_m;
}

void HallSignal::add_rslt() {
  if (!(info_m & FILTER_FILLED)) {
    info_m |= FILTER_FILLED;
  }

  filter_cnt_m = 0;

  if (rslts_pos_m == RSLTS_SIZE - 1) {
    rslts_pos_m = 0;
  }
  else {
    ++rslts_pos_m;
  }

  rslts_m[rslts_pos_m] = filter_m;
}

void HallSignal::update_trshld() {
  if (!(info_m & SIGNAL_VALUE)) {
    threshold_top_m = filter_m + THRESHOLD_OFFSET;
    threshold_bottom_m = filter_m - THRESHOLD_OFFSET;
  }
}