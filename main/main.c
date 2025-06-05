/*	ESP-NimBLE SPP Server Example

	This example code is in the Public Domain (or CC0 licensed, at your option.)

	Unless required by applicable law or agreed to in writing, this
	software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
	CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <inttypes.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/message_buffer.h"
#include "nvs_flash.h"
#include "esp_log.h"

static const char *TAG = "MAIN";

MessageBufferHandle_t xMessageBufferTx;
MessageBufferHandle_t xMessageBufferRx;

// The total number of bytes (not messages) the message buffer will be able to hold at any one time.
size_t xBufferSizeBytes = 1024;
// The size, in bytes, required to hold each item in the message,
size_t xItemSize = 256;

void nimble_spp_task(void * pvParameters);
void cdc_acm_vcp_task(void *pvParameters);

void app_main(void)
{
	// Initialize NVS
	// It is used to store PHY calibration data
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK( ret );

	// Create MessageBuffer
	xMessageBufferTx = xMessageBufferCreate(xBufferSizeBytes);
	configASSERT( xMessageBufferTx );
	xMessageBufferRx = xMessageBufferCreate(xBufferSizeBytes);
	configASSERT( xMessageBufferRx );

	// Start tasks
	xTaskCreate(nimble_spp_task, "NIMBLE_SPP", 1024*4, NULL, 2, NULL);
	//xTaskCreate(cdc_acm_vcp_task, "CDC_ACM_VCP", 1024*4, NULL, 10, NULL);
	xTaskCreate(cdc_acm_vcp_task, "CDC_ACM_VCP", 1024*4, NULL, 2, NULL);
}
