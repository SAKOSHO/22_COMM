/* 
 * File:   COM.h
 * Author: ç≤ÅXñÿ„ƒ
 *
 * Created on 2021/06/30, 17:40
 */

#ifndef COM_H
#define	COM_H

/*---ADS CAN Message---*/
/* SIDH */
#define SIDH_READ   0b01100000
#define SIDH_MODE   0b01100001
#define SIDH_DATA1  0b01100011
#define SIDH_DATA2  0b01100100

/* SIDL */
#define SIDL_W      0b00001001                                                  //WÇÃéûÇÃID
#define SIDL_R      0b00001000                                                  //RÇÃéûÇÃID

/* EID8 */
#define EID8_MODE   0b00000000
#define EID8_DATA1  0b00000000
#define EID8_DATA2  0b00000000

/* EID0 */
#define EID0_MODE   0b00000010
#define EID0_DATA1  0b00001010
#define EID0_DATA2  0b00001001

/* Filter */
#define Sub_Filt    0b01100000

/*---Modebit---*/
#define _ChargeMode                          0b00000001
#define _COMMMode                            0b00000010
#define _StanbyMode                          0b00000011
#define _MissionMode                         0b00000100
#define _SafetyMode                          0b00000101


#endif


