MODULES = pg_pageinspect_plus

PG_CPPFLAGS = -L$(libdir)
EXTENSION = pg_pageinspect_plus
DATA = pg_pageinspect_plus--1.0.sql pg_pageinspect_plus.control

REGRESS = init function

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)


