require 'rder'

include RdeR
#p R.public_methods.sort

r = RdeR::R.new
p r.class
p r.kind_of?(RdeR)
p r.c()
p r.get_last_error_message



