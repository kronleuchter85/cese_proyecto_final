#include "commons.h"
#include "stdint.h"


#ifndef MOCK_SUPPORT_H
#define MOCK_SUPPORT_H

typedef enum {
    ADC_WIDTH_BIT_9  = 0, /*!< ADC capture width is 9Bit. */
    ADC_WIDTH_BIT_10 = 1, /*!< ADC capture width is 10Bit. */
    ADC_WIDTH_BIT_11 = 2, /*!< ADC capture width is 11Bit. */
    ADC_WIDTH_BIT_12 = 3, /*!< ADC capture width is 12Bit. */
    ADC_WIDTH_MAX,
} adc_bits_width_t;

typedef enum {
    ADC1_CHANNEL_0 = 0, /*!< ADC1 channel 0 is GPIO36 */
    ADC1_CHANNEL_1,     /*!< ADC1 channel 1 is GPIO37 */
    ADC1_CHANNEL_2,     /*!< ADC1 channel 2 is GPIO38 */
    ADC1_CHANNEL_3,     /*!< ADC1 channel 3 is GPIO39 */
    ADC1_CHANNEL_4,     /*!< ADC1 channel 4 is GPIO32 */
    ADC1_CHANNEL_5,     /*!< ADC1 channel 5 is GPIO33 */
    ADC1_CHANNEL_6,     /*!< ADC1 channel 6 is GPIO34 */
    ADC1_CHANNEL_7,     /*!< ADC1 channel 7 is GPIO35 */
    ADC1_CHANNEL_MAX,
} adc1_channel_t;

typedef enum {
    ADC_ATTEN_DB_0   = 0,  ///<No input attenuation, ADC can measure up to approx.
    ADC_ATTEN_DB_2_5 = 1,  ///<The input voltage of ADC will be attenuated extending the range of measurement by about 2.5 dB
    ADC_ATTEN_DB_6   = 2,  ///<The input voltage of ADC will be attenuated extending the range of measurement by about 6 dB
    ADC_ATTEN_DB_12  = 3,  ///<The input voltage of ADC will be attenuated extending the range of measurement by about 12 dB
    ADC_ATTEN_DB_11 = ADC_ATTEN_DB_12,  ///<This is deprecated, it behaves the same as `ADC_ATTEN_DB_12`
    ADC_ATTEN_MAX,
} adc_atten_t;

typedef enum {
    ADC_CHANNEL_0 = 0, /*!< ADC channel */
    ADC_CHANNEL_1,     /*!< ADC channel */
    ADC_CHANNEL_2,     /*!< ADC channel */
    ADC_CHANNEL_3,     /*!< ADC channel */
    ADC_CHANNEL_4,     /*!< ADC channel */
    ADC_CHANNEL_5,     /*!< ADC channel */
    ADC_CHANNEL_6,     /*!< ADC channel */
    ADC_CHANNEL_7,     /*!< ADC channel */
    ADC_CHANNEL_8,     /*!< ADC channel */
    ADC_CHANNEL_9,     /*!< ADC channel */
    ADC_CHANNEL_MAX,
} adc_channel_t;

typedef enum {
    ADC_UNIT_1 = 1,          /*!< SAR ADC 1. */
    ADC_UNIT_2 = 2,          /*!< SAR ADC 2. */
    ADC_UNIT_BOTH = 3,       /*!< SAR ADC 1 and 2. */
    ADC_UNIT_ALTER = 7,      /*!< SAR ADC 1 and 2 alternative mode. */
    ADC_UNIT_MAX,
} adc_unit_t;


typedef struct {
    adc_unit_t adc_num;                     /**< ADC number*/
    adc_atten_t atten;                      /**< ADC attenuation*/
    adc_bits_width_t bit_width;             /**< ADC bit width */
    uint32_t coeff_a;                       /**< Gradient of ADC-Voltage curve*/
    uint32_t coeff_b;                       /**< Offset of ADC-Voltage curve*/
    uint32_t vref;                          /**< Vref used by lookup table*/
    const uint32_t *low_curve;              /**< Pointer to low Vref curve of lookup table (NULL if unused)*/
    const uint32_t *high_curve;             /**< Pointer to high Vref curve of lookup table (NULL if unused)*/
    uint8_t version;                        /**< ADC Calibration */
} esp_adc_cal_characteristics_t;

typedef enum {
    ESP_ADC_CAL_VAL_EFUSE_VREF = 0,         /**< Characterization based on reference voltage stored in eFuse*/
    ESP_ADC_CAL_VAL_EFUSE_TP = 1,           /**< Characterization based on Two Point values stored in eFuse*/
    ESP_ADC_CAL_VAL_DEFAULT_VREF = 2,       /**< Characterization based on default reference voltage*/
    ESP_ADC_CAL_VAL_EFUSE_TP_FIT = 3,       /**< Characterization based on Two Point values and fitting curve coefficients stored in eFuse */
    ESP_ADC_CAL_VAL_MAX,
    ESP_ADC_CAL_VAL_NOT_SUPPORTED = ESP_ADC_CAL_VAL_MAX,
} esp_adc_cal_value_t;


// typedef int esp_err_t;

int adc1_get_raw(adc1_channel_t channel);
uint32_t esp_adc_cal_raw_to_voltage(uint32_t adc_reading, const esp_adc_cal_characteristics_t *chars);

esp_err_t adc1_config_width(adc_bits_width_t width_bit);
esp_err_t adc1_config_channel_atten(adc1_channel_t channel, adc_atten_t atten);

esp_adc_cal_value_t esp_adc_cal_characterize(adc_unit_t adc_num,
                                             adc_atten_t atten,
                                             adc_bits_width_t bit_width,
                                             uint32_t default_vref,
                                             esp_adc_cal_characteristics_t *chars);


void ESP_ERROR_CHECK(esp_err_t x) ;

#endif // MOCK_SUPPORT_H