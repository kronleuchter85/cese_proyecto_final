#ifndef __WIFI_COMMONS_H__
#define __WIFI_COMMONS_H__

#include "stdbool.h"
#include "commons.h"
#include "stdint.h"



#define CONFIG_EXAMPLE_WIFI_SSID "1"
#define CONFIG_EXAMPLE_WIFI_PASSWORD "1"

#define MAC2STR(mac) (mac)[0], (mac)[1], (mac)[2], (mac)[3], (mac)[4], (mac)[5]


typedef enum {
    WIFI_MODE_NULL = 0,  /**< null mode */
    WIFI_MODE_STA,       /**< WiFi station mode */
    WIFI_MODE_AP,        /**< WiFi soft-AP mode */
    WIFI_MODE_APSTA,     /**< WiFi station + soft-AP mode */
    WIFI_MODE_MAX
} wifi_mode_t;

typedef enum {
    WIFI_IF_STA = 1,
    WIFI_IF_AP  = 2,
} wifi_interface_t;

typedef struct {
    char *  event_handler;          /**< WiFi event handler */
    char *      osi_funcs;              /**< WiFi OS functions */
    char *      wpa_crypto_funcs;       /**< WiFi station crypto functions when connect */
    int                    static_rx_buf_num;      /**< WiFi static RX buffer number */
    int                    dynamic_rx_buf_num;     /**< WiFi dynamic RX buffer number */
    int                    tx_buf_type;            /**< WiFi TX buffer type */
    int                    static_tx_buf_num;      /**< WiFi static TX buffer number */
    int                    dynamic_tx_buf_num;     /**< WiFi dynamic TX buffer number */
    int                    rx_mgmt_buf_type;       /**< WiFi RX MGMT buffer type */
    int                    rx_mgmt_buf_num;        /**< WiFi RX MGMT buffer number */
    int                    cache_tx_buf_num;       /**< WiFi TX cache buffer number */
    int                    csi_enable;             /**< WiFi channel state information enable flag */
    int                    ampdu_rx_enable;        /**< WiFi AMPDU RX feature enable flag */
    int                    ampdu_tx_enable;        /**< WiFi AMPDU TX feature enable flag */
    int                    amsdu_tx_enable;        /**< WiFi AMSDU TX feature enable flag */
    int                    nvs_enable;             /**< WiFi NVS flash enable flag */
    int                    nano_enable;            /**< Nano option for printf/scan family enable flag */
    int                    rx_ba_win;              /**< WiFi Block Ack RX window size */
    int                    wifi_task_core_id;      /**< WiFi Task Core ID */
    int                    beacon_max_len;         /**< WiFi softAP maximum length of the beacon */
    int                    mgmt_sbuf_num;          /**< WiFi management short buffer number, the minimum value is 6, the maximum value is 32 */
    uint64_t               feature_caps;           /**< Enables additional WiFi features and capabilities */
    bool                   sta_disconnected_pm;    /**< WiFi Power Management for station at disconnected status */
    int                    espnow_max_encrypt_num; /**< Maximum encrypt number of peers supported by espnow */
    int                    magic;                  /**< WiFi init magic number, it should be the last field */
} wifi_init_config_t;

