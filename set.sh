for X in $(seq 0 7); do for Y in $(seq 0 2); do echo 1 > /sys/devices/system/cpu/cpu$X/cpuidle/state$Y/disable ; done ; done
