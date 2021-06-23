SELECT ALL_TAB_COLUMNS.COLUMN_ID,
       ALL_TAB_COLUMNS.COLUMN_NAME,
       ALL_TAB_COLUMNS.DATA_TYPE,
       ALL_COL_COMMENTS.COMMENTS,
       ALL_COL_COMMENTS.OWNER
FROM ALL_TAB_COLUMNS
         INNER JOIN ALL_COL_COMMENTS
                    ON ALL_TAB_COLUMNS.COLUMN_NAME = ALL_COL_COMMENTS.COLUMN_NAME

WHERE ALL_TAB_COLUMNS.TABLE_NAME = 'POINT'
  AND ALL_COL_COMMENTS.TABLE_NAME = 'POINT'
  AND ALL_TAB_COLUMNS.OWNER = 'S225141';
