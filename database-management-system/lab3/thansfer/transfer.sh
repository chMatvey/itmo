scp /u01/init.sh oracle@db197:/u01/init.sh

scp /u01/yak27/bestmeat/ctrl.ctl oracle@db197:/u01/app/oracle/product/11.2.0/dbhome_1/dbs

scp /u01/yak27/oradata/bestmeat/temp01.dbf oracle@db197:/u01/yak27/oradata/bestmeat
scp /u01/yak27/oradata/bestmeat/undotbs01.dbf oracle@db197:/u01/yak27/oradata/bestmeat
scp /u01/yak27/oradata/node01/* oracle@db197:/u01/yak27/oradata/node01
scp /u01/yak27/oradata/node02/* oracle@db197:/u01/yak27/oradata/node02
scp /u01/yak27/oradata/node03/* oracle@db197:/u01/yak27/oradata/node03
scp /u01/yak27/oradata/node04/* oracle@db197:/u01/yak27/oradata/node04

scp /u01/yak27/logs/* oracle@db197:/u01/yak27/logs
scp oracle@db146:/u01/yak27/logs/* /u01/yak27/logs

rm -rf oracle@db146:/u01/yak27/backup/rman/*
scp /u01/yak27/backup/rman/* oracle@db146:/u01/yak27/backup/rman