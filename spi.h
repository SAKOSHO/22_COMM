/**********************************************************************
 * File         :spi.h                       
 * Date         :2020/8/4
 * Summary      :Use for spi communication
 * CPU type     :PIC16F886
 * Compiler     :XC8
 * Author       :Akaru Oishi
* ***********************************************************************/



#ifndef __SPI_H
#define __SPI_H

/*---Define---*/
#define _SSPSTAT_CONFIG                     0b01000000                          //CKE（bit6）が1（立ち上がりで送信）
#define _SSPCON_CONFIG                      0b00100000                          //SPIマスタモード、クロックはFosc/4、クロックがLowでアイドル、    
#define _XTAL_FREQ                          20000000

/*--Prototype--*/
void spi_init(void);
char spi_putc(char c);

#endif