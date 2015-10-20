AC_PREREQ([2.63])
AC_INIT([timestretch], [1.0.0], [quaglia@dis.uniroma1.it,pellegrini@dis.uniroma1.it])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_MACRO_DIR([m4])

# Preliminary check: are we on Linux?
AC_CANONICAL_HOST
AC_MSG_CHECKING([for supported host Operating System])
case $host_os in
  linux*)
        # Do something specific for linux
        AC_MSG_RESULT([yes, ${host_os}])
        ;;
    *)
        #Default Case
        AC_MSG_RESULT([no, ${host_os}])
        AC_MSG_ERROR([This module runs only on Linux])
        ;;
esac

# Preliminary check: are we on x86?
AC_MSG_CHECKING([for a supported CPU architecture])
case "${host_cpu}" in

     x86_64)
        AC_MSG_RESULT([yes, ${host_cpu}])
        ;;

     *)
       AC_MSG_RESULT([no, ${host_cpu}])
       AC_MSG_ERROR([Unsupported host architecture. Currently ROOT-Sim supports only x86_64 systems.])
       ;;
esac




# Configure kernel module paths
AC_SUBST([with_kernel], [`uname -r`])
AC_SUBST([with_kernel_mod], [/lib/modules/$with_kernel/extra])
AC_SUBST([KERNEL_SRC], [/lib/modules/$with_kernel/build])
AC_SUBST([KERNEL_MOD], [$with_kernel_mod])

# Checks for programs.
AC_LANG([C])
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MKDIR_P
AC_PROG_LN_S
AC_PROG_GREP
AC_PROG_SED
AC_PROG_RANLIB
AC_PATH_PROG(RM, rm, /bin/rm, $PATH:/bin:/usr/bin:/usr/local/bin)



# Get finish_task_switch in the current kernel
AC_MSG_CHECKING([for finish_task_switch in the current kernel])
fts_line=$($GREP -n finish_task_switch /boot/System.map-$(uname -r) | $SED 's/:.*//')
finish_task_switch=$($SED "${fts_line}q;d" /boot/System.map-$(uname -r) | $SED 's/ .*//')
if test -z "$finish_task_switch"; then
        AC_MSG_ERROR([Address of finish_task_switch not found in kernel map])
fi
AC_MSG_RESULT([found at 0x$finish_task_switch])
AC_SUBST([FTS_ADDR], [0x$finish_task_switch])

# Get function after finish_task_switch in the current kernel
AC_MSG_CHECKING([the address of function next to finish_task_switch in the current kernel])
let fts_line=$fts_line+1
finish_task_switch_next=$($SED "${fts_line}q;d" /boot/System.map-$(uname -r) | $SED 's/ .*//')
if test -z "$finish_task_switch_next"; then
        AC_MSG_ERROR([Address of function aftr finish_task_switch not found in kernel map])
fi
AC_MSG_RESULT([found at 0x$finish_task_switch_next])
AC_SUBST([FTS_ADDR_NEXT], [0x$finish_task_switch_next])


# Are kernel headers installed?
AC_CHECK_HEADERS([linux/ioctl.h],,
       [AC_MSG_ERROR([You must install kernel-headers])])

# Final output
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
