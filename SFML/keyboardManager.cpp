#include "keyboardManager.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace util
{

}



void KeyboardManager::AddKey(sf::Keyboard::Key key, std::function<void()> function, Mode mode)
{
    auto wrapperFunc = [function]() { function(); };
    _keyFunctions.try_emplace(key, wrapperFunc);
    KeyMapData data = { false, mode };
    _keyData.try_emplace(key, data);
    _keys.push_back(key);
}



void KeyboardManager::AddMouseButton(sf::Mouse::Button button, std::function<void()> function, Mode mode)
{
    auto wrapperFunc = [function]() { function(); };
    _mouseFunctions.try_emplace(button, wrapperFunc);
    MouseMapData data = { false, mode };
    _mouseData.try_emplace(button, data);
    _mouseButtons.push_back(button);
}

void KeyboardManager::RemoveKey(sf::Keyboard::Key key)
{

    _keyData.erase(key);
    _keyFunctions.erase(key);
    _keys.erase(std::remove(_keys.begin(), _keys.end(), key), _keys.end());
}



void KeyboardManager::Update()
{

    for (auto& CurrentKey : _keys)
    {
        if (_keyData[CurrentKey].mode == Mode::Hold)
        {
            if (sf::Keyboard::isKeyPressed(CurrentKey))
            {
                _keyFunctions[CurrentKey]();
            }
        }
        else if (_keyData[CurrentKey].mode == Mode::Press && _keyData[CurrentKey].down == false)
        {
            if (sf::Keyboard::isKeyPressed(CurrentKey))
            {
                _keyFunctions[CurrentKey]();
                _keyData[CurrentKey].down = true;
            }
        }
        else
        {
            _keyData[CurrentKey].down = true;
        }

    }
    for (auto& CurrentMouseKey : _mouseButtons)
    {
        if (_mouseData[CurrentMouseKey].mode == Mode::Hold)
        {
            if (sf::Mouse::isButtonPressed(CurrentMouseKey))
            {
                _mouseFunctions[CurrentMouseKey]();
            }
        }
        else if (_mouseData[CurrentMouseKey].mode == Mode::Press && _mouseData[CurrentMouseKey].down == false)
        {
            if (sf::Mouse::isButtonPressed(CurrentMouseKey))
            {
                _mouseFunctions[CurrentMouseKey]();
                _mouseData[CurrentMouseKey].down = true;
            }
        }
        else
        {
            _mouseData[CurrentMouseKey].down = false;
        }
    }
}
