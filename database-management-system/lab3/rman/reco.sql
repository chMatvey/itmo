startup nomount
alter database mount standby database;
recover standby databasae;
alter database open;