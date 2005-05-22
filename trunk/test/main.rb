require "RdeR"

r = RdeR.new

p r.class

p r["ls", "a, g, c"]
p r.ls("a, b, c")
p r.ls
p r.ls(r.plot("a"))

p r.eval_R("sum")
p r.eval_R("ls")
r
.quitR

q = RdeR.new
p q.class
