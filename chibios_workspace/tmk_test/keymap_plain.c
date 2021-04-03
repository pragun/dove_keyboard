/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "config.h"
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"
#include "keymap_common.h"

const uint8_t keymaps[5][25] =
 /* 0: Qwerty
      * ,-----------------------------------------------------------------------------------------------------------------------.
      * |Esc |F12|F11|F10|  ~`| 1|  2|  3|  4|  5|  6|  PrnScn|  Lock | Pause| 7 | 8 | 9 | 0 | - | = |BkSpc| NumLck| / | * | - |
      * |----------------------------------------------------------------------------------------------------------------------|
      * |{}  | F9| F8| F7| Tab   |  Q|  W|  E|  R|  T|  Ins   |  Home | PgUp | Y | U | I | O | P | { |  }  |      7| 8 | 9 | + |
      * |    --------------------------------------------------------------------------------------------------------------|   |
      * |    | F6| F5| F4| {}| {}|  A|  S|  D|  F|  G|  Del   |  End  | PgDn | H | J | K | L | : | " |  \  |      4| 5 | 6 |   |
        |----------------------------------------------------------------------------------------------------------------------|
      * |{}  | F3| F2| F1| Shift |  Z|  X|  C|  V|  B| XXXXXXX|   UP  | XXXXX| N | M | < | > | ? |  Shift  |      1| 2 | 3 |Ret|
      * |    --------------------------------------------------------------------------------------------------------------|   |
      * |    |  O| BckSpc|Ctrl|Win|Fnc|Alt|  Space  |  Left   | Down  | Right| Enter |Alt |Win |Func |Ctrl |      0    | . |   |
      * `----------------------------------------------------------------------------------------------------------------------'
      *                                         |Fn2|                         |Fn2|
      *       `--------------------------------------------------------------------------------------------------------'
      */
     KEYMAP(ESC, F12, F11, F10, GRV, 1,   2,   3,   4,   5,   6,   PSCR, SLCK, BRK, 7, 8 , 9, 0, MINS, EQL, BSPC, NLCK, PSLS, PAST, PMNS,
            PPLS, F9, F8, F7, TAB, Q, W, E, R, T, INS, HOME, PGUP, Y, U, I, O, P, LBRC, RBRC, P7, P8, P9, PPLS,
            F6, F5, F4, NO, NO, A, S, D, F, G, DEL, END, PGDN, H, J, K, L, SCLN, QUOT, BSLS, P4, P5, P6,
            PENT, F3, F2, F1, LSFT, Z, X, C, V, B, UP, N, M, COMM, DOT, SLSH, RSFT, P1, P2, P3, PENT,
            PDOT, NO, LCTL, LGUI, NO, LALT, SPC, LEFT, DOWN, RIGHT, ENT, RALT, RGUI, NO, RCTRL, P0, PDOT,
            NO, NO);

const action_t fn_actions[] = {
};


/* translates key to keycode */
//uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
//{
//    return keymaps[(layer)][(key.row)][(key.col)];
//}

/* translates Fn keycode to action */
//action_t keymap_fn_to_action(uint8_t keycode)
//{
//    return fn_actions[FN_INDEX(keycode)];
//}
