# pg\_pageinspect\_plus

This is a PostgreSQL Extension which helps page inspection with contrib/pageinspect.
It works in PostgreSQL 10 to 17 version.

## Usage example

````
db1=# CREATE EXTENSION pageinspect ;
db1=# CREATE EXTENSION pg_pageinspect_plus ;

db1=# \d public.t1
                           Table "public.t1"
 Column |            Type             | Collation | Nullable | Default
--------+-----------------------------+-----------+----------+---------
 id     | integer                     |           |          |
 txt    | text                        |           |          |
 ts     | timestamp without time zone |           |          |
 bool   | boolean                     |           |          |
 i8     | bigint                      |           |          |

db1=# SELECT * FROM public.t1;
 id  |  txt  |         ts          | bool |      i8
-----+-------+---------------------+------+--------------
 100 | ABCDE | 2020-08-01 12:00:00 | t    |     98765432
 101 | abcde | 2025-08-01 12:00:00 | f    | 554433221100
(2 rows)

db1=# SELECT *, tuple_data_split('public.t1'::regclass, t_data, t_infomask, t_infomask2, t_bits) FROM heap_page_items(get_raw_page('public.t1', 0));
 lp | lp_off | lp_flags | lp_len | t_xmin | t_xmax | t_field3 | t_ctid | t_infomask2 | t_infomask | t_hoff | t_bits | t_oid |                                       t_data                                       |                                   tuple_data_split
----+--------+----------+--------+--------+--------+----------+--------+-------------+------------+--------+--------+-------+------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------
  1 |   8128 |        1 |     64 |    501 |      0 |        0 | (0,1)  |           5 |      11010 |     24 |        |       | \x640000000d414243444500000000000000f0e069ce4e02000100000000000000780ae30500000000 | {"\\x64000000","\\x0d4142434445","\\x00f0e069ce4e0200","\\x01","\\x780ae30500000000"}
  2 |   8064 |        1 |     64 |    502 |      0 |        0 | (0,2)  |           5 |      11010 |     24 |        |       | \x650000000d616263646500000000000000b01b444bde02000000000000000000ec91cb1681000000 | {"\\x65000000","\\x0d6162636465","\\x00b01b444bde0200","\\x00","\\xec91cb1681000000"}
(2 rows)

db1=# SELECT *, tuple_data_parse('public.t1'::regclass, tuple_data_split('public.t1'::regclass, t_data, t_infomask, t_infomask2, t_bits)) FROM heap_page_items(get_raw_page('public.t1', 0));
 lp | lp_off | lp_flags | lp_len | t_xmin | t_xmax | t_field3 | t_ctid | t_infomask2 | t_infomask | t_hoff | t_bits | t_oid |                                       t_data                                       |                   tuple_data_parse
----+--------+----------+--------+--------+--------+----------+--------+-------------+------------+--------+--------+-------+------------------------------------------------------------------------------------+------------------------------------------------------
  1 |   8128 |        1 |     64 |    501 |      0 |        0 | (0,1)  |           5 |      11010 |     24 |        |       | \x640000000d414243444500000000000000f0e069ce4e02000100000000000000780ae30500000000 | {100,ABCDE,"2020-08-01 12:00:00",true,98765432}
  2 |   8064 |        1 |     64 |    502 |      0 |        0 | (0,2)  |           5 |      11010 |     24 |        |       | \x650000000d616263646500000000000000b01b444bde02000000000000000000ec91cb1681000000 | {101,abcde,"2025-08-01 12:00:00",false,554433221100}
(2 rows)


db1=# \d public.t2
                           Table "public.t2"
 Column |            Type             | Collation | Nullable | Default
--------+-----------------------------+-----------+----------+---------
 c1     | character varying(5)        |           |          |
 c2     | character(5)                |           |          |
 tstz   | timestamp(3) with time zone |           |          |
 f1     | real                        |           |          |
 df1    | double precision            |           |          |
 h1     | json                        |           |          |
 iv     | interval                    |           |          |

db1=# SELECT * FROM t2;
 c1  |  c2   |            tstz            |  f1   |    df1     |      h1       |    iv
-----+-------+----------------------------+-------+------------+---------------+-----------
 xxx | XXX   | 2020-08-02 21:19:00.698+09 | 1.234 | 9.87654321 | ["a","b","c"] | 100:00:00
(1 row)


db1=# SELECT *, tuple_data_split('public.t2'::regclass, t_data, t_infomask, t_infomask2, t_bits) FROM heap_page_items(get_raw_page('public.t2', 0));
 lp | lp_off | lp_flags | lp_len | t_xmin | t_xmax | t_field3 | t_ctid | t_infomask2 | t_infomask | t_hoff | t_bits | t_oid |                                                                       t_data                                                                       |                                                                          tuple_data_split      
----+--------+----------+--------+--------+--------+----------+--------+-------------+------------+--------+--------+-------+----------------------------------------------------------------------------------------------------------------------------------------------------+---------------------------------------------------------------------------------------------------------------------------------------------------------------------
  1 |   8096 |        1 |     96 |    541 |      0 |        0 | (0,1)  |           7 |      11010 |     24 |        |       | \x097878780d585858202000000000000090fbb5cbe24e0200b6f39d3f0000000033f68845cac023401d5b2261222c2262222c2263225d00000010acd1530000000000000000000000 | {"\\x09787878","\\x0d5858582020","\\x90fbb5cbe24e0200","\\xb6f39d3f","\\x33f68845cac02340","\\x1d5b2261222c2262222c2263225d","\\x0010acd1530000000000000000000000"}
(1 row)


db1=# SELECT bytea2text('\x0d5858582020');
 bytea2text
------------
 XXX
(1 row)

db1=# SELECT bytea2timestamptz('\x90fbb5cbe24e0200');
     bytea2timestamptz
----------------------------
 2020-08-02 21:19:00.698+09
(1 row)

db1=# SELECT bytea2float4('\xb6f39d3f');
 bytea2float4
--------------
        1.234
(1 row)

db1=# SELECT bytea2float8('\x33f68845cac02340');
 bytea2float8
--------------
   9.87654321
(1 row)

db1=# SELECT bytea2text('\x1d5b2261222c2262222c2263225d');
  bytea2text
---------------
 ["a","b","c"]
(1 row)

db1=# SELECT bytea2interval('\x0010acd1530000000000000000000000');
 bytea2interval
----------------
 100:00:00
(1 row)

````

## functions

|function                     |return   |
|-----------------------------|---------|
|bytea2timestamp(dat bytea)   |timestamp   |
|bytea2timestamptz(dat bytea) |timestamptz |
|bytea2interval(dat bytea)    |interval    |
|bytea2int(dat bytea)         |int4    |
|bytea2bigint(dat bytea)      |int8    |
|bytea2boolean(dat bytea)     |boolean |
|bytea2text(dat bytea)        |text    |
|bytea2float4(dat bytea)      |float4  |
|bytea2float8(dat bytea)      |float8  |
|tuple_data_parse(rel_oid oid, tuple_data bytea[]) | text[] |

bytea2text can also be used for char, varchar and json type.


