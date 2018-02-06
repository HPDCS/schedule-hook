ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I$(abs_top_srcdir)
EXTRA_DIST = COPYING INSTALL README module/Makefile module/hook.c module/hook.h

udevdir = /etc/udev/rules.d
initdir = @sysconfdir@/init.d

module/switch-hook.ko: module/hook.c
	test -f $(builddir)/module/Makefile || $(LN_S) $(abs_top_srcdir)/module/Makefile $(builddir)/module/
	test -f $(builddir)/module/hook.c || $(LN_S) $(abs_top_srcdir)/module/hook.c $(builddir)/module/
	test -f $(builddir)/module/hook.h || $(LN_S) $(abs_top_srcdir)/module/hook.h $(builddir)/module/
	$(MAKE) -C $(KERNEL_SRC) M=$(abs_top_builddir)/module EXTRA_CFLAGS="-Wall"

all-local: module/switch-hook.ko

install-exec-hook: module/switch-hook.ko
	test -z "$(DESTDIR)$(KERNEL_MOD)" || $(MKDIR_P) "$(DESTDIR)$(KERNEL_MOD)"
	$(INSTALL) $(builddir)/module/switch-hook.ko $(DESTDIR)$(KERNEL_MOD)/switch-hook.ko
	depmod -a

uninstall-hook:
	$(RM) $(DESTDIR)$(KERNEL_MOD)/switch-hook.ko
	depmod -a

clean-local:
	-$(MAKE) -C $(KERNEL_SRC) M=$(abs_top_builddir)/module clean