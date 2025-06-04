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
#include "freertos/queue.h"
#include "nvs_flash.h"
#include "esp_log.h"

#include "cmd.h"

static const char *TAG = "MAIN";

QueueHandle_t xQueueTx;
QueueHandle_t xQueueRx;

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

	// Create Queue
	xQueueTx = xQueueCreate(10, sizeof(CMD_t));
	configASSERT( xQueueTx );
	xQueueRx = xQueueCreate( 10, sizeof(CMD_t) );
	configASSERT( xQueueRx );

	// Start tasks
	xTaskCreate(nimble_spp_task, "NIMBLE_SPP", 1024*4, NULL, 2, NULL);
	//xTaskCreate(cdc_acm_vcp_task, "CDC_ACM_VCP", 1024*4, NULL, 10, NULL);
	xTaskCreate(cdc_acm_vcp_task, "CDC_ACM_VCP", 1024*4, NULL, 2, NULL);
}
