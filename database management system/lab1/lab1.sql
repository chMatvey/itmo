set verify off;
set serveroutput ON;

DECLARE
    --inputString            VARCHAR2(128) := '&tableName';
    inputString             VARCHAR2(128) := 's225141.point';
    tableName               VARCHAR2(128) := '';
    schemaName              VARCHAR2(128) := null;
    inputStringLength       NUMBER        := 0;
    tableNameLength         NUMBER        := 0;
    schemaNameLength        NUMBER        := 0;
    pointPosition           NUMBER        := 0;
    noLength                NUMBER        := 3;
    columnNameLength        NUMBER        := 15;
    attributesLength        NUMBER        := 60;
    attributeNameLength     NUMBER        := 15;
    tableExists             NUMBER        := 0;
    tableReached            NUMBER        := 0;
    isCorrectTableName      BOOLEAN       := TRUE;
    isCorrectSchemaName     BOOLEAN       := TRUE;
    tableAndSchemaNameRegex VARCHAR2(128) := '^[A-Za-zА-Яа-я][A-Za-zА-Яа-я0-9_$#.]*$';
    columnId                ALL_TAB_COLUMNS.COLUMN_ID%TYPE;
    columnName              ALL_TAB_COLUMNS.COLUMN_NAME%TYPE;
    columnDataType          ALL_TAB_COLUMNS.DATA_TYPE%TYPE;
    columnComment           ALL_COL_COMMENTS.COMMENTS%TYPE;
    allColumnsCursor        SYS_REFCURSOR;
    CURSOR notNullConstraints IS
        SELECT DISTINCT COLUMN_NAME
        FROM ALL_CONSTRAINTS
                 INNER JOIN ALL_CONS_COLUMNS
                            ON ALL_CONSTRAINTS.CONSTRAINT_NAME = ALL_CONS_COLUMNS.CONSTRAINT_NAME
        WHERE ALL_CONS_COLUMNS.TABLE_NAME = tableName
          AND ALL_CONSTRAINTS.TABLE_NAME = tableName
          AND ALL_CONSTRAINTS.CONSTRAINT_TYPE = 'C'
          AND ALL_CONSTRAINTS.SEARCH_CONDITION IS NOT NULL;

    PROCEDURE getColumnByTable(allColumns OUT SYS_REFCURSOR) IS
    BEGIN
        OPEN allColumns FOR
            SELECT ALL_TAB_COLUMNS.COLUMN_ID,
                   ALL_TAB_COLUMNS.COLUMN_NAME,
                   ALL_TAB_COLUMNS.DATA_TYPE,
                   ALL_COL_COMMENTS.COMMENTS
            FROM ALL_TAB_COLUMNS
                     INNER JOIN ALL_COL_COMMENTS
                                ON ALL_TAB_COLUMNS.COLUMN_NAME = ALL_COL_COMMENTS.COLUMN_NAME
            WHERE ALL_TAB_COLUMNS.TABLE_NAME = tableName
              AND ALL_COL_COMMENTS.TABLE_NAME = tableName;
    END;

    PROCEDURE getColumnByTableAndSchema(allColumns OUT SYS_REFCURSOR) IS
    BEGIN
        OPEN allColumns FOR
            SELECT ALL_TAB_COLUMNS.COLUMN_ID,
                   ALL_TAB_COLUMNS.COLUMN_NAME,
                   ALL_TAB_COLUMNS.DATA_TYPE,
                   ALL_COL_COMMENTS.COMMENTS
            FROM ALL_TAB_COLUMNS
                     INNER JOIN ALL_COL_COMMENTS
                                ON ALL_TAB_COLUMNS.COLUMN_NAME = ALL_COL_COMMENTS.COLUMN_NAME
            WHERE ALL_TAB_COLUMNS.TABLE_NAME = tableName
              AND ALL_COL_COMMENTS.TABLE_NAME = tableName
              AND ALL_TAB_COLUMNS.OWNER = schemaName;
    END;

