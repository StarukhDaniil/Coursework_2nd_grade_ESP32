#pragma once

#include <cstdint>
#include <cstddef>

#define FILTER_FILLED 0x02
#define SIGNAL_VALUE 0x01
#define RSLTS_SIZE 1024
#define FILTER_COEF 0.125
#define FILTER_SIZE 8
#define THRESHOLD_OFFSET 5

class HallSignal {
    uint16_t rslts_m[RSLTS_SIZE];
    uint16_t filter_m;
    uint16_t threshold_top_m;
    uint16_t threshold_bottom_m;
    size_t rslts_pos_m;
    size_t filter_cnt_m;
    uint8_t info_m;
public:
    const uint16_t* rslts() const;
    uint16_t rslts_pos() const;
    void add_value(uint16_t value);
    bool rslts_filled() const;
    uint8_t info() const;
    void update_trshld();
    uint16_t filter_value() const;
    HallSignal();
private:
    void check_signal();
    void add_rslt();
    uint16_t derivative() const;
};