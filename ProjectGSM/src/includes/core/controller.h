// ============================================================================
#ifndef CONTROLLER_H
#define CONTROLLER_H
// ============================================================================
#include "./includes/traffic/traffic.h"
// ============================================================================
class ModulesControl {
public:
    static void sms_analyze(
        SoftwareGSM* gsm_module,
	    KeyboardParser* keyboard_prs,
	    buffer* serial_buf
    );
    static void execute(SoftwareGSM* gsm_module, KeyboardParser* keyboard_prs);
};
// ============================================================================
#endif /* CONTROLLER_H */
// ============================================================================
