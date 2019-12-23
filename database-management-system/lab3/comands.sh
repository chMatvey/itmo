ssh-keygen -t rsa
cat ~/.ssh/id_rsa.pub | ssh oracle@db146 "mkdir -p ~/.ssh && touch ~/.ssh/authorized_keys && chmod -R go= ~/.ssh && cat >> ~/.ssh/authorized_keys"

ssh-keygen -t rsa
cat ~/.ssh/id_rsa.pub | ssh oracle@db197 "mkdir -p ~/.ssh && touch ~/.ssh/authorized_keys && chmod -R go= ~/.ssh && cat >> ~/.ssh/authorized_keys"

rm -rf adump/*
rm -rf logs/*

alter tablespace COOL_GOLD_DISK offline immediate;
cd $ORADATA/node02
rm coolgolddisk01.dbf
alter tablespace COOL_GOLD_DISK online immediate;

echo "startup nomount
alter database mount standby database;
recover standby database;
auto
shutdown immediate;
exit;" > recover.sql
