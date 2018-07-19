﻿#include <thread>

#include "SimpleAudioEngine.h"

#include "Helpers.h"
#include "SceneGameRoom.h"
#include "ServiceGame.h"

SceneBase* SceneGameRoom::createScene()
{
    return SceneGameRoom::create();
}

bool SceneGameRoom::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    addKeyboardListener();


    msgLabel = Label::createWithTTF("Msg", "Fonts/arial.ttf", 30);
    
    msgLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    this->addChild(msgLabel);

    srand((unsigned)time(NULL));
    id = rand() % 60000;

    Singleton<ServiceGame>::GetInstance()->JoinRoom(30082, id, [&](string res) -> void {
        msgLabel->setString(res);
    });


    auto t = new std::thread(&SceneGameRoom::GetState, this);

    return true;
}

void SceneGameRoom::GetState() {
    Singleton<ServiceGame>::GetInstance()->GetFrame([&](string res) -> void {
        msgLabel->setString(res);
    });
}

// 添加键盘事件监听器
void SceneGameRoom::addKeyboardListener() {
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(SceneGameRoom::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(SceneGameRoom::onKeyReleased, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void SceneGameRoom::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
    switch (code) {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
    case EventKeyboard::KeyCode::KEY_A:
        Singleton<ServiceGame>::GetInstance()->SendInput(1);
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
    case EventKeyboard::KeyCode::KEY_D:
        Singleton<ServiceGame>::GetInstance()->SendInput(2);
        break;
    }
}

void SceneGameRoom::onKeyReleased(EventKeyboard::KeyCode code, Event* event) {
    switch (code) {
    case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
    case EventKeyboard::KeyCode::KEY_A:
    case EventKeyboard::KeyCode::KEY_CAPITAL_A:
        Singleton<ServiceGame>::GetInstance()->SendInput(3);
        break;
    case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
    case EventKeyboard::KeyCode::KEY_D:
    case EventKeyboard::KeyCode::KEY_CAPITAL_D:
        Singleton<ServiceGame>::GetInstance()->SendInput(4);
        break;
    }
}

void SceneGameRoom::updateLayer(Tag tag)
{

}

void SceneGameRoom::updateScene(Tag tag)
{

}
