/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    usbcfg_LPC17xx.h
 * Purpose: USB Custom Configuration
 * Version: V1.21
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.21 Removed unsupported DMA
 *          V1.20 Added vendor specific support
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#ifndef __USBCFG_LPC17xx_H
#define __USBCFG_LPC17xx_H


//*** <<< Use Configuration Wizard in Context Menu >>> ***


/*
// <h> USB Configuration
//   <o0> USB Power
//        <i> Default Power Setting
//        <0=> Bus-powered
//        <1=> Self-powered
//   <o1> Max Number of Interfaces <1-256>
//   <o2> Max Number of Endpoints  <1-32>
//   <o3> Max Endpoint 0 Packet Size
//        <8=> 8 Bytes <16=> 16 Bytes <32=> 32 Bytes <64=> 64 Bytes
// </h>
*/

#define USB_POWER           1
#define USB_IF_NUM          1
#define USB_EP_NUM          32
#define USB_MAX_PACKET0     8


/*
// <h> USB Event Handlers
//   <h> Device Events
//     <o0.0> Power Event
//     <o1.0> Reset Event
//     <o2.0> Suspend Event
//     <o3.0> Resume Event
//     <o4.0> Remote Wakeup Event
//     <o5.0> Start of Frame Event
//     <o6.0> Error Event
//   </h>
//   <h> Endpoint Events
//     <o7.0>  Endpoint 0 Event
//     <o7.1>  Endpoint 1 Event
//     <o7.2>  Endpoint 2 Event
//     <o7.3>  Endpoint 3 Event
//     <o7.4>  Endpoint 4 Event
//     <o7.5>  Endpoint 5 Event
//     <o7.6>  Endpoint 6 Event
//     <o7.7>  Endpoint 7 Event
//     <o7.8>  Endpoint 8 Event
//     <o7.9>  Endpoint 9 Event
//     <o7.10> Endpoint 10 Event
//     <o7.11> Endpoint 11 Event
//     <o7.12> Endpoint 12 Event
//     <o7.13> Endpoint 13 Event
//     <o7.14> Endpoint 14 Event
//     <o7.15> Endpoint 15 Event
//   </h>
//   <h> USB Core Events
//     <o8.0>  Set Configuration Event
//     <o9.0>  Set Interface Event
//     <o10.0> Set/Clear Feature Event
//   </h>
// </h>
*/

#define USB_POWER_EVENT     0
#define USB_RESET_EVENT     1
#define USB_SUSPEND_EVENT   0
#define USB_RESUME_EVENT    0
#define USB_WAKEUP_EVENT    0
#define USB_SOF_EVENT       0
#define USB_ERROR_EVENT     0
#define USB_EP_EVENT        0x0003
#define USB_CONFIGURE_EVENT 1
#define USB_INTERFACE_EVENT 0
#define USB_FEATURE_EVENT   0


/*
// <e0> USB Class Support
//   <i> enables USB Class specific Requests
//   <e1> Human Interface Device (HID)
//     <o2> Interface Number <0-255>
//   </e>
//   <e3> Mass Storage
//     <o4> Interface Number <0-255>
//   </e>
//   <e5> Audio Device
//     <o6> Control Interface Number <0-255>
//     <o7> Streaming Interface 1 Number <0-255>
//     <o8> Streaming Interface 2 Number <0-255>
//   </e>
//   <e9> Communication Device
//     <o10> Control Interface Number <0-255>
//     <o11> Bulk Interface Number <0-255>
//     <o12> Max Communication Device Buffer Size
//        <8=> 8 Bytes <16=> 16 Bytes <32=> 32 Bytes <64=> 64 Bytes 
//   </e>
// </e>
*/

#define USB_CLASS           1
#define USB_HID             1
#define USB_HID_IF_NUM      0
#define USB_MSC             0
#define USB_MSC_IF_NUM      0
#define USB_AUDIO           0
#define USB_ADC_CIF_NUM     0
#define USB_ADC_SIF1_NUM    1
#define USB_ADC_SIF2_NUM    2
#define USB_CDC  			0
#define USB_CDC_CIF_NUM     0
#define USB_CDC_DIF_NUM     1
#define USB_CDC_BUFSIZE     64

/*
// <e0> USB Vendor Support
//   <i> enables USB Vendor specific Requests
// </e>
*/
#define USB_VENDOR          0


#endif  /* __USBCFG_LPC17xx_H */
