// Copyright 2025 Eric Ottosson (@ericotsn) <contact@ericotsn.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TAPPING_TERM 240
#define FLOW_TAP_TERM 60
#define CHORDAL_HOLD
#define PERMISSIVE_HOLD // Default tap-hold behavior
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define QUICK_TAP_TERM 0 // Disable auto-repeat for tap-hold keys

#define ORBITAL_MOUSE_SPEED_CURVE \
      {24, 24, 24, 32, 62, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72, 72}
//     |               |               |               |           |
// t = 0.000           1.024           2.048           3.072       3.840 s
