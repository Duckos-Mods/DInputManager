# DInputManager
DInputManager is a small header and cpp file lib that is meant to make having keybored inputs easy
# Docs
To get started make a new instance of the KeyboardManager class like 
```cpp
KeyboardManager Keymanager = KeyboardManager()
```   
then register a key/mousebuton with there respective functions. AddKey, AddMouseButton  
```cpp
KeyboardManager.AddKey('R', [](){std::cout<<"Hello World!\n";}, Press);

KeyboardManager.AddMouseButton(0, [](){std::cout<<"Hello World!\n";}, Press);
```
This can be done with lambdas as shown above or with functions
```cpp
void Print()
{
  std::cout << "Hello World!\n";
}

void main()
{
  KeyboardManager.AddKey('R', Print, Press);
  KeyboardManager.AddMouseButton(0, Print, Press);
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
  KeyboardManager.AddKey('R', Print, Press, "From Key R\n");
  KeyboardManager.AddMouseButton(0, Print, Press, "From MouseButton 0!\n");
}
```
