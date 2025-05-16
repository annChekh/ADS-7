// Copyright 2021 NNTU-CS
#include "train.h"
Train::Train() : countOp(0), first(nullptr) {}
void Train::addCar(bool light) {
    Car* new_car = new Car{light, nullptr, nullptr};
    if (!first) {
        first = new_car;
        first->next = first;
        first->prev = first;
    } else {
        Car* last_car = first->prev;
        last_car->next = new_car;
        new_car->prev = last_car;
        new_car->next = first;
        first->prev = new_car;
    }
}

int Train::getLength() {
    if (!first || !first->next) return 0;
    countOp = 0;
    Car* current_car = first;
    const bool original_light = first->light;
    if (!original_light) {
        first->light = true;
    }
    int distance = 0;
    while (true) {
        current_car = current_car->next;
        countOp++;
        distance++;
        if (current_car->light) {
            current_car->light = false;
            for (int i = 0; i < distance; i++) {
                current_car = current_car->prev;
                countOp++;
            }
            if (current_car == first && !current_car->light) {
                break;
            }
            distance = 0;
        }
    }
    first->light = original_light;
    return distance;
}

int Train::getOpCount() {
    return countOp;
}
