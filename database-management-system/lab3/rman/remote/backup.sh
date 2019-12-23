. ./init.sh

ssh oracle@db146 'rm @/u01/yak27/backup/rman/*'
rm /u01/yak27/backup/rman/*
rman @/u01/backup.rman
scp /u01/yak27/backup/rman/* oracle@db146:/u01/yak27/backup/rman