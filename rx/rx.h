#ifndef RX_H
#define RX_H

#include <libusb-1.0/libusb.h>

struct RX_open_result {
    libusb_device_handle *handle;
    int err_code;
};
typedef struct RX_open_result RX_open_result;

RX_open_result open_rx();

#endif