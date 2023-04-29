# DInputManager
DInputManager is a small header and cpp file lib that is meant to make having keybored inputs easy
# Docs
To get started make a new instance of the KeyboardManager class like 
```cpp
KeyboardManager Keymanager = KeyboardManager()
```   
then register a key/mousebuton with there respective functions. AddKey, AddMouseButton  
```cpp
Keymanager.AddKey('R', [](){std::cout<<"Hello World!\n";}, Press);

Keymanager.AddMouseButton(0, [](){std::cout<<"Hello World!\n";}, Press);
```
This can be done with lambdas as shown above or with functions
```cpp
void Print()
{
  std::cout << "Hello World!\n";
}

void main()
{
  Keymanager.AddKey('R', Print, Press);
  Keymanager.AddMouseButton(0, Print, Press);
}
```
These function pointers that are used above can also take in arguments

```cpp
void Print(std::string S)
{
  std::cout << "Hello World!" + S + "\n";
}

void main()
{
  Keymanager.AddKey('R', Print, Press, "From Key R\n");
  Keymanager.AddMouseButton(0, Print, Press, "From MouseButton 0!\n");
}
```
After you have registered all the functions call the Update method to check for inputs
```cpp
Keymanager.Update();
```
To Remove a keybind call RemoveKey
```cpp
Keymanager.AddKey('X', [](){std::cout << "Hi\n";}, Hold);

Keymanager.RemoveKey('X');
```
# Notes
This lib uses raylib.h as its input tester. IF you do not have raylib you need to 1 hook the lib into your own tester functions
