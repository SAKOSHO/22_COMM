/*************************************************************************
 * File         :spi.c                       				 
 * Date         :2020/8/4					 
 * Summary      :Use for spi communication			
 * CPU type     :PIC16F886						 
 * Compiler     :XC8							 
 * Author       :Akaru Oishi						 
 * Description  :		 
 *              :				 
 *              :		 
 *              :			 
 * ***********************************************************************

/*---File Include---*/
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "spi.h"
#include "MCP2515.h"

char strage[_CANRX_STRAGE_SIZE];
char id_strage[16];

/*---Initiation---*/
void MCP2515_init(char bps)
{                                                                               //初期設定
    Write(_CANCTRL , 0b10001000);                                               //コンフィギュレーションモード
    Write(_BFPCTRL , 0b00000000);                                               //RXnBFピン制御と状態初期化
    Write(_TXB0CTRL , 0b00000000);                                              //送信バッファ0制御レジスタ初期化
    Write(_RXB0CTRL , 0b00000000);                                              //受信バッファ0制御レジスタ初期化
    Write(_RXB1CTRL , 0b00000000);                                              //受信バッファ1制御レジスタ初期化
    Write(_CANINTE , 0b00000000);                                               //割り込み初期化
    Write(_CANINTF , 0b00000000);                                               //割り込みフラグ初期化
    Write(_EFLG , 0b00000000);                                                  //エラーフラグ初期化
    
    if(bps == 0)
    {
        Bit_Modify(_CNF1 , 0b00111111 , 0b00000111);                            //BRP=7
        Bit_Modify(_CNF2 , 0b11111111 , 0b10110001);                            //BLTMODE=1（PS2の長さはCLF3にて）、SAM=0,PHSEG1=6,PRGSEG=1
        Bit_Modify(_CNF3 , 0b11111111 , 0b00000101);                            //PHSEG2=2
    }
    if(bps == 1)
    {
        Bit_Modify(_CNF1 , 0b00111111 , 0b00000001);                            //BRP=1
        Bit_Modify(_CNF2 , 0b11111111 , 0b10110001);                            //BLTMODE=1（PS2の長さはCLF3にて）、SAM=0,PHSEG1=6,PRGSEG=1
        Bit_Modify(_CNF3 , 0b11111111 , 0b00000101);                            //PHSEG2=2
    }
    if(bps == 2)
    {
        Bit_Modify(_CNF1 , 0b00111111 , 0b00000000);                                //BRP=0
        Bit_Modify(_CNF2 , 0b11111111 , 0b10110001);                                //BLTMODE=1（PS2の長さはCLF3にて）、SAM=0,PHSEG1=6,PRGSEG=1
        Bit_Modify(_CNF3 , 0b11111111 , 0b00000101);                                //PHSEG2=2
    }
    
}

void MCP2515_Open(char rxint)
{
    if(rxint == 1)
    {
        Bit_Modify(_CANCTRL , 0b11100000 , 0b00000000);                         //通常動作モード
        INTCONbits.GIE = 1;                                                     //割り込み設定
        INTCONbits.PEIE = 1;
        INTCONbits.INTE = 1;
        INTCONbits.INTF = 0;
        TRISBbits.TRISB0 = 1;
        OPTION_REGbits.INTEDG = 0;
    }
    else
    {
        Bit_Modify(_CANCTRL , 0b11100000 , 0b00000000);                         //通常動作モード
        INTCONbits.INTE = 0;
    }
};

void Strage_Crea()
{
    memset(strage,'\0',_CANRX_STRAGE_SIZE);
}

/*---Communication---*/
void Write(char address , char value)
{
    PORTAbits.RA5 = 0;
    spi_putc(0b00000010);
    spi_putc(address);
    spi_putc(value);
    PORTAbits.RA5 = 1;
}

char Read(char address)
{
    char data;
    
    PORTAbits.RA5 = 0;
    spi_putc(0b00000011);
    spi_putc(address);
    data = spi_putc(0b11111111);
    PORTAbits.RA5 = 1;
    return data;
}

char Read_Status(void)
{
    char data;
    
    PORTAbits.RA5 = 0;
    spi_putc(0b10100000);
    spi_putc(0b11111111);
    data = spi_putc(0b11111111);
    PORTAbits.RA5 = 1;
    return data;
}

char RX_Status(void)
{
    char data;
    
    PORTAbits.RA5 = 0;
    spi_putc(0b10110000);
    spi_putc(0b11111111);
    data = spi_putc(0b11111111);
    PORTAbits.RA5 = 1;
    return data;
}

void Bit_Modify(char address , char mask , char value)
{
    PORTAbits.RA5 = 0;
    spi_putc(0b00000101);
    spi_putc(address);
    spi_putc(mask);
    spi_putc(value);
    PORTAbits.RA5 = 1;
}

char* Read_RX_Buffer(char buffer , char bytes)
{
    PORTAbits.RA5 = 0;
    spi_putc(buffer);
    for(char i = 0 ; i < bytes ; i++){
        strage[i] = spi_putc(0);
    }
    PORTAbits.RA5 = 1;
    
    return strage;
}

char* Read_RX_ID(char buffer , char bytes)
{
    PORTAbits.RA5 = 0;
    spi_putc(buffer);
    for(char i = 0 ; i < bytes ; i++){
        id_strage[i] = spi_putc(0);
    }
    PORTAbits.RA5 = 1;
    
    return id_strage;
}

void Load_TX_Data(char buffer , char bytes , char* p)
{
    PORTAbits.RA5 = 0;
    spi_putc(buffer);
    for(char i = 0 ; i < bytes ; i++){
        spi_putc(*p);
        p++;
    }
    PORTAbits.RA5 = 1;
}

void Load_TX_ID(char buffer , char sid_h , char sid_l , char eid_8 , char eid_0)
{
    PORTAbits.RA5 = 0;
    spi_putc(buffer);
    spi_putc(sid_h);
    spi_putc(sid_l);
    spi_putc(eid_8);
    spi_putc(eid_0);
    PORTAbits.RA5 = 1;
}

void RTS0(char time)
{
    PORTAbits.RA5 = 0;
    spi_putc(0b10000001);
    PORTAbits.RA5 = 1;
    if(time == 0)
    {
        __delay_us(1500);
    }
    if(time == 1)
    {
        __delay_us(400);
    }
    if(time == 2){
        __delay_us(200);
    }
};

void RTS0_CSS(char time)
{
    PORTAbits.RA5 = 0;
    spi_putc(0b10000001);
    PORTAbits.RA5 = 1;
    if(time == 0)
    {
        __delay_us(1000);
    }
    if(time == 1)
    {
        __delay_us(240);
    }
    if(time == 2)
    {
        __delay_us(120);
    }
};

void RTS1(void);
void RTS2(void);