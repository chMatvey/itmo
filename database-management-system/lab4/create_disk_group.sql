CREATE DISKGROUP famouseagle NORMAL REDUNDANCY
    '/u01/famouseagle/famouseagle0',
    '/u01/famouseagle/famouseagle1',
    '/u01/famouseagle/famouseagle2',
    '/u01/famouseagle/famouseagle3',
    '/u01/famouseagle/famouseagle4',
    '/u01/famouseagle/famouseagle5'
ATTRIBUTE 'COMPATIBLE.ASM'='11.2.0.0.0';

CREATE DISKGROUP cutechimpanzee EXTERNAL REDUNDANCY DISK
    '/u01/cutechimpanzee/cutechimpanzee0',
    '/u01/cutechimpanzee/cutechimpanzee1',
    '/u01/cutechimpanzee/cutechimpanzee2',
    '/u01/cutechimpanzee/cutechimpanzee3',
    '/u01/cutechimpanzee/cutechimpanzee4',
    '/u01/cutechimpanzee/cutechimpanzee5',
    '/u01/cutechimpanzee/cutechimpanzee6'
ATTRIBUTE 'COMPATIBLE.ASM'='11.2.0.0.0';

CREATE DISKGROUP carelessfrog EXTERNAL REDUNDANCY DISK
    '/u01/carelessfrog/carelessfrog0',
    '/u01/carelessfrog/carelessfrog1',
    '/u01/carelessfrog/carelessfrog2',
    '/u01/carelessfrog/carelessfrog3',
    '/u01/carelessfrog/carelessfrog4',
    '/u01/carelessfrog/carelessfrog5'
ATTRIBUTE 'COMPATIBLE.ASM'='11.2.0.0.0';

CREATE DISKGROUP crazycheetah EXTERNAL REDUNDANCY DISK
    '/u01/crazycheetah/crazycheetah0',
    '/u01/crazycheetah/crazycheetah1',
    '/u01/crazycheetah/crazycheetah2'
ATTRIBUTE 'COMPATIBLE.ASM'='11.2.0.0.0';

CREATE DISKGROUP crazycheetah NORMAL REDUNDANCY
    FAILGROUP new_fg1 DISK
    '/u01/crazycheetah/crazycheetah0' NAME crazycheetah0,
    '/u01/crazycheetah/crazycheetah1' NAME crazycheetah1,
    '/u01/crazycheetah/crazycheetah2' NAME crazycheetah2
    FAILGROUP new_fg2 DISK
    '/u01/crazycheetah/crazycheetah3' NAME crazycheetah3,
    '/u01/crazycheetah/crazycheetah4' NAME crazycheetah4,
    '/u01/crazycheetah/crazycheetah5' NAME crazycheetah5;