typedef enum {
    WIFI_EVENT_WIFI_READY = 0,           /**< ESP32 WiFi ready */
    WIFI_EVENT_SCAN_DONE,                /**< ESP32 finish scanning AP */
    WIFI_EVENT_STA_START,                /**< ESP32 station start */
    WIFI_EVENT_STA_STOP,                 /**< ESP32 station stop */
    WIFI_EVENT_STA_CONNECTED,            /**< ESP32 station connected to AP */
    WIFI_EVENT_STA_DISCONNECTED,         /**< ESP32 station disconnected from AP */
    WIFI_EVENT_STA_AUTHMODE_CHANGE,      /**< the auth mode of AP connected by ESP32 station changed */

    WIFI_EVENT_STA_WPS_ER_SUCCESS,       /**< ESP32 station wps succeeds in enrollee mode */
    WIFI_EVENT_STA_WPS_ER_FAILED,        /**< ESP32 station wps fails in enrollee mode */
    WIFI_EVENT_STA_WPS_ER_TIMEOUT,       /**< ESP32 station wps timeout in enrollee mode */
    WIFI_EVENT_STA_WPS_ER_PIN,           /**< ESP32 station wps pin code in enrollee mode */
    WIFI_EVENT_STA_WPS_ER_PBC_OVERLAP,   /**< ESP32 station wps overlap in enrollee mode */

    WIFI_EVENT_AP_START,                 /**< ESP32 soft-AP start */
    WIFI_EVENT_AP_STOP,                  /**< ESP32 soft-AP stop */
    WIFI_EVENT_AP_STACONNECTED,          /**< a station connected to ESP32 soft-AP */
    WIFI_EVENT_AP_STADISCONNECTED,       /**< a station disconnected from ESP32 soft-AP */
    WIFI_EVENT_AP_PROBEREQRECVED,        /**< Receive probe request packet in soft-AP interface */

    WIFI_EVENT_FTM_REPORT,               /**< Receive report of FTM procedure */

    /* Add next events after this only */
    WIFI_EVENT_STA_BSS_RSSI_LOW,         /**< AP's RSSI crossed configured threshold */
    WIFI_EVENT_ACTION_TX_STATUS,         /**< Status indication of Action Tx operation */
    WIFI_EVENT_ROC_DONE,                 /**< Remain-on-Channel operation complete */

    WIFI_EVENT_STA_BEACON_TIMEOUT,       /**< ESP32 station beacon timeout */

    WIFI_EVENT_MAX,                      /**< Invalid WiFi event ID */
} wifi_event_t;

typedef enum {
    WIFI_AUTH_OPEN = 0,         /**< authenticate mode : open */
    WIFI_AUTH_WEP,              /**< authenticate mode : WEP */
    WIFI_AUTH_WPA_PSK,          /**< authenticate mode : WPA_PSK */
    WIFI_AUTH_WPA2_PSK,         /**< authenticate mode : WPA2_PSK */
    WIFI_AUTH_WPA_WPA2_PSK,     /**< authenticate mode : WPA_WPA2_PSK */
    WIFI_AUTH_ENTERPRISE,       /**< authenticate mode : WiFi EAP security */
    WIFI_AUTH_WPA2_ENTERPRISE = WIFI_AUTH_ENTERPRISE,  /**< authenticate mode : WiFi EAP security */
    WIFI_AUTH_WPA3_PSK,         /**< authenticate mode : WPA3_PSK */
    WIFI_AUTH_WPA2_WPA3_PSK,    /**< authenticate mode : WPA2_WPA3_PSK */
    WIFI_AUTH_WAPI_PSK,         /**< authenticate mode : WAPI_PSK */
    WIFI_AUTH_WPA3_ENT_192,     /**< authenticate mode : WPA3_ENT_SUITE_B_192_BIT */
    WIFI_AUTH_MAX
} wifi_auth_mode_t;
typedef enum {
    WIFI_CIPHER_TYPE_NONE = 0,   /**< the cipher type is none */
    WIFI_CIPHER_TYPE_WEP40,      /**< the cipher type is WEP40 */
    WIFI_CIPHER_TYPE_WEP104,     /**< the cipher type is WEP104 */
    WIFI_CIPHER_TYPE_TKIP,       /**< the cipher type is TKIP */
    WIFI_CIPHER_TYPE_CCMP,       /**< the cipher type is CCMP */
    WIFI_CIPHER_TYPE_TKIP_CCMP,  /**< the cipher type is TKIP and CCMP */
    WIFI_CIPHER_TYPE_AES_CMAC128,/**< the cipher type is AES-CMAC-128 */
    WIFI_CIPHER_TYPE_SMS4,       /**< the cipher type is SMS4 */
    WIFI_CIPHER_TYPE_GCMP,       /**< the cipher type is GCMP */
    WIFI_CIPHER_TYPE_GCMP256,    /**< the cipher type is GCMP-256 */
    WIFI_CIPHER_TYPE_AES_GMAC128,/**< the cipher type is AES-GMAC-128 */
    WIFI_CIPHER_TYPE_AES_GMAC256,/**< the cipher type is AES-GMAC-256 */
    WIFI_CIPHER_TYPE_UNKNOWN,    /**< the cipher type is unknown */
} wifi_cipher_type_t;

