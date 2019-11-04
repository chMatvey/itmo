export ORACLE_BASE=/u01/app/oracle
export ORACLE_HOME=/u01/app/oracle/product/11.2.0/dbhome_1
export ORACLE_SID=s225141
export ORADATA=/u01/yak27/oradata
export NLS_LANG=American_America.UTF8
export NLS_SORT=AMERICAN
export NLS_DATE_LANGUAGE=AMERICAN
PATH=$PATH:$ORACLE_HOME/bin

cd $ORACLE_HOME/dbs
orapwd file=orapws225141

cd $ORACLE_BASE
mkdir -p admin/orcl/adump
mkdir flash_recovery_area
mkdir -p /u01/yak27
mkdir -p /u01/yak27/oracle/product/11.2.0/dbhome_1
mkdir -p /u01/yak27/oradata/bestmeat
mkdir -p /u01/yak27/oradata/node01
mkdir -p /u01/yak27/oradata/node02
mkdir -p /u01/yak27/oradata/node03
mkdir -p /u01/yak27/oradata/node04
export ORADATA=/u01/yak27/oradata

cd $ORACLE_HOME/dbs
touch inits225141.ora

cd $ORACLE_HOME/network/admin
touch listener.ora
touch sqlnet.ora
touch tnsnames.ora