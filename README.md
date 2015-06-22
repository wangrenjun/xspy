#xspy

将Xunsearch的拼音库提取出封装成PHP扩展，使用so easy。

##Example:
	<?php
	xspy_init("/usr/local/xunsearch/etc/py.xdb");
	$py = xspy_hanzi_to_pinyin("你好世界", 0, 0);
	echo $py . "\r\n";
	$py = xspy_hanzi_to_pinyin("你好世界", 1, 0); // 拼音模糊
	echo $py . "\r\n";
	$py = xspy_hanzi_to_pinyin("你好世界", 0, 1); // 拼音首字母缩写
	echo $py . "\r\n";
	$py = xspy_hanzi_to_pinyin("你好世界", 1, 1);
	echo $py . "\r\n";
	xspy_deinit();
	?>

##安装：
	phpize
	./configure --with-scws-dir=<Xunsearch安装路径，如：/usr/local/xunsearch/>
	make
	make install
		
	echo "[xspy]
	extension = xspy.so" >> php.ini
