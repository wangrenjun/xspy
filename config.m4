
PHP_ARG_ENABLE(xspy, whether to enable xspy support,
[  --enable-xspy           Enable xspy support])

PHP_ARG_WITH(scws-dir, for scws support,
[  --with-scws-dir[=DIR]        Set the path to scws install prefix.], yes)

if test "$PHP_XSPY" != "no"; then
	if test "$PHP_SCWS_DIR" != "no" && test "$PHP_SCWS_DIR" != "yes"; then
		if test -r "$PHP_SCWS_DIR/include/scws/scws.h"; then
			PHP_SCWS_INCDIR="$PHP_SCWS_DIR/include/"
			PHP_SCWS_LIBDIR="$PHP_SCWS_DIR/lib/"
		else
			AC_MSG_ERROR([pinyin support requires scws. Use --with-scws-dir=<DIR> to specify the prefix where scws headers and library are located])
		fi
	else
		AC_MSG_ERROR([pinyin support requires scws. Use --with-scws-dir=<DIR> to specify the prefix where scws headers and library are located])
	fi

	PHP_ADD_INCLUDE($PHP_SCWS_INCDIR)
	PHP_ADD_LIBRARY_WITH_PATH(scws, $PHP_SCWS_LIBDIR, XSPY_SHARED_LIBADD)
	PHP_SUBST(XSPY_SHARED_LIBADD)

	PHP_NEW_EXTENSION(xspy, pinyin.c xspyimpl.c xspy.c, $ext_shared)
fi
