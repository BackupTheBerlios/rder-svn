$LOAD_PATH.unshift('../../lib', '../ext/rder')

require 'rder'

include RdeR
#p R.public_methods.sort

c = Robj.new('c')
p c.r_class
p c.r_class = 'function'

r = R.new # R Engine starts

#p r.c.class
p r.ls
p r.sum
#p r.version

p r.class
p r.kind_of?(RdeR)
p r.kind_of?(R)

#p Robj.new(nil)#.eval


#p Robj.new('ls').eval
# p Robj.new('version').eval # version is not a R function.

__END__

p r.version



p robj1 = r.c
#p r.c('a', 'b')

#p robj2 = r.get_last_error_message

robj2 = r.ls
p robj2

#p r.geterrmessage



begin

rescue
end

puts 'END'

r.close # R Engine stops


