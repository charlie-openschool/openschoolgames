select
  b.contributor_name
 , a.source_name
from
 reference_source_contributor r,
 reference_source a,
 contributor b,
 contributor_type c 
where
 r.reference_source_uuid_bin = a.uuid_bin and
 r.contributor_uuid_bin = b.uuid_bin and
 r.contributor_type_uuid_bin = c.uuid_bin and
 a.source_name like %s
order
 by a.source_name desc		;