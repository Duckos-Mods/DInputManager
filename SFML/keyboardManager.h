#pragma once
#include <functional>
#include <map>
#include <vector>
#include <utility>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

enum class Mode
{
    Hold,
    Toggle,
    Press
};

struct KeyMapData
{
    bool down = false;
    Mode mode = Mode::Hold;
};

struct MouseMapData
{
    bool down = false;
    Mode mode = Mode::Hold;
};

class KeyboardManager
{
public:
    template <typename... Args>
    void AddKey(sf::Keyboard::Key key, std::function<void(Args...)> function, Mode mode, Args... args)
    {
        auto wrapperFunc = [function, args...]() { function(args...); };
        _keyFunctions.try_emplace(key, wrapperFunc);
        KeyMapData data = { false, mode };
        _keyData.try_emplace(key, data);
        _keys.push_back(key);
    }

    void AddKey(sf::Keyboard::Key key, std::function<void()> function, Mode mode);

    template <typename... Args>
    void AddMouseButton(sf::Mouse::Button button, std::function<void(Args...)> function, Mode mode, Args... args)
    {
        auto wrapperFunc = [function, args...]() { function(args...); };
        _mouseFunctions.try_emplace(button, wrapperFunc);
        MouseMapData data = { false, mode };
        _mouseData.try_emplace(button, data);
        _mouseButtons.push_back(button);
    }

    void AddMouseButton(sf::Mouse::Button button, std::function<void()> function, Mode mode);

    void RemoveKey(sf::Keyboard::Key key);

    void Update();

private:
    std::map<sf::Keyboard::Key, std::function<void()>> _keyFunctions;
    std::map<sf::Keyboard::Key, KeyMapData> _keyData;
    std::vector<sf::Keyboard::Key> _keys;

    std::map<sf::Mouse::Button, std::function<void()>> _mouseFunctions;
    std::map<sf::Mouse::Button, MouseMapData> _mouseData;
    std::vector<sf::Mouse::Button> _mouseButtons;



};
