$:.unshift('..')

require 'rder'

include RdeR
#p R.public_methods.sort

r = R.new
p r.class
p r.kind_of?(RdeR)
p r.kind_of?(R)
p robj1 = r.c()
p robj2 = r.get_last_error_message

r.close

p robj1.mode

robj = Robj.new
p robj.kind_of?(Robj)


