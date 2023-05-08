#pragma once
#ifndef LORAWAN_HPP
#define LORAWAN_HPP

#include <LoRaWan-RAK4630.h>

#define LORAWAN_APP_DATA_BUFF_SIZE 32 /* buffer size in bytes of the data to be transmitted */

#define LORAWAN_DATARATE DR_0		/* LoRaMac datarates definition, from DR_0 to DR_5 */
#define LORAWAN_TX_POWER TX_POWER_5 /* LoRaMac tx power definition, from TX_POWER_0 to TX_POWER_15 */
#define LORAWAN_ADR LORAWAN_ADR_ON	/* LoRAMac enable ADR */
#define LORAWAN_DO_OTAA true		/* Enable OTAA */
#define JOINREQ_NBTRIALS 3			/* < Number of trials for the join request. */

extern DeviceClass_t lora_currClass;	/* class definition */
extern LoRaMacRegion_t lora_currRegion; /* Region */
extern lmh_confirm lora_currConfirm;	/* confirm/unconfirm packet definition */
extern uint8_t lora_appPort;			/* data port */
extern bool lora_isJoined;				/* whether the device has joined the network */

extern uint8_t lora_deviceEUI[8];
extern uint8_t lora_joinEUI[8];
extern uint8_t lora_appKey[16];

void initLoRaWan();

void lora_has_joined_handler();
void lora_join_failed_handler();
void lora_rx_handler(lmh_app_data_t *);
void lora_confirm_class_handler(DeviceClass_t);

void lora_send_data();

#endif // LORAWAN_HPP
