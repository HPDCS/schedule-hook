ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS = -I$(abs_top_srcdir)
EXTRA_DIST = COPYING INSTALL README \
	     module/Makefile module/schedule-hook.c module/schedule-hook.h module/83-schedule-hook.rules 

udevdir = /etc/udev/rules.d
initdir = @sysconfdir@/init.d

#udev_DATA = module/83-schedule-hook.rules

#lib_LIBRARIES = libovertick.a
#libovertick_a_SOURCES=lib/overticklib.c

#include_HEADERS = lib/overtick.h

module/schedule.ko: module/schedule-hook.c module/hook.S
	test -f $(builddir)/module/Makefile || $(LN_S) $(abs_top_srcdir)/module/Makefile $(builddir)/module/
	test -f $(builddir)/module/schedule-hook.c || $(LN_S) $(abs_top_srcdir)/module/schedule-hook.c $(builddir)/module/
	test -f $(builddir)/module/schedule-hook.h || $(LN_S) $(abs_top_srcdir)/module/schedule-hook.h $(builddir)/module/
	$(MAKE) -C $(KERNEL_SRC) M=$(abs_top_builddir)/module EXTRA_CFLAGS="-Wall \
									    -DFTS_ADDR=$(FTS_ADDR) -DFTS_ADDR_NEXT=$(FTS_ADDR_NEXT)"

all-local: module/schedule.ko

install-exec-hook: module/schedule.ko
	test -z "$(DESTDIR)$(KERNEL_MOD)" || $(MKDIR_P) "$(DESTDIR)$(KERNEL_MOD)"
	$(INSTALL) $(builddir)/module/schedule.ko $(DESTDIR)$(KERNEL_MOD)/schedule.ko
	depmod -a

uninstall-hook:
	$(RM) $(DESTDIR)$(KERNEL_MOD)/schedule.ko
	depmod -a

clean-local:
	-$(MAKE) -C $(KERNEL_SRC) M=$(abs_top_builddir)/module clean

