SELECT DISTINCT COLUMN_NAME
FROM ALL_CONSTRAINTS
         INNER JOIN ALL_CONS_COLUMNS
                    ON ALL_CONSTRAINTS.CONSTRAINT_NAME = ALL_CONS_COLUMNS.CONSTRAINT_NAME

WHERE ALL_CONS_COLUMNS.TABLE_NAME = 'Н_УЧЕНИКИ'
  AND ALL_CONSTRAINTS.TABLE_NAME = 'Н_УЧЕНИКИ'
  AND ALL_CONSTRAINTS.CONSTRAINT_TYPE = 'C'
  AND ALL_CONSTRAINTS.SEARCH_CONDITION IS NOT NULL;
