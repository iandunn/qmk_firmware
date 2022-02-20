# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file

LTO_ENABLE = yes
#CONSOLE_ENABLE = no
CONSOLE_ENABLE = yes


COMMAND_ENABLE = no
WEBUSB_ENABLE = yes
RGBLIGHT_ENABLE = no

SRC += ../../../users/callum/oneshot.c
