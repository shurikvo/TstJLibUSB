#pragma once
#include "libusb.h"


class JLibUSBFunc
{
public:
	int Init()
	{
		return libusb_init(NULL);
	}

	void Exit()
	{
		libusb_free_device_list(Devs, 1);
		libusb_exit(NULL);
	}

private:
	libusb_context *LibContext;
	libusb_device **Devs;

};
