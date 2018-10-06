# Hardware Abstraction Layer {#hal}

HAL provides unified API to different hardware via 
* specific low-level drivers for every computer module type, or 
* host OS API wrappers for emulated mode.

In result, even if you have some hardware-specific code, most of them still
can be run portable between many platforms.

**HAL must stay a thin layer**, else you will get not a little fun hardware console, but yet another Linux.

