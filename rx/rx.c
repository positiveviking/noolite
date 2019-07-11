#include <libusb-1.0/libusb.h>

#define RX_DEV_VID 0x16c0 //0x5824
#define RX_DEV_PID 0x05df //0x1503
#define RX_DEV_CONFIG 1
#define RX_DEV_INTF 0
#define RX_EP_IN 0x81
#define RX_EP_OUT 0x01
#define RX_REQ_NO 0x9
#define RX_REQ_VALUE 0x300

void exit_usb()
{
    libusb_exit(NULL);
}

int RX_OPEN_OK = 0;
int RX_OPEN_NO_DEVICE = 10;
int RX_OPEN_BUSY = 11;
int RX_OPEN_CONFIG_ERROR = 12;
int RX_OPEN_CLAIM_ERROR = 12;

struct RX_open_result
{
    libusb_device_handle *handle;
    int err_code;
};

struct RX_open_result open_rx()
{
    struct RX_open_result result;
    libusb_init(NULL);

    libusb_device_handle *handle = libusb_open_device_with_vid_pid(NULL, RX_DEV_VID, RX_DEV_PID);
    if (handle == NULL)
    {
        // exit_usb();
        result.err_code = RX_OPEN_NO_DEVICE;
        return result;
    }

    if (libusb_kernel_driver_active(handle, RX_DEV_INTF))
        libusb_detach_kernel_driver(handle, RX_DEV_INTF);

    int ret = libusb_set_configuration(handle, RX_DEV_CONFIG);
    if (ret < 0)
    {
        libusb_close(handle);
        // exit_usb()
        if (ret == LIBUSB_ERROR_BUSY)
        {
            result.err_code = RX_OPEN_BUSY;
        }
        result.err_code = RX_OPEN_CONFIG_ERROR;
        return result;
    }

    if (libusb_claim_interface(handle, RX_DEV_INTF) < 0)
    {
        libusb_close(handle);
        result.err_code = RX_OPEN_CLAIM_ERROR;
        return result;
    }

    result.err_code = RX_OPEN_OK;
    result.handle = handle;
    return result;
}
