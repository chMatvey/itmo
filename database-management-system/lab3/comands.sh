#!/usr/bin/env bash

scp -r /u01/yak27 oracle@db197:/u01/yak27
scp -r /u01/app/oracle/product/11.2.0/dbhome_1/dbs/inits225141.ora oracle@db197:/u01/app/oracle/product/11.2.0/dbhome_1/dbs/inits225141.ora
//scp -r /u01/app/oracle/admin/orcl/adump oracle@db197:/u01/app/oracle/admin/orcl/adump
scp -r /u01/app/oracle/flash_recovery_area oracle@db197:/u01/app/oracle/flash_recovery_area
scp /u01/app/oracle/product/11.2.0/dbhome_1/dbs/inits225141.ora oracle@db197:/u01/app/oracle/product/11.2.0/dbhome_1/dbs/inits225141.ora
scp /u01/init.sh oracle@db197:/u01/init.sh
