#include "data.h"

static const char *TAG1 = "MQTT_Publisher";

uint32_t MQTT_CONNECTED = 0;

#define MQTT_BROKER_URI "mqtt://mqtt.eclipseprojects.io"//"mqtt://etransito.vitoria.ifes.edu.br"
// #define MQTT_CLIENT_ID NULL
// #define MQTT_USERNAME "c43b745e-0ee3-4ca3-a41b-413068a7fe32"
// #define MQTT_PASSWORD "9c02894934fd40d999678f4576b6e7e6"
#define MQTT_TOPIC "record"

static esp_mqtt_client_handle_t client;

static esp_err_t mqtt_event_handler_cb(esp_mqtt_event_handle_t event)
{
    //esp_mqtt_client_handle_t client = event->client;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG1, "MQTT_EVENT_CONNECTED");
            MQTT_CONNECTED = 1;         
            //esp_mqtt_client_publish(client, "topic", "data", 0, 1, 0);
            //esp_mqtt_client_subscribe(client, "topic", 0);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG1, "MQTT_EVENT_DISCONNECTED");
            MQTT_CONNECTED = 0;
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

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    ESP_LOGD(TAG1, "Event dispatched from event loop base=%s, event_id=%ld", base, (long int)event_id);
    mqtt_event_handler_cb(event_data);
}

static void mqtt_app_start(void) {
    ESP_LOGI(TAG1, "STARTING MQTT");
    const esp_mqtt_client_config_t mqtt_cfg = {
        .broker = {
            .address.uri = MQTT_BROKER_URI,
            .address.port = 1883
        },
        // .credentials = {
        //     .username = MQTT_USERNAME,
        //     .authentication.password = MQTT_PASSWORD,
        // }
    };

    // esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
}

void Publisher_Task(void)
{
  while (true)
  {
    if(MQTT_CONNECTED)
    {
        char *data_to_send = geolocation();
        esp_mqtt_client_publish(client, MQTT_TOPIC, data_to_send, 0, 1, 0);
        vTaskDelay(pdMS_TO_TICKS(60000));
    }
  }
}

void send_data()
{
    mqtt_app_start();
    xTaskCreate(Publisher_Task, "Publisher_Task", 1024 * 5, NULL, 5, NULL);
}