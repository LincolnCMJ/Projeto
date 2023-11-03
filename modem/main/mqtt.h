#include "data.h"

static const char *TAG1 = "MQTT_Publisher";

//#define MQTT_BROKER_URI "mqtt://mqtt.eclipseprojects.io:1883"
#define MQTT_BROKER_URI "mqtt://etransito.vitoria.ifes.edu.br:1883"
#define MQTT_CLIENT_ID NULL
#define MQTT_USERNAME "c43b745e-0ee3-4ca3-a41b-413068a7fe32"
#define MQTT_PASSWORD "9c02894934fd40d999678f4576b6e7e6"
#define MQTT_TOPIC "FPS"
// #define MQTT_PAYLOAD "data_to_send"

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event) {
    esp_mqtt_client_handle_t client = event->client;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG1, "MQTT_EVENT_CONNECTED");
            char *data_to_send = generate_json();
            esp_mqtt_client_publish(client, MQTT_TOPIC, data_to_send, 0, 1, 0);
            //esp_mqtt_client_subscribe(client, "topic", 0);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG1, "MQTT_EVENT_DISCONNECTED");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG1, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG1, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG1, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG1, "MQTT_EVENT_DATA");
            printf("\nTOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG1, "MQTT_EVENT_ERROR");
            break;
        default:
            ESP_LOGI(TAG1, "Other event id:%d", event->event_id);
            break;
        }
    return ESP_OK;
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG1, "Event dispatched from event loop base=%s, event_id=%ld", base, (long int)event_id);
    mqtt_event_handler_cb(event_data);
}

static void mqtt_app_start(void) {
    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address.uri = MQTT_BROKER_URI,
        },
        .credentials = {
            .username = MQTT_USERNAME,
            .client_id = MQTT_CLIENT_ID,
            .authentication = {
                .password = MQTT_PASSWORD,
                //.certificate = NULL,
            }
        },
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
}

void send() {
    vTaskDelay(pdMS_TO_TICKS(2000));
    mqtt_app_start();
}