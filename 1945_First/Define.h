#pragma once

#define WINDOW CoreManager::getInstance()->getWindow()
#define SINGLE(classType) static classType* getInstance() {static classType mInstance; return &mInstance;} 
#define IS_TIC(key)   InputManager::getInstance()->isTic(key)
#define IS_PRESS(key) InputManager::getInstance()->isPress(key)
#define IS_BACK(key)  InputManager::getInstance()->isBack(key)
#define DS TimeManager::getInstance()->getDS()
#define ADD_STAGE_CHANGE(eType, sChangeType) EventManager::getInstance()->addStageChange(eType, sChangeType)
#define COLOR_WHITE RGB(255, 255, 255)