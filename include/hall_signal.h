#pragma once

#include <cstdint>
#include <cstddef>

#define THRESHOLD_SET 0x04
#define FILTER_FILLED 0x02
#define SIGNAL_VALUE 0x01
#define RSLTS_BUFF_SIZE_BYTES 1024
#define NUM_OF_RSLTS RSLTS_BUFF_SIZE_BYTES / 2
#define FILTER_COEF 0.125
#define THRESHOLD_OFFSET 15

class HallSignal {
private:
    uint16_t rslts_m[NUM_OF_RSLTS];
    uint16_t filter_m;
    uint16_t threshold_top_m;
    uint16_t threshold_bottom_m;
    size_t rslts_pos_m;
    size_t filter_cnt_m;
    uint8_t info_m;
public:
    // returns pointer to the results
    const uint8_t* rslts() const;
    const uint16_t* p16_rslts() const;
    // returns index, where the next result will be added
    size_t rslts_pos() const;
    size_t rslts_pos_bytes() const;
    void add_value(uint16_t value);
    // takes size in vals(bytes / 2) for uin16_t, size_bytes must be able to be divided by 2
    void add_values(const uint16_t* data, size_t size_vals);
    bool rslts_filled() const;
    uint8_t info() const;
    void update_trshld();
    uint16_t filter_value() const;
    HallSignal();
private:
    void check_signal();
    void add_rslt();
};