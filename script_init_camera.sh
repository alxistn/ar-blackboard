v4l2-ctl -d/dev/video1 --set-ctrl=brightness=128 # (int)    : min=0 max=255 step=1 default=128 value=128
v4l2-ctl -d/dev/video1 --set-ctrl=contrast=32 # (int)    : min=0 max=255 step=1 default=32 value=32
v4l2-ctl -d/dev/video1 --set-ctrl=saturation=32 # (int)    : min=0 max=255 step=1 default=32 value=32
v4l2-ctl -d/dev/video1 --set-ctrl=white_balance_temperature_auto=0 # (bool)   : default=1 value=1
v4l2-ctl -d/dev/video1 --set-ctrl=gain=64 # (int)    : min=0 max=255 step=1 default=64 value=64
v4l2-ctl -d/dev/video1 --set-ctrl=power_line_frequency=2 # (menu)   : min=0 max=2 default=2 value=2
v4l2-ctl -d/dev/video1 --set-ctrl=white_balance_temperature=2800 # (int)    : min=2800 max=6500 step=1 default=4000 value=5616 flags=inactive
v4l2-ctl -d/dev/video1 --set-ctrl=sharpness=72 # (int)    : min=0 max=255 step=1 default=72 value=72
v4l2-ctl -d/dev/video1 --set-ctrl=backlight_compensation=0 # (int)    : min=0 max=1 step=1 default=0 value=0
v4l2-ctl -d/dev/video1 --set-ctrl=exposure_auto=1 # (menu)   : min=0 max=3 default=3 value=3
v4l2-ctl -d/dev/video1 --set-ctrl=exposure_absolute=20 # (int)    : min=3 max=2047 step=1 default=166 value=166 flags=inactive
v4l2-ctl -d/dev/video1 --set-ctrl=exposure_auto_priority=0 # (bool)   : default=0 value=1
v4l2-ctl -d/dev/video1 --set-ctrl=pan_absolute=0 # (int)    : min=-36000 max=36000 step=3600 default=0 value=0
v4l2-ctl -d/dev/video1 --set-ctrl=tilt_absolute=0 # (int)    : min=-36000 max=36000 step=3600 default=0 value=0
v4l2-ctl -d/dev/video1 --set-ctrl=focus_absolute=68 # (int)    : min=0 max=255 step=17 default=68 value=102 flags=inactive
v4l2-ctl -d/dev/video1 --set-ctrl=focus_auto=0 # (bool)   : default=1 value=1
v4l2-ctl -d/dev/video1 --set-ctrl=zoom_absolute=1 # (int) : min=1 max=5 step=1 default=1 value=1
