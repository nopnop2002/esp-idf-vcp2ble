typedef enum {BLE_CONNECT_EVT, BLE_AUTH_EVT, BLE_WRITE_EVT, BLE_DISCONNECT_EVT, BLE_UART_EVT} COMMAND;

#define PAYLOAD_SIZE 128

typedef struct {
	size_t length;
	uint8_t payload[PAYLOAD_SIZE];
} CMD_t;
