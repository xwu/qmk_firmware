# Drop CTRL — xwu

This customized keymap is designed to work with [SmartEEPROM–enabled][pr] firmware and makes a small number of customizations for ease of use, including on macOS. It uses [QMK RGB][rgb] lighting and matrix features rather than Drop/Massdrop's own implementation.

## Typing layer

### Media keys

**F9**–**F12** are replaced with **Play/Pause**, **Mute**, **Volume Down**, and **Volume Up** (in that order).

> **Previous Track** and **Next Track** keys are omitted in part because many keycap sets don't include them.

### Modifiers

On the right, **Menu** is replaced by **OS** (e.g., **Cmd** or **Windows**) and swapped in position with **Fn**. By default, **Alt (Option)** and **OS** are swapped for a macOS layout, but this setting can be toggled (see below).

> Many Microsoft keyboards now include a **Windows** key on both sides of the space bar, and there is precedent in omitting the **Menu** key in favor of the **Fn** key with Logitech keyboards. Swapping the **Alt (Option)** and **OS** keys then produces a layout similar to that of many Keychron keyboards.

## Function layer

In the function layer, keys are added to reset the SmartEEPROM and to toggle swapping **Alt (Option)** and **OS**, and LED customization keys are moved to the right side and rationalized.

### Function keys

**F9**–**F12** are accessed in the function layer by **Fn** + the corresponding media key.

### Keyboard configuration keys

Unchanged from stock, **Fn** + **B** (press and hold) restarts into the Massdrop <u>B</u>ootloader, and **Fn** + **N** toggles between 6-key rollover (6KRO) and full <u>N</u>-key rollover (NKRO).

**Fn** + **M** resets the SmartEEPRO<u>M</u>.

**Fn** + **OS** or, once swapped, **Fn** + **Alt (Option)** toggles swapping **Alt (Option)** and **OS**.

### LED configuration keys

**Fn** + **Pause/Break** toggles LED mode (keys and underglow, keys only, underglow only, or none).

**Fn** + **Insert** and **Fn** + **Delete** increase and decrease LED hue, respectively.  
**Fn** + **Home** and **Fn** + **End** increase and decrease LED saturation, respectively.  
**Fn** + **Page Up** and **Fn** + **Page Down** increase and decrease LED brightness (value), respectively.

**Fn** + **&uarr;** and **Fn** + **&darr;** increase and decrease LED pattern speed, respectively.  
**Fn** + **&larr;** selects the previous LED pattern, and **Fn** + **&rarr;** selects the next LED pattern.

[pr]: https://github.com/Massdrop/mdloader/pull/16#issuecomment-731976189

[rgb]: https://beta.docs.qmk.fm/using-qmk/hardware-features/lighting/feature_rgblight
