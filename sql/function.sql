SELECT tuple_data_parse('public.t1'::regclass, tuple_data_split('public.t1'::regclass, t_data, t_infomask, t_infomask2, t_bits)) FROM heap_page_items(get_raw_page('public.t1', 0));
SELECT tuple_data_parse('public.t2'::regclass, tuple_data_split('public.t2'::regclass, t_data, t_infomask, t_infomask2, t_bits)) FROM heap_page_items(get_raw_page('public.t2', 0));
