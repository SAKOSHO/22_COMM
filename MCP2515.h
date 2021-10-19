/**********************************************************************
 * File         :spi.h                       
 * Date         :2020/8/4
 * Summary      :Use for spi communication
 * CPU type     :PIC16F886
 * Compiler     :XC8
 * Author       :Sasaki Sho
 * Discription  :MCP2515のヘッダファイル
* ***********************************************************************/



#ifndef __MCP2515_H
#define __MCP2515_H

/*---Define---*/
#define _BFPCTRL                            0b00001100
#define _TXB0CTRL                           0b00110000
#define _TXB1CTRL                           0b01000000
#define _TXB2CTRL                           0b01010000
#define _RXB0CTRL                           0b01100000
#define _RXB1CTRL                           0b01110000

#define _TXRTSCTRL                          0b00001100
#define _CANCTRL                            0b00001111
#define _CNF1                               0b00101010
#define _CNF2                               0b00101001
#define _CNF3                               0b00101000
#define _TXB0DLC                            0b00110101
#define _TXB1DLC                            0b01000101
#define _TXB2DLC                            0b01010101
#define _RXB0DLC                            0b01100101
#define _RXF0SIDH                           0b00000000
#define _RXF0SIDL                           0b00000001
#define _RXF0EID8                           0b00000010
#define _RXF0EID0                           0b00000011
#define _RXF1SIDH                           0b00000100
#define _RXF1SIDL                           0b00000101
#define _RXM0SIDH                           0b00100000
#define _RXM0SIDL                           0b00100001
#define _RXM0EID8                           0b00100010
#define _RXM0EID0                           0b00100011
#define _RXM1SIDH                           0b00100100
#define _RXM1SIDL                           0b00100101
#define _RXB0SIDH                           0b01100001
#define _RXB0SIDL                           0b01100010
#define _RXB0EID8                           0b01100011
#define _RXB0EID0                           0b01100100
#define _RXB1SIDH                           0b01110001
#define _RXB1SIDL                           0b01110010
#define _RXB1EID8                           0b01110011
#define _RXB1EID0                           0b01110100
#define _CANSTAT                            0b00001110
#define _CANINTE                            0b00101011
#define _CANINTF                            0b00101100
#define _EFLG                               0b00101101

/*---Define（Read RX Buffer format）---*/
#define _F_RXB0SIDH                         0b10010000
#define _F_RXB0D0                           0b10010010
#define _F_RXB1SIDH                         0b10010100
#define _F_RXB1D0                           0b10010110

/*---Define（Load TX Buffer format）---*/
#define _F_TXB0SIDH                         0b01000000
#define _F_TXB0D0                           0b01000001
#define _F_TXB1SIDH                         0b01000010
#define _F_TXB1D0                           0b01000011
#define _F_TXB2SIDH                         0b01000100
#define _F_TXB2D0                           0b01000101

/*---Flagbit---*/
#define _Flagbit0                           0b00000001
#define _Flagbit1                           0b00000010
#define _Flagbit2                           0b00000100
#define _Flagbit3                           0b00001000
#define _Flagbit4                           0b00010000
#define _Flagbit5                           0b00100000
#define _Flagbit6                           0b01000000
#define _Flagbit7                           0b10000000


#define _CANRX_STRAGE_SIZE                  8                  

/*--Prototype--*/
void MCP2515_init(char bps);
void MCP2515_Open(char rxint);
void Strage_Crea();
void Write(char address , char data);
char Read(char address);
char Read_Status(void);
char RX_Status(void);
void Bit_Modify(char address , char mask , char value);
char* Read_RX_Buffer(char buffer , char bytes);
char* Read_RX_ID(char buffer , char bytes);
void Load_TX_Data(char buffer , char bytes ,char* p);
void Load_TX_ID(char buffer , char sid_h , char sid_l , char eid_8 , char e_id_0);
void RTS0(char time);
void RTS0_CSS(char time);
void RTS1(void);
void RTS2(void);
#endif
