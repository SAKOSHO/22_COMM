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

/*---Initiation---*/
void spi_init(void)
{
    SSPCON = _SSPCON_CONFIG;
    SSPSTAT = _SSPSTAT_CONFIG;
    INTCONbits.GIE = 1;                                                         //割り込み設定
    INTCONbits.PEIE = 1;                                                        //割り込み設定
    PIE1bits.SSPIE = 0;                                                         //SSP割り込みをイネーブル
    PIR1bits.SSPIF = 0;                                                         //SSP割り込みフラグをクリア
    TRISAbits.TRISA4 = 0;                                                       //CSピンを出力設定
    TRISAbits.TRISA5 = 0;                                                       //CSピンを出力設定
    TRISCbits.TRISC3 = 0;                                                       //CLKピンを出力設定
    TRISCbits.TRISC4 = 1;                                                       //DIピンを入力設定
    TRISCbits.TRISC5 = 0;                                                       //DOピンを出力設定
    PORTAbits.RA4 = 1;                                                          //CSピンをHighで待機
    PORTAbits.RA5 = 1;                                                          //CSピンをHighで待機
}

/*---Communication---*/
char spi_putc(char c)
{
    char dumy;                                                                  //ダミーリード用変数宣言
    char data;                                                                  //データ格納用変数宣言
    
    dumy = SSPBUF;                                                              //SSPバッファダミーリード                                                           
    if(!SSPSTATbits.BF)
    {                                                        //送信用レジスタフラグチェック（空で0）
        SSPBUF = c;                                                             
    }
    while(!SSPSTATbits.BF);                                                     //送信（受信）完了待ち
    data = SSPBUF;                                                              //バッファリード
    
    //__delay_us(1);
    return data;
}