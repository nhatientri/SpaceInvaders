#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "main.h"
Model::Model() : modelListener(0)
{

}

extern ADC_HandleTypeDef hadc1;

void Model::tick() {
    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
        uint32_t adc_value = HAL_ADC_GetValue(&hadc1);
        int xPos = 30 + (adc_value * (210 - 20)) / 4095;
        modelListener->updatePlayerX(xPos);
    }
}
