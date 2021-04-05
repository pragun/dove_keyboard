/*
Copyright 2014 Jun Wako <wakojun@gmail.com>

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
#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "action_util.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


//Generating python code
//def p1(j):
//  return ', '.join(['K_%d_%d'%(i,j) for i in reversed(range(0,25))])
//
//def p2(j):
//  return ', '.join(['KC_##K_%d_%d'%(i,j) for i in (range(0,25))])
//
//def k1(r):
//  return ', \ \n'.join([p1(i) for i in range(0,r)])
//
//def k2(r):
//  return ', \ \n'.join([('{'+p2(i)+' }') for i in range(0,r)])
//
//print(k1(5),'\n')
//print(k2(5),'\n')


/* Dove prototype */
#define KEYMAP( \
  K_24_0, K_23_0, K_22_0, K_21_0, K_20_0, K_19_0, K_18_0, K_17_0, K_16_0, K_15_0, K_14_0, K_13_0, K_12_0, K_11_0, K_10_0, K_9_0, K_8_0, K_7_0, K_6_0, K_5_0, K_4_0, K_3_0, K_2_0, K_1_0, K_0_0, \
  K_24_1, K_23_1, K_22_1, K_21_1, K_19_1, K_18_1, K_17_1, K_16_1, K_15_1, K_14_1, K_13_1, K_12_1, K_11_1, K_10_1, K_9_1, K_8_1, K_7_1, K_6_1, K_5_1, K_4_1, K_3_1, K_2_1, K_1_1, K_0_2, \
  K_23_2, K_22_2, K_21_2, K_20_2, K_19_2, K_18_2, K_17_2, K_16_2, K_15_2, K_14_2, K_13_2, K_12_2, K_11_2, K_10_2, K_9_2, K_8_2, K_7_2, K_6_2, K_5_2, K_4_2, K_3_2, K_2_2, K_1_2,  \
  K_24_3, K_23_3, K_22_3, K_21_3, K_19_3, K_17_3, K_16_3, K_15_3, K_20_3, K_14_3, K_12_3, K_10_3, K_9_3, K_8_3, K_7_3, K_6_3, K_5_3, K_3_3, K_2_3, K_1_3, K_0_4, \
  K_23_4, K_21_4, K_20_4, K_18_4, K_17_4,  K_15_4, K_14_4, K_13_4, K_12_4, K_11_4, K_9_4, K_8_4, K_7_4, K_6_4, K_4_4, K_2_4, K_1_4, \
  K_16_4, K_10_4) \
{ \
  {KC_##K_0_0, KC_##K_1_0, KC_##K_2_0, KC_##K_3_0, KC_##K_4_0, KC_##K_5_0, KC_##K_6_0, KC_##K_7_0, KC_##K_8_0, KC_##K_9_0, KC_##K_10_0, KC_##K_11_0, KC_##K_12_0, KC_##K_13_0, KC_##K_14_0, KC_##K_15_0, KC_##K_16_0, KC_##K_17_0, KC_##K_18_0, KC_##K_19_0, KC_##K_20_0, KC_##K_21_0, KC_##K_22_0, KC_##K_23_0, KC_##K_24_0 }, \
  {KC_NO, KC_##K_1_1, KC_##K_2_1, KC_##K_3_1, KC_##K_4_1, KC_##K_5_1, KC_##K_6_1, KC_##K_7_1, KC_##K_8_1, KC_##K_9_1, KC_##K_10_1, KC_##K_11_1, KC_##K_12_1, KC_##K_13_1, KC_##K_14_1, KC_##K_15_1, KC_##K_16_1, KC_##K_17_1, KC_##K_18_1, KC_##K_19_1, KC_NO, KC_##K_21_1, KC_##K_22_1, KC_##K_23_1, KC_##K_24_1 }, \
  {KC_##K_0_2, KC_##K_1_2, KC_##K_2_2, KC_##K_3_2, KC_##K_4_2, KC_##K_5_2, KC_##K_6_2, KC_##K_7_2, KC_##K_8_2, KC_##K_9_2, KC_##K_10_2, KC_##K_11_2, KC_##K_12_2, KC_##K_13_2, KC_##K_14_2, KC_##K_15_2, KC_##K_16_2, KC_##K_17_2, KC_##K_18_2, KC_##K_19_2, KC_##K_20_2, KC_##K_21_2, KC_##K_22_2, KC_##K_23_2, KC_NO }, \
  {KC_NO, KC_##K_1_3, KC_##K_2_3, KC_##K_3_3, KC_NO, KC_##K_5_3, KC_##K_6_3, KC_##K_7_3, KC_##K_8_3, KC_##K_9_3, KC_##K_10_3, KC_NO, KC_##K_12_3, KC_NO, KC_##K_14_3, KC_##K_15_3, KC_##K_16_3, KC_##K_17_3, KC_NO, KC_##K_19_3, KC_##K_20_3,  KC_##K_21_3, KC_##K_22_3, KC_##K_23_3, KC_##K_24_3 }, \
  {KC_##K_0_4, KC_##K_1_4, KC_##K_2_4, KC_NO, KC_##K_4_4, KC_NO, KC_##K_6_4, KC_##K_7_4, KC_##K_8_4, KC_##K_9_4, KC_##K_10_4, KC_##K_11_4, KC_##K_12_4, KC_##K_13_4, KC_##K_14_4, KC_##K_15_4, KC_##K_16_4, KC_##K_17_4, KC_##K_18_4,  KC_NO, KC_##K_20_4, KC_##K_21_4, KC_NO, KC_##K_23_4, KC_NO }  \
}

#else

#endif

