// polhemus.cpp


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

#include <termios.h>
#include <pthread.h>
#include "polhemus.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

#define FT_INT   0x84
#define FT_PID   0x0002


typedef struct _USB_PARAMS {
	int vid;
	int pid;
	int writeEp;
	int readEp;
} *LPUSB_PARAMS,USB_PARAMS;
// usb vid/pids for Polehemus trackers
USB_PARAMS usbTrkParams[NUM_SUPP_TRKS]= {
	{0x0f44,0xff20,0x04,0x88},  // Liberty high speed
	{0x0f44,0xff12,0x02,0x82},   // Liberty (what we have)
	{0x0f44,0xef12,0x02,0x82},  // Patriot (what I used to have)
	{0x0f44,0x0002,0x02,0x82}
};  // Fastrak

polhemus::polhemus()
{
	m_handle=NULL;
	m_rs232Port=-1;
	m_cnxType=NO_CNX;
	m_bCloseUsbLibrary=0;
	m_FtContUsb=m_isFt=m_lastFtCont=0;
	pthread_mutex_init(&m_mutex,NULL);
}

polhemus::~polhemus()
{
	if (m_cnxType!=NO_CNX)
		Close();
}

int polhemus::UsbConnect(int trackerType)
{
	return UsbConnect2(
	               usbTrkParams[trackerType].vid,
	               usbTrkParams[trackerType].pid,
	               usbTrkParams[trackerType].writeEp,
	               usbTrkParams[trackerType].readEp);
}

int polhemus::UsbConnect2(int Vid,int Pid,int writeEp, int readEp)
{

	int r=libusb_init(NULL);
	if (r<0) {
		fprintf(stderr,"libusb failed initialization attempt\n");
		return -1;
	}
	m_bCloseUsbLibrary=1;
	if (Pid==FT_PID)
		m_isFt=1;

	m_usbVid=Vid;
	m_usbPid=Pid;
	m_usbWriteEp=writeEp;
	m_usbReadEp=readEp;

	m_handle=libusb_open_device_with_vid_pid(NULL,m_usbVid,m_usbPid);
	if (!m_handle)
		return -1;

	m_cnxType=USB_CNX;

	return 0;
}

int polhemus::Rs232Connect(const char *port,int baud/*=115200*/)
{

	int br;
	struct termios newAtt;

	switch (baud) {
	case 9600:
		br=B9600;
		break;
	case 19200:
		br=B19200;
		break;
	case 38400:
		br=B38400;
		break;
	case 57600:
		br=B57600;
		break;
	case 115200:
		br=B115200;
		break;
	default:
		printf("Baud value not available in this application, defaulting to 115200\n");
		br=B115200;
	}

	m_rs232Port=open(port,O_RDWR|O_NOCTTY|O_NDELAY);
	if (m_rs232Port==-1) {
		printf("Error opening serial port.\nDo you have necessary permissions to access %s?\n",port);
		return -1;
	}

	// set up terminal for raw data
	tcgetattr(m_rs232Port,&m_initialAtt);            // save this to restore later
	newAtt = m_initialAtt;
	cfmakeraw(&newAtt);
	cfsetspeed(&newAtt,br);           // set baud
	if (tcsetattr(m_rs232Port,TCSANOW,&newAtt)) {
		printf("Polhemus: Error setting terminal attributes\n");
		perror(":");
		close(m_rs232Port);
		return -2;
	}
	m_cnxType=RS232_CNX;
	return 0;
}

int polhemus::Write(void *data,int len)
{
	int bw=0;

	pthread_mutex_lock(&m_mutex);

	if (m_cnxType==USB_CNX)
		bw=WriteUsbData(data,len);
	else if (m_cnxType==RS232_CNX)
		bw=WriteRs232Data(data,len);
	else
		fprintf(stderr,"No Connection\n");

	pthread_mutex_unlock(&m_mutex);
	return bw;
}

int polhemus::Write(const char *data)
{
	int n = strlen(data);
	return Write((void *)data, n);
}

int polhemus::Read(void *buf,int maxLen)
{

	int br=0;

	pthread_mutex_lock(&m_mutex);
	if (m_cnxType==USB_CNX)
		br=ReadUsbData(buf,maxLen);
	else if (m_cnxType==RS232_CNX)
		br=ReadRs232Data(buf,maxLen);
	else
		fprintf(stderr,"No Connection\n");

	pthread_mutex_unlock(&m_mutex);
	return br;
}

void polhemus::Close()
{

	if (m_cnxType==USB_CNX) {
		libusb_close(m_handle);
		m_handle=NULL;
	}

	else if (m_cnxType==RS232_CNX) { // return attributes to initial settings
		printf("polhemus: closing serial connection.\n");
		tcsetattr(m_rs232Port,TCSANOW,&m_initialAtt);
		close(m_rs232Port);
		m_rs232Port=-1;
	}

	else
		fprintf(stderr,"No connection to close\n");

	if (m_bCloseUsbLibrary) {
		libusb_exit(NULL);
		m_bCloseUsbLibrary=0;
	}

	m_cnxType=NO_CNX;
}

int polhemus::WriteUsbData(void *data,int len)
{

	int bw;

	// special case for Fastrak, it puts its continuous data over an interrupt endpoint
	if (((*(char *)data)=='C') && m_isFt)
		m_FtContUsb=1;

	else if (((*(char *)data)=='c') && m_isFt)
		m_lastFtCont=1;

	libusb_bulk_transfer(m_handle,m_usbWriteEp,(BYTE *)data,len,&bw,50);
	return bw;
}

int polhemus::WriteRs232Data(void *data,int len)
{
	return write(m_rs232Port,data,len);
}

int polhemus::ReadUsbData(void *buf,int maxlen)
{
	int br;

	if (m_FtContUsb) {
		libusb_interrupt_transfer(m_handle,FT_INT,(BYTE *)buf,maxlen,&br,50); // Fastrak's interrupt endpoint
		if (m_lastFtCont && (br==0))
			m_FtContUsb=m_lastFtCont=0;
	} else
		libusb_bulk_transfer(m_handle,m_usbReadEp,(BYTE *)buf,maxlen,&br,50);

	return br;
}

int polhemus::ReadRs232Data(void *buf,int maxLen)
{

	return read(m_rs232Port,(BYTE *)buf,maxLen);
}

int polhemus::GetCnxType()
{
	return m_cnxType;
}
