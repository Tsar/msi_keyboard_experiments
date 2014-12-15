#!/bin/bash
g++ -fpermissive switch_700ms.cpp -lhidapi-libusb -o switch_700ms
g++ turn_off.cpp -lhidapi-libusb -o turn_off
