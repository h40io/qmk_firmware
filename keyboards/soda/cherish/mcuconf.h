/* Copyright 2020 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#pragma once

<<<<<<<< HEAD:keyboards/soda/cherish/mcuconf.h
#include_next <mcuconf.h>

#undef STM32_I2C_USE_DMA
#define STM32_I2C_USE_DMA FALSE

========
// Enable RGB Matrix
#define VIA_QMK_RGBLIGHT_ENABLE
>>>>>>>> f3162304dd (Merge branch 'master' of https://github.com/mechlovin/qmk_firmware):keyboards/xelus/la_plus/keymaps/via/config.h
