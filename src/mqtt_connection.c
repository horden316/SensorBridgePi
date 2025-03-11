#include "mqtt_connection.h"
#define ADDRESS  "tcp://localhost:1883"
#define CLIENTID "ModularClient"
#define QOS      1
#define TIMEOUT  10000L

// 宣告一個全域的 MQTTClient 變數
static MQTTClient client;

int mqtt_connect(void) {
    Config config;
    if (read_config_json("config.json", &config) != 0) {
        printf("讀取設定檔失敗\n");
        return -1;
    }
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    int rc;

    if ((rc = MQTTClient_create(&client, ADDRESS, CLIENTID,
                                  MQTTCLIENT_PERSISTENCE_NONE, NULL)) != MQTTCLIENT_SUCCESS) {
        printf("建立 MQTT client 失敗，錯誤代碼：%d\n", rc);
        return rc;
    }
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = config.username;
    conn_opts.password = config.password;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        printf("連線失敗，錯誤代碼：%d\n", rc);
        return rc;
    }
    printf("成功連線到 MQTT Broker (%s)\n", ADDRESS);
    return MQTTCLIENT_SUCCESS;
}

void mqtt_publish(const char* topic, const char* payload) {
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;

    pubmsg.payload = (char *)payload;
    pubmsg.payloadlen = (int)strlen(payload);
    pubmsg.qos = QOS;
    pubmsg.retained = 0;
    
    int rc = MQTTClient_publishMessage(client, topic, &pubmsg, &token);
    if (rc != MQTTCLIENT_SUCCESS) {
        printf("發佈訊息失敗，錯誤代碼：%d\n", rc);
        return;
    }
    MQTTClient_waitForCompletion(client, token, TIMEOUT);
    printf("已發佈訊息：%s 到 topic：%s\n", payload, topic);
}

void mqtt_disconnect(void) {
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    printf("MQTT 連線已斷線\n");
}
