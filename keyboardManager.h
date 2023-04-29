#pragma once
#include <functional>
#include <map>
#include <vector>
#include <utility>
#include <functional>
#include <array>

enum Mode
{
    Hold,
    Toggle,
    Press
};

struct KeyMapData
{
    bool down = false;
    Mode mode = Hold;
};

struct MouseMapData
{

    bool down = false;
    Mode mode = Hold;
};

class KeyboardManager 
{
public:
    template <typename... Args>
    void AddKey(int Key, std::function<void(Args...)> Function, Mode mode,Args... args)
    {
        auto WrapperFunc = [Function, args...]() { Function(args...); };
        _keyFunctions.try_emplace(Key, WrapperFunc);
        KeyMapData Data = { false, mode };
        _keyData.try_emplace(Key, Data);
        _keys.push_back(Key);

    }
    void AddKey(int Key, std::function<void()> Function, Mode KeyMode);


    template <typename... Args>
    void AddMouseButton(int Key, std::function<void(Args...)> Function, Mode mode, Args... args)
    {
        auto WrapperFunc = [Function, args...]() { Function(args...); };
        _mouseFunctions.try_emplace(Key, WrapperFunc);
        MouseMapData Data = { false, mode };
        _mouseData.try_emplace(Key, Data);
        _miceButtons.push_back(Key);
    }


    void AddMouseButton(int Key, std::function<void()> Function, Mode KeyMode);


    void RemoveKey(int Key);

    void Update();
private:
    std::map <int, std::function<void()>> _keyFunctions;
    std::map<int, KeyMapData> _keyData;
    std::vector<int> _keys;

    std::map<int, std::function<void()>> _mouseFunctions;
    std::map<int, MouseMapData> _mouseData;
    std::vector<int> _miceButtons;
};

