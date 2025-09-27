#include "signal_processing.h"

HallSignal::HallSignal() 
  : rslts_pos_m(0){

}

bool HallSignal::check_signal() const {

}

const uint16_t* HallSignal::rslts() const {
  return const_cast<const uint16_t*>(rslts_m);
}

uint16_t* HallSignal::rslts_pos() const {
  return rslts_pos_m;
}

void HallSignal::add_value(uint16_t value) {
  filter_m = filter_m * (1.0 - FILTER_COEF) + value * FILTER_COEF;
  ++filter_cnt_m;
  
  if (filter_cnt_m == 8) {
    filter_cnt_m = 0;

    if (rslts_pos_m == 1023) {
      rslts_pos_m = 0;
    }
    else {
      ++rslts_pos_m;
    }

    rslts_m[rslts_pos_m] = filter_m;
  }
}

bool HallSignal::rslts_filled() const {
  return rslts_filled_m;
}