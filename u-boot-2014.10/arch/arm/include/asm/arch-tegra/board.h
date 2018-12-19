/*
 *  (C) Copyright 2010,2011
 *  NVIDIA Corporation <www.nvidia.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _TEGRA_BOARD_H_
#define _TEGRA_BOARD_H_

/* Set up pinmux to make UART usable */
void gpio_early_init_uart(void);

/* Set up early UART output */
void board_init_uart_f(void);

/* Set up any early GPIOs the board might need for proper operation */
void gpio_early_init(void);  /* overrideable GPIO config        */

/*
 * Hooks to allow boards to set up the pinmux for a specific function.
 * Has to be implemented in the board files as we don't yet support pinmux
 * setup from FTD. If a board file does not implement one of those functions
 * an empty stub function will be called.
 */

void pinmux_init(void);      /* overrideable general pinmux setup */
void pin_mux_usb(void);      /* overrideable USB pinmux setup     */
void pin_mux_spi(void);      /* overrideable SPI pinmux setup     */
void pin_mux_nand(void);     /* overrideable NAND pinmux setup    */
void pin_mux_display(void);  /* overrideable DISPLAY pinmux setup */

#endif
