#pragma once

#define SIGNAL_HIGH true
#define SIGNAL_LOW false

#define RSLTS_SIZE 1024
#define FILTER_COEF 0.125

#define THRESHOLD_OFFSET 15

class HallSignal {
  uint16_t rslts_m[RSLTS_SIZE];
  uint16_t filter_m;
  uint16_t threshold_top_m;
  uint16_t threshold_bottom_m;
  size_t rslts_pos_m;
  size_t filter_cnt_m;
  bool rslts_filled_m;
  bool signal_lvl_m;
public:
  bool check_signal() const;
  const uint16_t* rslts() const;
  uint16_t rslts_pos() const;
  void add_value(uint16_t value);
  bool rslts_filled() const;
}