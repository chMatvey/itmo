#!/usr/bin/env bash

export ORACLE_BASE='/u01/app/oracle'
export ORACLE_HOME='/u01/app/oracle/product/11.2.0/dbhome_1'
export ORACLE_SID='s225141'
export ORADATA='/u01/yak27/oradata'
export NLS_LANG='American_America.UTF8'
export NLS_SORT='AMERICAN'
export NLS_DATE_LANGUAGE='AMERICAN'
export LD_LIBRARY_PATH='$ORACLE_HOME/lib:/lib:/usr/lib:/usr/local/lib'

PATH=$PATH:$ORACLE_HOME/bin

rman @/u01/app/oracle/reprman.rman


