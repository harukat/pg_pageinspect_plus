CREATE EXTENSION pageinspect ;
CREATE EXTENSION pg_pageinspect_plus ;
CREATE TABLE public.t1 (id integer, txt text,ts timestamp without time zone, bool boolean, i8 bigint) ;
CREATE TABLE public.t2 (c1 character varying(5), c2 character(5),
 tstz timestamp(3) with time zone, f1 real, df1 double precision, h1 json, iv interval) ;
INSERT INTO public.t1 VALUES (100, 'ABCDE', '2020-08-01 12:00:00', 't', 98765432), (101, 'abcde', '2025-08-01 12:00:00', 'f', 554433221100);
INSERT INTO public.t2 VALUES ('xxx', 'XXX', '2020-08-02 21:19:00.698+09', 1.234, 9.87654321, '["a","b","c"]', '100:00:00');
