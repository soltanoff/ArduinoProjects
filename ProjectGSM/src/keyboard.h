/* ========================================================================= */
#ifndef KEYBOARD_H
#define KEYBOARD_H
/* ========================================================================= */
#include <Keyboard.h>
#include <hidboot.h>
#include <usbhub.h>
/* ========================================================================= */
class KeyboardParser : public KeyboardReportParser
{
private:
    void PrintKey(uint8_t mod, uint8_t key);
protected:
    void OnControlKeysChanged(uint8_t before, uint8_t after);
    void OnKeyDown(uint8_t mod, uint8_t key);
    void OnKeyUp(uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};
/* ========================================================================= */
#endif /* KEYBOARD_H */
/* ========================================================================= */
