#pragma once

class InputManager
{
private:
    enum class KeyType : UINT
    {
        kNone = 0,
        kDown,
        kHold,
        kUp
    };

    struct Key
    {
        KeyType type;
        bool is_down;
    };

    // ΩÃ±€≈Ê
    static std::shared_ptr<InputManager> instance_;
    static std::once_flag flag_;

    std::map<int, Key> keys_;
public:
    InputManager();
    ~InputManager() = default;

    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    static std::shared_ptr<InputManager> GetInstance();

    void Release();
    void Initiate();
    void AddKey(int key);
    void InputUpdate();

    bool GetKeyDown(int key);
    bool GetKey(int key);
    bool GetKeyUp(int key);
};
