/*
 * RTC.h
 *
 *  Created on: Nov 4, 2025
 *      Author: TITHI
 */

#ifndef SRC_INTERNAL_RTC_RTC_H_
#define SRC_INTERNAL_RTC_RTC_H_

#define READRTCTIME	60

extern bool bTimeToReadRTC;
extern bool bBatchStartedFromKeyboardFlag;

extern int8_t ucReadRTCTime;
extern volatile int  uiStoreDataTime;

#pragma pack(push)  // To solve structure padding issue
#pragma pack(1)
typedef struct
{
    uint8_t ucDD;
    uint8_t ucMM;
    uint8_t ucYY;
    uint8_t ucHR;
    uint8_t ucMN;
    uint8_t ucSC;
}DEVICERTC;
#pragma pack(pop)

typedef union
{
    DEVICERTC   DeviceRTC;
    uint8_t i[6];
}RTCBUFFER;


extern RTCBUFFER CurrentRTC;

void SetRTC(RTCBUFFER *RTCStorage);
void ReadRTC(RTCBUFFER *RTCStorage);
void ReadRTCFromInterrupt(uint8_t *RTCStorage, RTC_HandleTypeDef *hrtc_it);

#endif /* SRC_INTERNAL_RTC_RTC_H_ */
