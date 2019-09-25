DECLARE
    tableName           VARCHAR2(128) := 'Н_УЧЕНИКИ';
    no                  VARCHAR2(16)  := 'No.';
    columnName          VARCHAR2(128) := 'Имя столбца';
    attributes          VARCHAR2(128) := 'Атрибуты';
    noLength            NUMBER        := 3;
    columnNameLength    NUMBER        := 15;
    attributesLength    NUMBER        := 60;
    attributeNameLength NUMBER        := 15;
    typeName            VARCHAR2(128) := 'Type:';
    commentName         VARCHAR2(128) := 'COMMEN:';
    constraintName      VARCHAR2(128) := 'Constraint:';
    CURSOR allColumns IS
        SELECT ALL_TAB_COLUMNS.COLUMN_ID,
               ALL_TAB_COLUMNS.COLUMN_NAME,
               ALL_TAB_COLUMNS.DATA_TYPE,
               ALL_COL_COMMENTS.COMMENTS
        FROM ALL_TAB_COLUMNS
                 INNER JOIN ALL_COL_COMMENTS
                            ON ALL_TAB_COLUMNS.COLUMN_NAME = ALL_COL_COMMENTS.COLUMN_NAME

        WHERE ALL_TAB_COLUMNS.TABLE_NAME = 'Н_УЧЕНИКИ'
          AND ALL_COL_COMMENTS.TABLE_NAME = 'Н_УЧЕНИКИ';
    CURSOR notNullConstraints IS
        SELECT DISTINCT COLUMN_NAME
        FROM ALL_CONSTRAINTS
                 INNER JOIN ALL_CONS_COLUMNS
                            ON ALL_CONSTRAINTS.CONSTRAINT_NAME = ALL_CONS_COLUMNS.CONSTRAINT_NAME

        WHERE ALL_CONS_COLUMNS.TABLE_NAME = 'Н_УЧЕНИКИ'
          AND ALL_CONSTRAINTS.TABLE_NAME = 'Н_УЧЕНИКИ'
          AND ALL_CONSTRAINTS.CONSTRAINT_TYPE = 'C'
          AND ALL_CONSTRAINTS.SEARCH_CONDITION IS NOT NULL;

BEGIN
    DBMS_OUTPUT.PUT_LINE('Таблица: ' || tableName);
    DBMS_OUTPUT.PUT_LINE('');
    DBMS_OUTPUT.PUT_LINE(RPAD(no, noLength) || ' ' ||
                         RPAD(columnName, columnNameLength) || ' ' ||
                         RPAD(attributes, attributesLength));
    DBMS_OUTPUT.PUT_LINE(RPAD('-', noLength, '-') || ' ' ||
                         RPAD('-', columnNameLength, '-') || ' ' ||
                         RPAD('-', attributesLength, '-'));

    FOR column IN allColumns
        LOOP
            DBMS_OUTPUT.PUT_LINE(RPAD(column.COLUMN_ID, noLength) || ' ' ||
                                 RPAD(column.COLUMN_NAME, columnNameLength) || ' ' ||
                                 RPAD(typeName, attributeNameLength) ||
                                 RPAD(column.DATA_TYPE, attributesLength - attributeNameLength));
            IF column.COMMENTS IS NOT NULL THEN
                DBMS_OUTPUT.PUT_LINE(RPAD(' ', noLength + columnNameLength + 2) ||
                                     RPAD(commentName, attributeNameLength) ||
                                     RPAD(column.COMMENTS, attributesLength - attributeNameLength));
            end if;

            FOR constraint IN notNullConstraints
                LOOP
                    IF (constraint.COLUMN_NAME = column.COLUMN_NAME) THEN
                        DBMS_OUTPUT.PUT_LINE(RPAD(' ', noLength + columnNameLength + 2) ||
                                             RPAD(constraintName, attributeNameLength) ||
                                             RPAD('Not null', attributesLength - attributeNameLength));
                    end if;
                end loop;
        end loop;
END;
