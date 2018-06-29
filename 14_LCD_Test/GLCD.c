/*----------------------------------------------------------------------------
 * Name:    GLCD.c
 * Purpose: MCB1700 low level Graphic LCD (320x240 pixels) functions
 * Version: V1.00
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <LPC17xx.H>                    /* NXP LPC17xx definitions            */

#include "GLCD.h"
#include "font.h"


/*********************** Hardware specific configuration **********************/

/*------------------------- Speed dependant settings -------------------------*/

/* If processor works on high frequency delay has to be increased, it can be
   increased by factor 2^N by this constant                                   */
#define DELAY_2N    18

/*---------------------- Graphic LCD size definitions ------------------------*/

#define WIDTH       320                 /* Screen Width (in pixels)           */
#define HEIGHT      240                 /* Screen Hight (in pixels)           */
//#define WIDTH       240                 /* Screen Width (in pixels)           */
//#define HEIGHT      320                 /* Screen Hight (in pixels)           */
#define BPP         16                  /* Bits per pixel                     */
#define BYPP        ((BPP+7)/8)         /* Bytes per pixel                    */

/*--------------- Graphic LCD interface hardware definitions -----------------*/
#define SSP_DATA    (0x100)              /* RS bit 1 within start byte         */
#define SSP_INDEX   (0x00)              /* RS bit 0 within start byte         */

/*---------------------------- Global variables ------------------------------*/

/******************************************************************************/
static volatile unsigned short TextColor = Black, BackColor = White;


/************************ Local auxiliary functions ***************************/
static void GLCD_SetX(unsigned int x, unsigned int width);
static void GLCD_SetY(unsigned int y, unsigned int height);

/*******************************************************************************
* Delay in while loop cycles                                                   *
*   Parameter:    cnt:    number of while cycles to delay                      *
*   Return:                                                                    *
*******************************************************************************/

static void delay (int cnt)
{
	cnt <<= DELAY_2N;
	while (cnt--);
}


/*******************************************************************************
* Send 1 byte over serial communication                                        *
*   Parameter:    byte:   byte to be sent                                      *
*   Return:                                                                    *
*******************************************************************************/

static __inline unsigned char ssp_send (unsigned int byte)
{
	LPC_SSP1->DR = byte & 0x1FF;
	while (LPC_SSP1->SR & (1 << 4));      /* Wait for transfer to finish        */
	return (LPC_SSP1->DR) & 0xFF;                /* Return received value              */
}


/*******************************************************************************
* Write command to LCD controller                                              *
*   Parameter:    c:      command to be written                                *
*   Return:                                                                    *
*******************************************************************************/

static __inline void wr_cmd (unsigned char c)
{
	LPC_GPIO0->FIOPIN &= ~(1 << 6);
	ssp_send(c | SSP_INDEX);
	LPC_GPIO0->FIOPIN |=  (1 << 6);
}


/*******************************************************************************
* Write data to LCD controller                                                 *
*   Parameter:    c:      data to be written                                   *
*   Return:                                                                    *
*******************************************************************************/

static __inline void wr_dat (unsigned short c)
{
	LPC_GPIO0->FIOPIN &= ~(1 << 6);
	ssp_send(c | SSP_DATA);    /* Write : RS = 1, RW = 0       */
	LPC_GPIO0->FIOPIN |=  (1 << 6);
}


/*******************************************************************************
* Write Pixel data to LCD controller                                                 *
*   Parameter:    c:      Pixel data to be written                                   *
*   Return:                                                                    *
*******************************************************************************/

static __inline void wr_pixel (unsigned short c)
{
	LPC_GPIO0->FIOPIN &= ~(1 << 6);
	ssp_send((c >> 8) | SSP_DATA);                       /* Write D8..D15                */
	ssp_send((c & 0xFF) | SSP_DATA);                       /* Write D0..D7                 */
	LPC_GPIO0->FIOPIN |=  (1 << 6);
}

/*******************************************************************************
* Write to LCD register                                                        *
*   Parameter:    reg:    register to be read                                  *
*                 val:    value to write to register                           *
*******************************************************************************/

/*static __inline void wr_reg (unsigned char reg, unsigned short val)
{
	wr_cmd(reg);
	wr_dat(val);
}*/

/************************ Exported functions **********************************/

