$LOAD_PATH.unshift('../../lib', '../ext/rder')

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

robj2 = r.ls
p robj2.length
p robj1.length
#p robj2.size

#p r.geterrmessage



begin

rescue
end

puts 'END'

r.close


