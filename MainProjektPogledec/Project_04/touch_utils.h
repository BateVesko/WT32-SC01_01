//Project_03
#ifndef TOUCH_UTILS_H
#define TOUCH_UTILS_H

#include <bb_captouch.h>
#include <TFT_eSPI.h>

extern TFT_eSPI tft; // Деклариране на външен обект за дисплея

bb_captouch touch; // Създаване на обект за тъчскрийна

// Функция за инициализация на тъчскрийна
void initTouch() {
    touch.init(); // Инициализиране на тъчскрийна
    // Може да се наложи да зададете специфични GPIO пинове за вашия хардуер
    touch.setPins(21, 22, 23, 24); // Примерни GPIO пинове, заменете със съответните
}

// Функция за проверка на тъч събития
bool getTouch(int16_t &x, int16_t &y) {
    TOUCHINFO info;
    if (touch.getSamples(&info)) {
        if (info.count > 0) {
            x = info.x[0];
            y = info.y[0];
            return true;
        }
    }
    return false;
}

// Примерна функция за обработка на тъч събития
void handleTouch() {
    int16_t x, y;
    if (getTouch(x, y)) {
        Serial.print("Touched at: ");
        Serial.print(x);
        Serial.print(", ");
        Serial.println(y);

        // Проверка на различни зони на екрана и извършване на действия
        if (x > 0 && x < 80 && y > 0 && y < 80) {
            Serial.println("Touched fan icon");
            // Вашият код за действие при тъч на иконката за вентилатор
        }

        // Добавете още проверки за други зони и иконки на екрана
    }
}

#endif // TOUCH_UTILS_H
