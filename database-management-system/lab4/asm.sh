#!/bin/bash

export ORACLE_BASE="/u01/app/oracle"
export ORACLE_HOME="/u01/app/11.2.0/grid"
export ORACLE_SID="+ASM.225141"
export NLS_LANG="AMERICAN_AMERICA.UTF8"
export PATH=$PATH:$ORACLE_HOME/bin

srvctl stop asm;
crsctl stat resource ora.cssd;