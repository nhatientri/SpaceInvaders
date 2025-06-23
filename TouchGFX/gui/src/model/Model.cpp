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
        // Điều kiện logic tùy chỉnh
        int xPos;
        if (adc_value <= 5) {
            xPos = -3; // tốc độ di chuyển sang trái
        }
        else if (adc_value > 15) {
            xPos = 3; // tốc độ di chuyển sang phải
        }
        else {
        	xPos = 0;
        }
        modelListener->updatePlayerX(xPos);
    }


    // Giảm cooldown nếu đang > 0
    if (fireCooldown > 0)
        fireCooldown--;

    // Đọc trạng thái nút switch
    bool isPressed = (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) == GPIO_PIN_RESET);

    if (isPressed && fireCooldown == 0) {
        // Bắn đạn
        modelListener->fireBullet();

        // Đặt lại thời gian chờ giữa các phát (tùy bạn chỉnh)
        fireCooldown = 20;  // 10 tick → ~166ms nếu tick = 60Hz
    }

}