BEGIN
    pointPosition := INSTR(inputString, '.');

    IF pointPosition != 0 THEN
        tableName := SUBSTR(inputString, pointPosition + 1);

        inputStringLength := LENGTH(inputString);
        tableNameLength := LENGTH(tableName);
        schemaNameLength := inputStringLength - tableNameLength;

        schemaName := SUBSTR(inputString, 1, schemaNameLength - 1);
        isCorrectSchemaName := REGEXP_LIKE(schemaName, tableAndSchemaNameRegex);

        SELECT TABLE_NAME, OWNER
            INTO tableName, schemaName
            FROM ALL_TAB_COLUMNS
            WHERE UPPER(TABLE_NAME) = UPPER(tableName)
            AND UPPER(OWNER) = UPPER(schemaName)
            AND ROWNUM = 1;

        SELECT COUNT(*)
        INTO tableExists
        FROM dba_tables
        WHERE TABLE_NAME = tableName
          AND OWNER = schemaName;

        SELECT COUNT(*)
        INTO tableReached
        FROM all_tables
        WHERE TABLE_NAME = tableName
          AND OWNER = schemaName;
    ELSE
        SELECT TABLE_NAME
        INTO inputString
        FROM ALL_TAB_COLUMNS
        WHERE UPPER(TABLE_NAME) = UPPER(inputString)
          AND ROWNUM = 1;

        tableName := inputString;

        SELECT COUNT(*)
        INTO tableExists
        FROM dba_tables
        WHERE TABLE_NAME = tableName;

        SELECT COUNT(*)
        INTO tableReached
        FROM all_tables
        WHERE TABLE_NAME = tableName;
    end if;

    isCorrectTableName := REGEXP_LIKE(tableName, tableAndSchemaNameRegex);

    IF NOT isCorrectTableName AND NOT isCorrectSchemaName THEN
        DBMS_OUTPUT.PUT_LINE('Имя таблицы и имя схемы не корректны');
    ELSIF NOT isCorrectTableName THEN
        DBMS_OUTPUT.PUT_LINE('Имя таблицы не корректно');
    ELSIF NOT isCorrectSchemaName THEN
        DBMS_OUTPUT.PUT_LINE('Имя схемы не корректно');
    ELSIF tableExists = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Таблица не существует ' || inputString);
    ELSIF tableReached = 0 THEN
        DBMS_OUTPUT.PUT_LINE('У вас нет доступа к таблице ' || inputString);
    ELSE
        IF schemaName IS NULL THEN
            SELECT TABLE_NAME
            INTO inputString
            FROM ALL_TAB_COLUMNS
            WHERE TABLE_NAME = tableName
              AND ROWNUM = 1;

            getColumnByTable(allColumnsCursor);
        ELSE
            SELECT TABLE_NAME, OWNER
            INTO tableName, schemaName
            FROM ALL_TAB_COLUMNS
            WHERE TABLE_NAME = tableName
              AND OWNER = schemaName
              AND ROWNUM = 1;

            inputString := UTL_LMS.FORMAT_MESSAGE('%s.%s', schemaName, tableName);

            getColumnByTableAndSchema(allColumnsCursor);
        end if;

        DBMS_OUTPUT.PUT_LINE('Таблица: ' || inputString);
        DBMS_OUTPUT.PUT_LINE('');
        DBMS_OUTPUT.PUT_LINE(RPAD('No.', noLength) || ' ' ||
                             RPAD('Имя столбца', columnNameLength) || ' ' ||
                             RPAD('Атрибуты', attributesLength));
        DBMS_OUTPUT.PUT_LINE(RPAD('-', noLength, '-') || ' ' ||
                             RPAD('-', columnNameLength, '-') || ' ' ||
                             RPAD('-', attributesLength, '-'));

        LOOP
            FETCH allColumnsCursor
                INTO columnId, columnName, columnDataType, columnComment;
            EXIT WHEN allColumnsCursor%NOTFOUND;

            DBMS_OUTPUT.PUT_LINE(RPAD(columnId, noLength) || ' ' ||
                                 RPAD(columnName, columnNameLength) || ' ' ||
                                 RPAD('Type:', attributeNameLength) ||
                                 RPAD(columnDataType, attributesLength - attributeNameLength));
            IF columnComment IS NOT NULL THEN
                DBMS_OUTPUT.PUT_LINE(RPAD(' ', noLength + columnNameLength + 2) ||
                                     RPAD('COMMEN:', attributeNameLength) ||
                                     RPAD(columnComment, attributesLength - attributeNameLength));
            end if;

            FOR constraint IN notNullConstraints
                LOOP
                    IF (constraint.COLUMN_NAME = columnName) THEN
                        DBMS_OUTPUT.PUT_LINE(RPAD(' ', noLength + columnNameLength + 2) ||
                                             RPAD('Constraint:', attributeNameLength) ||
                                             RPAD('Not null', attributesLength - attributeNameLength));
                    end if;
                end loop;
        end loop;
    end if;
END ;
/
