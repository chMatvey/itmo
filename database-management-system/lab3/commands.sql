alter system set log_archive_format='%t_%s_%r.arc'
alter system archive log current;
ARCHIVE LOG LIST

startup mount
alter database archivelog;
alter system archive log start;
alter database create standby controlfile as '/u01/yak27/bestmeat/ctrl.ctl';