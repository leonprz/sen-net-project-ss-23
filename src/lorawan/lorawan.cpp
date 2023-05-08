#include "lorawan.hpp"
#include "debug.hpp"

DeviceClass_t lora_currClass = CLASS_A;
LoRaMacRegion_t lora_currRegion = LORAMAC_REGION_EU868;
lmh_confirm lora_currConfirm = LMH_UNCONFIRMED_MSG;
uint8_t lora_appPort = LORAWAN_APP_PORT;
bool lora_isJoined = false;

uint8_t lora_deviceEUI[8] = {0xAC, 0x1F, 0x09, 0xFF, 0xFE, 0x08, 0xFB, 0x6A};
uint8_t lora_joinEUI[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t lora_appKey[16] = {0x6A, 0xF2, 0x30, 0xDF, 0x9A, 0x10, 0x59, 0xD5, 0xC6, 0xEE, 0x5D, 0x1C, 0x9C, 0x17, 0x6D, 0x00};

static uint8_t lora_appDataBuffer[LORAWAN_APP_DATA_BUFF_SIZE];
static lmh_app_data_t lora_appData = {lora_appDataBuffer, 0, 0, 0, 0};
static uint32_t lora_msgCount = 0;
static uint32_t lora_msgFailCount = 0;

static lmh_param_t lora_params = {LORAWAN_ADR, LORAWAN_DATARATE, LORAWAN_PUBLIC_NETWORK, JOINREQ_NBTRIALS, LORAWAN_TX_POWER, LORAWAN_DUTYCYCLE_OFF};
static lmh_callback_t lora_callbacks = {BoardGetBatteryLevel, BoardGetUniqueId, BoardGetRandomSeed, lora_rx_handler, lora_has_joined_handler, lora_confirm_class_handler, lora_join_failed_handler};

void initLoRaWan()
{
	lora_rak4630_init();

	lmh_setDevEui(lora_deviceEUI);
	lmh_setAppEui(lora_joinEUI);
	lmh_setAppKey(lora_appKey);

	uint32_t err_code = lmh_init(&lora_callbacks, lora_params, LORAWAN_DO_OTAA, lora_currClass, lora_currRegion);
	if (err_code != 0)
	{
		MYLOG("LORAWAN", "lmh_init failed - %lu", err_code);
	}

	lmh_join();
}

void lora_has_joined_handler()
{
	MYLOG("LORAWAN", "device joined");
	lora_isJoined = true;
}

void lora_join_failed_handler()
{
	MYLOG("LORAWAN", "OTAA join failed");
}

void lora_rx_handler(lmh_app_data_t *appData)
{
	MYLOG("LORAWAN", "LoRa Packet received on port %u, size:%u, rssi:%d, snr:%u, data:%p", appData->port, appData->buffsize, appData->rssi, appData->snr, appData->buffer);
}

void lora_confirm_class_handler(DeviceClass_t devClass)
{
	MYLOG("LORAWAN", "switch to class %c done", "ABC"[devClass]);
	lora_appData.buffsize = 0;
	lora_appData.port = lora_appPort;
	lmh_send(&lora_appData, lora_currConfirm);
}

void lora_send_data()
{
	if (lmh_join_status_get() != LMH_SET)
	{
		MYLOG("LORAWAN", "not joined to a network");
		return;
	}

	memset(lora_appData.buffer, 0, LORAWAN_APP_DATA_BUFF_SIZE);
	lora_appData.port = lora_appPort;

	// WRITE PAYLOAD
	uint32_t i = 0;
	lora_appData.buffer[i++] = 'H';
	lora_appData.buffer[i++] = 'E';
	lora_appData.buffer[i++] = 'L';
	lora_appData.buffer[i++] = 'L';
	lora_appData.buffer[i++] = 'O';
	lora_appData.buffer[i++] = '!';
	lora_appData.buffsize = i;

	MYLOG("LORAWAN", "approx. time on air : %lu ms", Radio.TimeOnAir(MODEM_LORA, lora_appData.buffsize));

	lmh_error_status err = lmh_send(&lora_appData, lora_currConfirm);
	if (err == LMH_SUCCESS)
	{
		lora_msgCount++;
		MYLOG("LORAWAN", "lmh_send ok - %lu", lora_msgCount);
	}
	else
	{
		lora_msgFailCount++;
		MYLOG("LORAWAN", "lmh_send failed - %lu", lora_msgFailCount);
	}
}
