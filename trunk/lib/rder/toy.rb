$:.unshift('..')

require 'rder'

include RdeR
#p R.public_methods.sort

r = R.new
p r.class
p r.kind_of?(RdeR)
p r.kind_of?(R)
p robj1 = r.c()
p r.c('a', 'b')

#p robj2 = r.get_last_error_message

p robj1.size
#p robj2.size

#p r.geterrmessage


r.close


