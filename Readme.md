## Firmware for the Dove Mechanical Keyboard
It uses TMK for the keyboard & USB HID, and ChibiOS as the HAL for STM32F407. 
This project uses a slightly different organization as described in the [tmk documentation](https://github.com/tmk/tmk_core/blob/master/README.md). The differences are 
1. It uses a Makefile derived from a ChibiOs example rather than the one used in `tmk/tmk_core/tool/chibios.mk`,
2. It is based on a ChibiOS demo, so it can be used from within ChibiStudio for debugging.

Incase you're interested in building (or tinkering with) the Dove Keyboard, you can find the CAD model in the [dove_keyboard_hw](https://github.com/pragun/dove_keyboard_hw) repo.

## Steps to build, flash & debug.
1. Download and install [ChibiStudio](https://www.chibios.org/dokuwiki/doku.php?id=chibios:products:chibistudio:start)
2. Create a folder that will serve as the workspace for Chibios studio. Lets assume this is is `dove_keyboard_wspace`
3. Clone ChibiOS git repo, and checkout the `stable_20.3` branch.
```
git clone https://github.com/ChibiOS/ChibiOS
cd ChibiOS
git checkout --track origin/stable_20.3
```
4. Clone this repo in the `dove_keyboard_wspace`.
5. Your `dove_keyboard_wspace` folder should now have two folders in it
```
ChibiOS -- checked out to branch 20.3
dove_keyboard_fw
```
6. Run ChibiStudio (making sure to select gcc90 launcher)
7. Open the workspace `dove_keyboard_wspace` as a workspace within ChibiStudio
8. Import ChibiOs as an 'existing project' by selecting File > Import > Existing Projects into Workspace. I recommend unchecking 'Search for nested projects' to avoid littering your workspace with all the demo projects that ChibiOS comes with.
9. Import `dove_keyboard_fw` as an existing project using the same steps as above.
10. You can build, debug, flash, etc on your STM32F407 board as described in this excellent tutorial on [Using ChibiStudio at playembeddded](https://www.playembedded.org/blog/debugging-stm32-chibistudio/)
