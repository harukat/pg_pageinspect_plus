#include "postgres.h"
#include "fmgr.h"

#include <ctype.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <sys/time.h>

#include "access/hash.h"
#include "access/xact.h"
#include "catalog/pg_type.h"
#include "funcapi.h"
#include "libpq/pqformat.h"
#include "miscadmin.h"
#include "nodes/nodeFuncs.h"
#include "parser/scansup.h"
#include "utils/array.h"
#include "utils/builtins.h"
#include "utils/datetime.h"

PG_MODULE_MAGIC;

Datum bytea2timestamp(PG_FUNCTION_ARGS);
Datum bytea2timestamptz(PG_FUNCTION_ARGS);
Datum bytea2interval(PG_FUNCTION_ARGS);
Datum bytea2int(PG_FUNCTION_ARGS);
Datum bytea2bigint(PG_FUNCTION_ARGS);
Datum bytea2boolean(PG_FUNCTION_ARGS);
Datum bytea2text(PG_FUNCTION_ARGS);
Datum bytea2float4(PG_FUNCTION_ARGS);
Datum bytea2float8(PG_FUNCTION_ARGS);

PG_FUNCTION_INFO_V1(bytea2timestamp);
PG_FUNCTION_INFO_V1(bytea2timestamptz);
PG_FUNCTION_INFO_V1(bytea2interval);
PG_FUNCTION_INFO_V1(bytea2int);
PG_FUNCTION_INFO_V1(bytea2bigint);
PG_FUNCTION_INFO_V1(bytea2boolean);
PG_FUNCTION_INFO_V1(bytea2text);
PG_FUNCTION_INFO_V1(bytea2float4);
PG_FUNCTION_INFO_V1(bytea2float8);

Datum
bytea2timestamp(PG_FUNCTION_ARGS)
{
	bytea      *bytea_val = PG_GETARG_BYTEA_PP(0);
	if (8 > VARSIZE_ANY_EXHDR(bytea_val)) PG_RETURN_NULL();
	PG_RETURN_TIMESTAMP( *((int64*) VARDATA_ANY(bytea_val)));
}

Datum
bytea2timestamptz(PG_FUNCTION_ARGS)
{
	bytea      *bytea_val = PG_GETARG_BYTEA_PP(0);
	if (8 > VARSIZE_ANY_EXHDR(bytea_val)) PG_RETURN_NULL();
	PG_RETURN_TIMESTAMPTZ( *((int64*) VARDATA_ANY(bytea_val)));
}

Datum
bytea2interval(PG_FUNCTION_ARGS)
{
	bytea      *bytea_val = PG_GETARG_BYTEA_PP(0);
	if (16 > VARSIZE_ANY_EXHDR(bytea_val)) PG_RETURN_NULL();
	PG_RETURN_INTERVAL_P( (Interval*) VARDATA_ANY(bytea_val));
}

Datum
bytea2int(PG_FUNCTION_ARGS)
{
	bytea      *bytea_val = PG_GETARG_BYTEA_PP(0);
	if (4 > VARSIZE_ANY_EXHDR(bytea_val)) PG_RETURN_NULL();
	PG_RETURN_INT32( *((int32*) VARDATA_ANY(bytea_val)));
}

Datum
bytea2bigint(PG_FUNCTION_ARGS)
{
	bytea      *bytea_val = PG_GETARG_BYTEA_PP(0);
	if (8 > VARSIZE_ANY_EXHDR(bytea_val)) PG_RETURN_NULL();
	PG_RETURN_INT64( *((int64*) VARDATA_ANY(bytea_val)));
}

Datum
bytea2boolean(PG_FUNCTION_ARGS)
{
	bytea      *bytea_val = PG_GETARG_BYTEA_PP(0);
	if (1 > VARSIZE_ANY_EXHDR(bytea_val)) PG_RETURN_NULL();
	PG_RETURN_BOOL( *((unsigned char*) VARDATA_ANY(bytea_val)));
}

Datum
bytea2text(PG_FUNCTION_ARGS)
{
	bytea  *bytea_val = PG_GETARG_BYTEA_PP(0);
	text   *text_val;
	int len;

	len = VARSIZE_ANY_EXHDR(bytea_val);
	text_val = (text*) palloc(len + VARHDRSZ);
	SET_VARSIZE(text_val, len + VARHDRSZ);
	memcpy(VARDATA_ANY(text_val), VARDATA_ANY(VARDATA_ANY(bytea_val)), len);
	PG_RETURN_TEXT_P(text_val);
}

Datum
bytea2float4(PG_FUNCTION_ARGS)
{
	bytea      *bytea_val = PG_GETARG_BYTEA_PP(0);
	if (4 > VARSIZE_ANY_EXHDR(bytea_val)) PG_RETURN_NULL();
	PG_RETURN_FLOAT4( *((float4*) VARDATA_ANY(bytea_val)));
}


Datum
bytea2float8(PG_FUNCTION_ARGS)
{
	bytea      *bytea_val = PG_GETARG_BYTEA_PP(0);
	if (8 > VARSIZE_ANY_EXHDR(bytea_val)) PG_RETURN_NULL();
	PG_RETURN_FLOAT8( *((float8*) VARDATA_ANY(bytea_val)));
}

