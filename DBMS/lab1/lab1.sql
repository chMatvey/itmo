set verify off;
set serveroutput ON FORMAT WRAPPED;

DECLARE
    tableName           VARCHAR2(128) := '&tableName';
    noLength            NUMBER        := 3;
    columnNameLength    NUMBER        := 15;
    attributesLength    NUMBER        := 60;
    attributeNameLength NUMBER        := 15;
    tableExists         NUMBER        := 0;
    tableReached        NUMBER        := 0;

    CURSOR allColumns IS
        SELECT ALL_TAB_COLUMNS.COLUMN_ID,
               ALL_TAB_COLUMNS.COLUMN_NAME,
               ALL_TAB_COLUMNS.DATA_TYPE,
               ALL_COL_COMMENTS.COMMENTS
        FROM ALL_TAB_COLUMNS
                 INNER JOIN ALL_COL_COMMENTS
                            ON ALL_TAB_COLUMNS.COLUMN_NAME = ALL_COL_COMMENTS.COLUMN_NAME
        WHERE ALL_TAB_COLUMNS.TABLE_NAME = tableName
          AND ALL_COL_COMMENTS.TABLE_NAME = tableName;

    CURSOR notNullConstraints IS
        SELECT DISTINCT COLUMN_NAME
        FROM ALL_CONSTRAINTS
                 INNER JOIN ALL_CONS_COLUMNS
                            ON ALL_CONSTRAINTS.CONSTRAINT_NAME = ALL_CONS_COLUMNS.CONSTRAINT_NAME
        WHERE ALL_CONS_COLUMNS.TABLE_NAME = tableName
          AND ALL_CONSTRAINTS.TABLE_NAME = tableName
          AND ALL_CONSTRAINTS.CONSTRAINT_TYPE = 'C'
          AND ALL_CONSTRAINTS.SEARCH_CONDITION IS NOT NULL;

BEGIN
    IF (REGEXP_LIKE(tableName, ))

    SELECT COUNT(*) INTO tableExists
    FROM dba_tables
    WHERE TABLE_NAME = tableName;

    SELECT COUNT(*) INTO tableReached
    FROM all_tables
    WHERE TABLE_NAME = tableName;

    IF tableExists = 0 THEN
        DBMS_OUTPUT.PUT_LINE('Таблица не существует ' || tableName);
    ELSIF tableReached = 0 THEN
        DBMS_OUTPUT.PUT_LINE('У вас нет доступа к таблице ' || tableName);
    ELSE
        DBMS_OUTPUT.PUT_LINE('Таблица: ' || tableName);
        DBMS_OUTPUT.PUT_LINE('');
        DBMS_OUTPUT.PUT_LINE(RPAD('No.', noLength) || ' ' ||
                             RPAD('Имя столбца', columnNameLength) || ' ' ||
                             RPAD('Атрибуты', attributesLength));
        DBMS_OUTPUT.PUT_LINE(RPAD('-', noLength, '-') || ' ' ||
                             RPAD('-', columnNameLength, '-') || ' ' ||
                             RPAD('-', attributesLength, '-'));

        FOR column IN allColumns
            LOOP
                DBMS_OUTPUT.PUT_LINE(RPAD(column.COLUMN_ID, noLength) || ' ' ||
                                     RPAD(column.COLUMN_NAME, columnNameLength) || ' ' ||
                                     RPAD('Type:', attributeNameLength) ||
                                     RPAD(column.DATA_TYPE, attributesLength - attributeNameLength));
                IF column.COMMENTS IS NOT NULL THEN
                    DBMS_OUTPUT.PUT_LINE(RPAD(' ', noLength + columnNameLength + 2) ||
                                         RPAD('COMMEN:', attributeNameLength) ||
                                         RPAD(column.COMMENTS, attributesLength - attributeNameLength));
                end if;

                FOR constraint IN notNullConstraints
                    LOOP
                        IF (constraint.COLUMN_NAME = column.COLUMN_NAME) THEN
                            DBMS_OUTPUT.PUT_LINE(RPAD(' ', noLength + columnNameLength + 2) ||
                                                 RPAD('Constraint:', attributeNameLength) ||
                                                 RPAD('Not null', attributesLength - attributeNameLength));
                        end if;
                    end loop;
            end loop;
    end if;
END;
/
