<?php

xspy_init("/usr/local/xunsearch/etc/py.xdb");

$py = xspy_hanzi_to_pinyin("你好", 0, 0);
echo $py . '\r\n';

$py = xspy_hanzi_to_pinyin("你好", 1, 0); // 拼音模糊
echo $py . '\r\n';

$py = xspy_hanzi_to_pinyin("你好", 0, 1); // 拼音首字母缩写
echo $py . '\r\n';

xspy_deinit();

?>
