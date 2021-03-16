#!/bin/bash
if [ "" == "$1" ];
then
  mode=gbb
elif [ "GBB" == $1 ] || [ "gbb" == $1 ];
then
  mode=gbb
elif [ "ESNA" == $1 ] || [ "esna" == $1 ];
then
  mode=esna
else
  echo unknown mode $1
  exit -1
fi
rcfile=canpush-$mode.rc
echo $rcfile
cp $rcfile /etc/init.d/canpush
ln -s /etc/init.d/canpush /etc/rc1.d/S99canpush
ln -s /etc/init.d/canpush /etc/rc2.d/S99canpush
ln -s /etc/init.d/canpush /etc/rc3.d/S99canpush
ln -s /etc/init.d/canpush /etc/rc4.d/S99canpush
ln -s /etc/init.d/canpush /etc/rc5.d/K99canpush
ln -s /etc/init.d/canpush /etc/rc6.d/K99canpush
echo Installing canpush in $mode mode
timedatectl set-ntp false
