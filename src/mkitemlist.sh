#!/bin/bash

#this one gets the item id #s too
# cat ffxiah_items.xml |perl -n -e "if(/(int_id|en_name)/) { print $1 }"|sed -e 's/^[	]*//g;s/<[^>]*>//g'|sed 'N;s/\n/        /'|awk '{ if($2 && $2 != ".") { print $0 }}'
#this one just does item names
cat ffxiah_items.xml |perl -n -e "if(/(en_name)/) { print $1 }"|sed -e 's/^[	]*//g;s/<[^>]*>//g'|awk '{ if($2 && $2 != ".") { print $0 }}'
