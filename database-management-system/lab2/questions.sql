column name format a30

show parameters bd_name

select name, (bytes / 1024 / 1024) as mb from V$SGAINFO where name='Granule Size';

--кодировка
select userenv('language') from dual;
--язык
select userenv('LANG') from dual;

select tablespace_name from DBA_TABLESPACES;
select FILE_NAME from DBA_DATA_FILES where TABLESPACE_NAME='COOL_GOLD_DISK';

select TABLE_NAME from DICT where TABLE_NAME like '%FILES%';

--database name
select name from v$database;
select ora_database_name from dual;

--sid
select instance from v$thread;
select sys_context('userenv','instance_name') from dual;

select userenv('LANG') from dual;

--parameters bd
SELECT a.name, a.value FROM v$parameter a ORDER BY a.name;

--audit
select USERNAME, ACTION_NAME from DBA_AUDIT_TRAIL;
select USERID, COMMENT$TEXT from SYS.AUD$;

--control files
SELECT NAME FROM V$CONTROLFILE;

--redo lof files
SELECT MEMBER FROM V$LOGFILE;

--recovery files
SELECT NAME FROM V$RECOVERY_FILE_DEST;

--processes
select PNAME from V$PROCESS;

--spfile
select * from V$SYSTEM_PARAMETER where name='spfile';

--Dynamic Performance Views
select VIEW_NAME from DBA_VIEWS where VIEW_NAME like 'V_$%';

select * from DBA_DATA_FILES;