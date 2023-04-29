#include "keyboardManager.h"
#include "..\raylib.h"

void KeyboardManager::AddKey(int Key, std::function<void()> Function, Mode KeyMode)
{
    auto WrapperFunc = [Function]() { Function(); };
    _keyFunctions.try_emplace(Key, WrapperFunc);
    KeyMapData Data = { false, KeyMode };
    _keyData.try_emplace(Key, Data);
    _keys.push_back(Key);
}

void KeyboardManager::RemoveKey(int Key)
{
    _keyData.erase(Key);
    _keyFunctions.erase(Key);
    std::remove(_keys.begin(), _keys.end(), Key);
}


void KeyboardManager::AddMouseButton(int Key, std::function<void()> Function, Mode KeyMode)
{
    auto WrapperFunc = [Function]() { Function(); };
    _mouseFunctions.try_emplace(Key, WrapperFunc);
    MouseMapData Data = { false, KeyMode };
    _mouseData.try_emplace(Key, Data);
    _miceButtons.push_back(Key);
}

void KeyboardManager::Update()
{
    for (auto& CurrentKey : _keys)
    {
        if (_keyData[CurrentKey].mode == Hold)
        {
            if (IsKeyDown(CurrentKey))
            {
                _keyFunctions[CurrentKey]();
                _keyData[CurrentKey].down = true;
            }
        }
        else if (_keyData[CurrentKey].mode == Press)
        {
            if (IsKeyPressed(CurrentKey))
            {
                _keyFunctions[CurrentKey]();
                _keyData[CurrentKey].down = true;
            }
        }
    }

    for (auto& CurrentMouseKey : _miceButtons)
    {
        if (_mouseData[CurrentMouseKey].mode == Hold)
        {
            if (IsMouseButtonDown(CurrentMouseKey))
            {
                _mouseFunctions[CurrentMouseKey]();
                _mouseData[CurrentMouseKey].down = true;
            }
        }
        else if (_mouseData[CurrentMouseKey].mode == Press)
        {
            if (IsMouseButtonPressed(CurrentMouseKey))
            {
                _mouseFunctions[CurrentMouseKey]();
                _mouseData[CurrentMouseKey].down = true;
            }
        }
    }
}

