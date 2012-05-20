#!/bin/bash

# cat ffxiah_items.xml |grep en_name|sed -e "s/<[^>]*>//g;s/	//g" |uniq -u |sort | awk '{ if ($0 && $0 != ".") { print $0 }}'
#I dumped the XML into a local MySQL database to make it even simpler and more
#accurate
mysql -u root -h localhost -proot ff11 -e '
SELECT
	en_name
FROM items
WHERE TYPE IN (4, 5)
	AND en_name is NOT NULL
	AND `en_name` <> "."
ORDER BY en_name ASC 
' | sed -e '1d'
