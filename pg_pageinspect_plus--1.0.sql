
CREATE FUNCTION pg_catalog.bytea2timestamp(dat bytea)
RETURNS timestamp AS 'MODULE_PATHNAME', 'bytea2timestamp'
LANGUAGE C VOLATILE STRICT;

CREATE FUNCTION pg_catalog.bytea2timestamptz(dat bytea)
RETURNS timestamptz AS 'MODULE_PATHNAME', 'bytea2timestamptz'
LANGUAGE C VOLATILE STRICT;

CREATE FUNCTION pg_catalog.bytea2interval(dat bytea)
RETURNS interval AS 'MODULE_PATHNAME', 'bytea2interval'
LANGUAGE C VOLATILE STRICT;

CREATE FUNCTION pg_catalog.bytea2int(dat bytea)
RETURNS int4 AS 'MODULE_PATHNAME', 'bytea2int'
LANGUAGE C VOLATILE STRICT;

CREATE FUNCTION pg_catalog.bytea2bigint(dat bytea)
RETURNS int8 AS 'MODULE_PATHNAME', 'bytea2bigint'
LANGUAGE C VOLATILE STRICT;

CREATE FUNCTION pg_catalog.bytea2boolean(dat bytea)
RETURNS boolean AS 'MODULE_PATHNAME', 'bytea2boolean'
LANGUAGE C VOLATILE STRICT;

CREATE FUNCTION pg_catalog.bytea2text(dat bytea)
RETURNS text AS 'MODULE_PATHNAME', 'bytea2text'
LANGUAGE C VOLATILE STRICT;

CREATE FUNCTION pg_catalog.bytea2float4(dat bytea)
RETURNS float4 AS 'MODULE_PATHNAME', 'bytea2float4'
LANGUAGE C VOLATILE STRICT;

CREATE FUNCTION pg_catalog.bytea2float8(dat bytea)
RETURNS float8 AS 'MODULE_PATHNAME', 'bytea2float8'
LANGUAGE C VOLATILE STRICT;


CREATE FUNCTION pg_catalog.tuple_data_parse(rel_oid oid, tuple_data bytea[])
RETURNS text[] LANGUAGE plpgsql VOLATILE STRICT AS
$func$
DECLARE
  r1 RECORD;
  ret_arr text[] := '{}'::text[];
  ret_item text;
BEGIN
  FOR r1 IN SELECT atttypid, attnum
    FROM pg_attribute WHERE attnum > 0 AND attrelid = rel_oid ORDER BY attnum
  LOOP
    IF r1.atttypid = 23 THEN
      ret_item := bytea2int(tuple_data[r1.attnum])::text;
    ELSIF r1.atttypid = 20 THEN
      ret_item := bytea2bigint(tuple_data[r1.attnum])::text;
    ELSIF r1.atttypid = 25 OR r1.atttypid = 1042 OR r1.atttypid = 1043 OR r1.atttypid = 114 THEN
      ret_item := bytea2text(tuple_data[r1.attnum])::text;
    ELSIF r1.atttypid = 16 THEN
      ret_item := bytea2boolean(tuple_data[r1.attnum])::text;
    ELSIF r1.atttypid = 1114 THEN
      ret_item := bytea2timestamp(tuple_data[r1.attnum])::text;
    ELSIF r1.atttypid = 1184 THEN
      ret_item := bytea2timestamptz(tuple_data[r1.attnum])::text;
    ELSIF r1.atttypid = 1186 THEN
      ret_item := bytea2interval(tuple_data[r1.attnum])::text;
    ELSIF r1.atttypid = 700 THEN
      ret_item := bytea2float4(tuple_data[r1.attnum])::text;
    ELSIF r1.atttypid = 701 THEN
      ret_item := bytea2float8(tuple_data[r1.attnum])::text;
    ELSE ret_item := '';
    END IF;
    ret_arr := ret_arr || ARRAY[ret_item];
  END LOOP;
  RETURN ret_arr;
END;
$func$;

