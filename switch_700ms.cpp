#include <stdlib.h>
#include <time.h>
#include <iostream>

#include <hidapi/hidapi.h>

enum Region {
    LEFT   = 1,
    MIDDLE = 2,
    RIGHT  = 3
};

enum Color {
    OFF    = 0,
    RED    = 1,
    ORANGE = 2,
    YELLOW = 3,
    GREEN  = 4,
    SKY    = 5,
    BLUE   = 6,
    PURPLE = 7,
    WHITE  = 8
};

enum Intensity {
    LIGHT = 3,
    LOW   = 2,
    MED   = 1,
    HIGH  = 0
};

enum Mode {
    NORMAL  = 1,
    GAMING  = 2,
    BREATHE = 3,
    DEMO    = 4,
    WAVE    = 5
};

void setColor(hid_device* keyboard, Region region, Color color, Intensity intensity) {
    unsigned char buf[8];
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 66;
    buf[3] = region;
    buf[4] = color;
    buf[5] = intensity;
    buf[6] = 0;
    buf[7] = 236;
    hid_send_feature_report(keyboard, buf, 8);
}

void setMode(hid_device* keyboard, Mode mode) {
    unsigned char buf[8];
    buf[0] = 1;
    buf[1] = 2;
    buf[2] = 65;
    buf[3] = mode;
    buf[4] = 0;
    buf[5] = 0;
    buf[6] = 0;
    buf[7] = 236;
    hid_send_feature_report(keyboard, buf, 8);
}

int main() {
    hid_device* keyboard = hid_open(0x1770, 0xff00, NULL);
    if (!keyboard) {
        std::cerr << "MSI keyboard not found!" << std::endl;
        return 1;
    }

    srand(time(0));

    timespec _t;
    _t.tv_sec = 0;
    _t.tv_nsec = 700000000;  // 700 ms

    while (true) {
        setColor(keyboard, LEFT, rand() % 9 + 1, HIGH);
        setColor(keyboard, MIDDLE, rand() % 9 + 1, HIGH);
        setColor(keyboard, RIGHT, rand() % 9 + 1, HIGH);
        setMode(keyboard, NORMAL);

        nanosleep(&_t, 0);
    }

    return 0;
}
