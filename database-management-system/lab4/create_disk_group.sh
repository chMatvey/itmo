#!/bin/bash

group1=famouseagle;
group2=cutechimpanzee;
group3=carelessfrog;
group4=crazycheetah;

mkdir -p /u01/$group1;
mkdir -p /u01/$group2;
mkdir -p /u01/$group3;
mkdir -p /u01/$group4;

for i in {0..6}
do
    if ((i < 6));
    then
        /usr/sbin/mkfile 250m /u01/$group1/$group1$i;
        /usr/sbin/mkfile 250m /u01/$group3/$group3$i;
    fi

    /usr/sbin/mkfile 250m /u01/$group2/$group2$i;

    if ((i < 3));
    then
        /usr/sbin/mkfile 250m /u01/$group4/$group4$i;
    fi
done;