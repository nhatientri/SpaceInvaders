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
        modelListener->updateADCValue(adc_value);
    }

    // Biến static để giữ trạng thái giữa các tick
    static int fireCooldown = 0;

    // Giảm cooldown nếu đang > 0
    if (fireCooldown > 0)
        fireCooldown--;

    // Đọc trạng thái nút switch
    bool isPressed = (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET);

    if (isPressed && fireCooldown == 0) {
        // Bắn đạn
        modelListener->fireBullet();

        // Đặt lại thời gian chờ giữa các phát (tùy bạn chỉnh)
        fireCooldown = 10;  // 10 tick → ~166ms nếu tick = 60Hz
    }

}
