// ============================================================================
#include "gsm.h"
// #include "mouse.h"
#include "keyboard.h"
// ============================================================================
SoftwareGSM* gsm;
// ============================================================================
USB usb;
// USBHub hub(&usb);
// HIDBoot<USB_HID_PROTOCOL_KEYBOARD | USB_HID_PROTOCOL_MOUSE> hid_composite(&usb);

HIDBoot<USB_HID_PROTOCOL_KEYBOARD> hid_keyboard(&usb);
KeyboardParser keyboard_prs;

// HIDBoot<USB_HID_PROTOCOL_MOUSE> hid_mouse(&usb);
// MouseParser mouse_prs;
// ============================================================================
void setup() {
	Serial.begin(DEFAULT_SERIAL_PORT);  // Скорость порта для связи Arduino с компьютером
	digitalWrite(DEFUALT_POWER_PIN, HIGH);

	gsm = new SoftwareGSM();

	// Mouse.begin();
    Keyboard.begin();

    // while(!Serial);

	if (usb.Init() == -1)
	    Serial.println(F("[ERROR] OSC did not start."));

	// hid_composite.SetReportParser(0, &keyboard_prs);
	// hid_composite.SetReportParser(1, &mouse_prs);
	hid_keyboard.SetReportParser(0, &keyboard_prs);
	// hid_mouse.SetReportParser(0, &mouse_prs);

	Serial.println(F("[GSM] module started."));
	viewFreeMemory();
}
// ============================================================================
void loop() {
	gsm->execute();
	usb.Task();
}
// ============================================================================