/*******************************************************************************
* Initialize the Graphic LCD controller                                        *
*   Parameter:                                                                 *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_init (void)
{
	/* Configure the LCD Control pins ------------------------------------------*/
	LPC_PINCON->PINSEL9 &= ~(3 << 24);    /* Pin P4.28 used for backlight       */
	LPC_GPIO4->FIODIR   |=  (1 << 28);    /* Pin P2.28 is output                */
	LPC_PINCON->PINSEL9 &= ~(3 << 26);    /* Pin P4.29 used for LCD CS          */
	LPC_GPIO4->FIODIR   |=  (1 << 29);    /* Pin P2.29 is output                */
	LPC_GPIO4->FIOPIN   |=  (1 << 29);    /* Pin P2.29 is high                  */

	/*-- SSP Configuration -----------------------------------------------------*/
	LPC_SC->PCONP       |=  (1 << 10);    /* Enable power to SSP1 block         */
	LPC_SC->PCLKSEL0    |=  (2 << 20);    /* SSP1 clock = CCLK / 2              */
	LPC_GPIO0->FIODIR   |=  (1 <<  6);    /* Pin P0.6 is GPIO output (SSEL1)    */
	LPC_GPIO0->FIOSET    =  (1 <<  6);    /* Set P0.6 high                      */
	LPC_PINCON->PINSEL0 &= ~0x000FC000;
	LPC_PINCON->PINSEL0 |=  0x000A8000;   /* Select SSP mode for SSP pins       */

	LPC_SSP1->CR0        =  (   0 << 7) | /* CPHA = 0                           */
	                      (   0 << 6) | /* CPOL = 0                           */
	                      (   0 << 4) | /* Frame format = SPI                 */
                          ((9-1)<< 0) ; /* Data size = 9 bits                 */
	LPC_SSP1->CPSR       =  6;            /* Clock Rate = 6.25MHz               */
	LPC_SSP1->CR1        =  (   1 << 1);  /* Enable SSP1                        */

	delay(5);                             /* Delay 50 ms                        */

#if 1 // new
	//************* Start Initial Sequence **********//
	wr_cmd(0xCF); // Power Control B
	wr_dat(0x00);
	wr_dat(0x83);
	wr_dat(0X30);

	wr_cmd(0xED); // Power on sequence control
	wr_dat(0x64);
	wr_dat(0x03);
	wr_dat(0X12);
	wr_dat(0X81);

	wr_cmd(0xE8); // Driver timing control A
	wr_dat(0x85);
	wr_dat(0x01);
	wr_dat(0x79);

	wr_cmd(0xCB); // Power Control A
	wr_dat(0x39);
	wr_dat(0x2C);
	wr_dat(0x00);
	wr_dat(0x34);
	wr_dat(0x02);

	wr_cmd(0xF7); // Pump ratio control
	wr_dat(0x20);

	wr_cmd(0xEA); // Driver timing control B
	wr_dat(0x00);
	wr_dat(0x00);

	wr_cmd(0xC0); //Power control
	wr_dat(0x1D); //VRH[5:0]

	wr_cmd(0xC1); //Power control
	wr_dat(0x11); //SAP[2:0];BT[3:0]

	wr_cmd(0xC5); //VCM control
	wr_dat(0x33);
	wr_dat(0x34);

	wr_cmd(0xC7); //VCM control2
	wr_dat(0Xbe);

	wr_cmd(0xF6); // Memory Access Control
	wr_dat(0x01);
	wr_dat(0x10);// RGB16bit -> RGB18bit
	wr_dat(0x00);

	wr_cmd(0x3A); // COLMOD: Pixel Format Set
	wr_dat(0x55); // 16bits/pixel

	wr_cmd(0x36); // Memory Access Control
	wr_dat((1<<7)|(0<<6)|(1<<5)|(1<<4)|(0<<3)|(0<<2)); // MY, MX, MV, ML, BGR, MH

	wr_cmd(0xB1); // Frame Rate Control
	wr_dat(0x00);
	wr_dat(0x1B);

	wr_cmd(0xB6); // Display Function Control
	wr_dat(0x0A);
	wr_dat(0xA2);

	wr_cmd(0xF2); // 3Gamma Function Disable
	wr_dat(0x00);

	wr_cmd(0x26); //Gamma curve selected
	wr_dat(0x01);

	wr_cmd(0xE0); //Set Gamma
	wr_dat(0x0F);
	wr_dat(0x23);
	wr_dat(0x1F);
	wr_dat(0x09);
	wr_dat(0x0f);
	wr_dat(0x08);
	wr_dat(0x4B);
	wr_dat(0Xf2);
	wr_dat(0x38);
	wr_dat(0x09);
	wr_dat(0x13);
	wr_dat(0x03);
	wr_dat(0x12);
	wr_dat(0x07);
	wr_dat(0x04);

	wr_cmd(0XE1); //Set Gamma
	wr_dat(0x00);
	wr_dat(0x1d);
	wr_dat(0x20);
	wr_dat(0x02);
	wr_dat(0x11);
	wr_dat(0x07);
	wr_dat(0x34);
	wr_dat(0x81);
	wr_dat(0x46);
	wr_dat(0x06);
	wr_dat(0x0e);
	wr_dat(0x0c);
	wr_dat(0x32);
	wr_dat(0x38);
	wr_dat(0x0F);

	wr_cmd(0x11); //Exit Sleep

	delay(12);

	wr_cmd(0x29); //Display on
