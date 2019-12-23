. ./init.sh
scp oracle@db146:/u01/yak27/logs/* /u01/yak27/logs
sqlplus / as sysdba @/u01/recover.sql
