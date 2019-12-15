select
  a.source_name
from
 reference_source a 
where
 a.reference_source_id > 0
order
 by a.source_name -- desc		;