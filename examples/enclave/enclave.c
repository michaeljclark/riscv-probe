#include "femto.h"

/*
 * Simple enclave example using RISC-V PMP (Physical Memory Protection)
 *
 * NOTE: Physical memory protection is enabled for the program text (RX)
 *       program data (RW), UART, and the hart is switch to U mode, however,
 *       there is only one program and the default trap vector points into
 *       the executable text, so traps are handled in M mode, in the same
 *       executable text segment. A more complete example needs to load a
 *       second process and provide ecall APIs to the protected enclave.
 */

extern char _text_start;
extern char _rodata_end;
extern char _data_start;
extern char _bss_end;

static uintptr_t uart_keys[] = {
	SIFIVE_UART0_CTRL_ADDR,
	NS16550A_UART0_CTRL_ADDR,
	0
};

int main()
{
	uintptr_t uart = 0;
	uintptr_t *uart_k = uart_keys;
	const uintptr_t uartlen = 32;

	/* locate UART address using known configuration keys */
	while (*uart_k) {
		if (uart = getauxval(*uart_k)) {
			break;
		}
	}

	/* locate ROM/Flash (text+rodata) and RAM (data+bss) */
	uintptr_t rx_s = (uintptr_t)&_text_start;
	uintptr_t rx_l = roundpow2((uintptr_t)(&_rodata_end - &_text_start));
	uintptr_t rw_s = (uintptr_t)&_data_start;
	uintptr_t rw_l = roundpow2((uintptr_t)(&_bss_end - &_data_start));

	/* print our findings */
	printf("text: 0x%x - 0x%x\n", rx_s, rx_s + rx_l - 1);
	printf("data: 0x%x - 0x%x\n", rw_s, rw_s + rw_l - 1);
	if (uart) {
		printf("uart: 0x%x - 0x%x\n", uart, uart + uartlen - 1);
	}

	/* set up physical memory protection */
	pmp_entry_set(0, PMP_R | PMP_X, rx_s, rx_l);
	pmp_entry_set(1, PMP_R | PMP_W, rw_s, rw_l);
	if (uart) {
		pmp_entry_set(2, PMP_R | PMP_W, uart, uartlen);
	}

	/* switch to user mode enclave */
	set_mode_and_continue(PRV_U);
	puts("enclave");
}
