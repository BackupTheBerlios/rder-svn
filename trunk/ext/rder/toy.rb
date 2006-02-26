$LOAD_PATH.unshift('../../lib', '../ext/rder')

require 'rder'

include RdeR
#p R.public_methods.sort

r = R.new # R Engine starts

p r.class
p r.kind_of?(RdeR)
p r.kind_of?(R)

#p Robj.new(nil)#.eval


r_c = Robj.function('c')

p res = r_c.eval # shuld be 

p res.kind_of?(Robj)

#p Robj.new('ls').eval
# p Robj.new('version').eval # version is not a R function.

__END__

p r.version



p robj1 = r.c
#p r.c('a', 'b')

#p robj2 = r.get_last_error_message

robj2 = r.ls
p robj2
# p robj2.length
# p robj1.length
#p robj2.size

#p r.geterrmessage



begin

rescue
end

puts 'END'

r.close # R Engine stops