#endif

  LPC_GPIO4->FIOPIN   |=  (1 << 28);    /* Turn backlight on                  */
}


static void GLCD_SetX(unsigned int x, unsigned int width)
{
	wr_cmd(0x2A);
	wr_dat((x>>8) & 0xFF);
	wr_dat(x & 0xFF);
	wr_dat(((x+width-1)>>8) & 0xFF);
	wr_dat((x+width-1) & 0xFF);
}

static void GLCD_SetY(unsigned int y, unsigned int height)
{
	wr_cmd(0x2B);
	wr_dat((y>>8) & 0xFF);
	wr_dat(y & 0xFF);
	wr_dat(((y+height-1)>>8) & 0xFF);
	wr_dat((y+height-1) & 0xFF);
}

void GLCD_putPixel(unsigned int x, unsigned int y)
{
	GLCD_SetX(x, 1);
	GLCD_SetY(y, 1);

    wr_cmd(0x2C);
    wr_pixel(TextColor);
}


/*******************************************************************************
* Set foreground color                                                         *
*   Parameter:    color:  color for clearing display                           *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_setTextColor(unsigned short color)
{
	TextColor = color;
}


/*******************************************************************************
* Set background color                                                         *
*   Parameter:    color:  color for clearing display                           *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_setBackColor(unsigned short color)
{
	BackColor = color;
}


/*******************************************************************************
* Clear display                                                                *
*   Parameter:    color:  color for clearing display                           *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_clear (unsigned short color)
{
	unsigned int   i;

	GLCD_SetX(0, WIDTH);
	GLCD_SetY(0, HEIGHT);

	wr_cmd(0x2C); // RAM Write

	for(i = 0; i < (WIDTH*HEIGHT); i++)
		wr_pixel(color);
}


/*******************************************************************************
* Draw character on given position                               *
*   Parameter:     x :        horizontal position                              *
*                  y :        vertical position                                *
*                  c*:        pointer to color value                           *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_drawChar(unsigned int x, unsigned int y, unsigned short *c)
{
	unsigned int index = 0;
	int  i = 0;

	GLCD_SetX(x, 16);
	GLCD_SetY(y, 24);

    wr_cmd(0x2C);

	for(index = 0; index < 24; index++)
	{
		for(i = 0; i <16; i++)
		{
			if((c[index] & (1 << i)) == 0x00)
			{
				wr_pixel(BackColor);
			}
			else
			{
				wr_pixel(TextColor);
			}
		}
	}
}


/*******************************************************************************
* Disply character on given line                                               *
*   Parameter:     c :        ascii character                                  *
*                  x:        X position                                      *
*                  y:        Y position                                      *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_displayChar(unsigned int x, unsigned int y, unsigned char  c)
{
	c -= 32;
	GLCD_drawChar(x, y, &ASCII_Table[c * 24]);
}


/*******************************************************************************
* Disply string on given line                                                  *
*   Parameter:     s*:        pointer to string                                *
*                  y:        Y position                                      *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_displayStringLn(unsigned int y, char *s)
{
	unsigned int i = 0;
	unsigned int refcolumn = 0;

	while ((*s != 0) & (i < 20))                   /* write the string character by character on lCD */
	{
		GLCD_displayChar(refcolumn, y, *s);         /* Display one character on LCD */
		refcolumn += 16;                             /* Decrement the column position by 16 */
		s++;                                         /* Point on the next character */
		i++;                                         /* Increment the character counter */
	}
}


/*******************************************************************************
* Clear given line                                                             *
*   Parameter:     y:        Y position                                      *
*   Return:                                                                    *
*******************************************************************************/
void GLCD_clearLn(unsigned int y)
{
	GLCD_displayStringLn(y, "                    ");
}


/*******************************************************************************
* Display graphical bitmap image at position x horizontally and y vertically   *
* (This function is optimized for 16 bits per pixel format, it has to be       *
*  adapted for any other bits per pixel format)                                *
*   Parameter:      x:        horizontal position                              *
*                   y:        vertical position                                *
*                   w:        width of bitmap                                  *
*                   h:        height of bitmap                                 *
*                   bitmap:   address at which the bitmap data resides         *
*   Return:                                                                    *
*******************************************************************************/

void GLCD_bitmap (unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *bitmap)
{
	unsigned int   i;
	unsigned int   len = w*h;
	unsigned short *bitmap_ptr = (unsigned short *)bitmap;

	GLCD_SetX(x, w);
	GLCD_SetY(y, h);

	wr_cmd(0x2C);
	for (i = 0; i < len; i++)
	{
		wr_pixel(*bitmap_ptr++);
	}
}


/******************************************************************************/
