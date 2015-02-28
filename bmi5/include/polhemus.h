/*
Polhemus Tracker Terminal version 1.0.0 -- Terminal Interface to Polhemus Trackers: Fastrak, Patriot, and Liberty
Copyright  ©  2009  Polhemus, Inc.

This file is part of Tracker Terminal.

Tracker Terminal is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Tracker Terminal is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Tracker Terminal.  If not, see <http://www.gnu.org/licenses/>.

*************************************************************************

Tracker Terminal version 1.0.0 uses the libusb library version 1.0
libusb Copyright © 2007-2008 Daniel Drake <dsd@gentoo.org>
libusb Copyright © 2001 Johannes Erdfelt <johannes@erdfelt.com>
Licensed under the GNU Lesser General Public License version 2.1 or later.
*/



#ifndef PITRACKER_H_
#define PITRACKER_H_

#include <libusb-1.0/libusb.h>
#include <termios.h>

enum {NO_CNX=-1,USB_CNX,RS232_CNX};

#ifndef BYTE
#define BYTE uint8
#endif

class polhemus
{


public:

	polhemus();
	~polhemus();

	int UsbConnect(int trackerType);
	int Rs232Connect(const char *port,int baud=115200);
	int Write(void *data,int len);
	int Write(const char *data);
	int Read(void *buf,int maxLen);
	int GetCnxType();
	void Close();

private:
	int UsbConnect2(int Vid,int Pid,int writeEp, int readEp);
	int WriteUsbData(void *data,int len);
	int WriteRs232Data(void *data,int len);
	int ReadUsbData(void *buf,int len);
	int ReadRs232Data(void *buf,int maxLen);


	libusb_device_handle *m_handle;
	int m_cnxType;
	int m_usbWriteEp;
	int m_usbReadEp;
	int m_usbVid;
	int m_usbPid;
	int m_bCloseUsbLibrary;

	int m_FtContUsb;  // Fastrak needs some special flags
	int m_isFt;       // It is a special case since it puts its USB continuous data
	int m_lastFtCont; // over an interrupt endpoint

	int m_rs232Port;
	struct termios m_initialAtt;

	pthread_mutex_t m_mutex;



};

enum {TRKR_LIB_HS,TRKR_LIB,TRKR_PAT,TRKR_FT,NUM_SUPP_TRKS};

#endif
