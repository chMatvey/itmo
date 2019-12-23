startup nomount
alter database mount standby database;
recover standby database;
auto
shutdown immediate;
exit;