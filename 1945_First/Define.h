#pragma once

#define SINGLE(classType) static classType* getInstance() {static classType mInstance; return &mInstance;} 
#define IS_TIC(key)   InputManager::getInstance()->isTic(key);
#define IS_PRESS(key) InputManager::getInstance()->isPress(key);
#define IS_BACK(key)  InputManager::getInstance()->isBack(key);