typedef struct {
    uint8_t ssid[32];           /**< SSID of ESP32 soft-AP. If ssid_len field is 0, this must be a Null terminated string. Otherwise, length is set according to ssid_len. */
    uint8_t password[64];       /**< Password of ESP32 soft-AP. */
    uint8_t ssid_len;           /**< Optional length of SSID field. */
    uint8_t channel;            /**< Channel of soft-AP */
    wifi_auth_mode_t authmode;  /**< Auth mode of soft-AP. Do not support AUTH_WEP, AUTH_WAPI_PSK and AUTH_OWE in soft-AP mode. When the auth mode is set to WPA2_PSK, WPA2_WPA3_PSK or WPA3_PSK, the pairwise cipher will be overwritten with WIFI_CIPHER_TYPE_CCMP. */
    uint8_t ssid_hidden;        /**< Broadcast SSID or not, default 0, broadcast the SSID */
    uint8_t max_connection;     /**< Max number of stations allowed to connect in */
    uint16_t beacon_interval;   /**< Beacon interval which should be multiples of 100. Unit: TU(time unit, 1 TU = 1024 us). Range: 100 ~ 60000. Default value: 100 */
    wifi_cipher_type_t pairwise_cipher;   /**< Pairwise cipher of SoftAP, group cipher will be derived using this. Cipher values are valid starting from WIFI_CIPHER_TYPE_TKIP, enum values before that will be considered as invalid and default cipher suites(TKIP+CCMP) will be used. Valid cipher suites in softAP mode are WIFI_CIPHER_TYPE_TKIP, WIFI_CIPHER_TYPE_CCMP and WIFI_CIPHER_TYPE_TKIP_CCMP. */
    bool ftm_responder;         /**< Enable FTM Responder mode */
} wifi_ap_config_t;

typedef int wifi_sta_config_t;

typedef union {
    wifi_ap_config_t  ap;  /**< configuration of AP */
    wifi_sta_config_t sta; /**< configuration of STA */
} wifi_config_t;

typedef struct {
    uint8_t mac[6];           /**< MAC address of the station connected to ESP32 soft-AP */
    uint8_t aid;              /**< the aid that ESP32 soft-AP gives to the station connected to  */
    bool is_mesh_child;       /**< flag to identify mesh child */
} wifi_event_ap_staconnected_t;

typedef const char*  esp_event_base_t; 

typedef struct {
    uint8_t mac[6];           /**< MAC address of the station disconnects to ESP32 soft-AP */
    uint8_t aid;              /**< the aid that ESP32 soft-AP gave to the station disconnects to  */
    bool is_mesh_child;       /**< flag to identify mesh child */
} wifi_event_ap_stadisconnected_t;


esp_err_t esp_wifi_init(const wifi_init_config_t *config);
esp_err_t esp_wifi_set_mode(wifi_mode_t mode);
esp_err_t esp_wifi_set_config(wifi_interface_t interface, wifi_config_t *conf);
esp_err_t esp_wifi_start(void);


wifi_init_config_t WIFI_INIT_CONFIG_DEFAULT();

void ESP_ERROR_CHECK(esp_err_t x) ;

#define WIFI_EVENT 1
#define ESP_EVENT_ANY_ID 1


esp_err_t esp_event_handler_instance_register(int event_loop,
                                                  int32_t event_id,
                                                  void (*)(void *, const char *, int32_t,  void *),
                                                  void *arg,
                                                  int *instance);

void esp_netif_create_default_wifi_ap();

#endif

