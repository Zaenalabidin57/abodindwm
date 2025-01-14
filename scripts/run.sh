#!/bin/sh

xrdb merge ~/.Xresources 
xbacklight -set 10 &
xrandr --output HDMI-1 --left-of eDP-1
nitrogen --restore
#feh --bg-fill ~/Pictures/wollpeper/chne.jpeg &
#feh --bg-fill ~/Pictures/wollpeper/chieh.jpg &
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
xset r rate 200 50 &
dunst &
picom &
clipcatd

dash ~/shigure/abodindwm/scripts/bar.sh &
while type chadwm >/dev/null; do chadwm && continue || break; done
