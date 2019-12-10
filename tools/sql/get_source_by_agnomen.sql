select
  b.contributor_name
 , a.source_name
from
 reference_source_contributor r,
 reference_source a,
 contributor b,
 contributor_type c,
 agnomen m 
where
 r.reference_source_uuid_bin = a.uuid_bin and
 r.contributor_uuid_bin = b.uuid_bin and
 r.contributor_type_uuid_bin = c.uuid_bin and
 a.uuid_bin = r.reference_source_uuid_bin and
 b.uuid_bin = m.uuid_bin and
 m.agnomen like %s

order
 by a.source_name desc;