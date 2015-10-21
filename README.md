# schedule-hook
A kernel module that dynamically patches the Linux kernel scheduler so as to allow running a custom function upon thread reschedule
This is the schedule-hook kernel module, to allow running a custom function
e.g. in another module, upon thread reschedule

This module can be used either in cross compilation with the one containing 
the custom function or not 

This module patches at run-time the kernel schedule() and enables running a schedule-hook
function as the last task of thread re-schedule 

The schdule-hook function is embedded within this module, it checks the value of a function pointer
and in case it is not null the target functio is called

In cross compilation the function pointer is exported as a symbol to be updated while mounting 
the module containing the custom functions to be run

Otherwise, the function ponter is accessible as a pseudofile called 
/sys/module/schedule_hook/parameters/the_hook  

In the latter configuraiton, after mounting the module, you can load any function pointer 
you would like (pointing to kernel stuff) by writing it on that pseudofile

The custom function to be run needs to get no paramter in input

Please check with the follosing configuration macros to manage the configuration of this module:
- DEBUG and DEBUG_SCHEDULE_HOOK for enalbing or disabling debugging/audit stuff
- SYS_FS for enabling of disabling the reliance on /sys

NOTE: the custom function is expected to be non-blocking, 
in case it is blocking the unmount of this module may hang

NOTE: this module shoudl be unmounted before unmounting the one containing the custom function
otherwise your kernel wil likely crash

The code has been developed by:
- Francesco Quaglia <quaglia@dis.uniroma1.it>
- Alessandro Pellegrini <pellegrini@dis.uniroma1.it>

and is Copyright (C) 2015 HPDCS Group, http://www.dis.uniroma1.it/~hpdcs

For installation and usage information, please refer to INSTALL.

