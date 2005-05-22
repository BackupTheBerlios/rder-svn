
# Subversion keyword: $Id: RdeR.rb 1068 2005-05-16 02:06:54Z shinamon $

require "RdeR.so"

class RdeR

#   def method_missing(symbol, *args)
#     symbol = symbol.id2name.delete("[]")
#     if (symbol.size > 0)
#       fnc = symbol.to_s
#     else
#       fnc = args.shift
#     end

#     eval_test_R(rexpr(symbol, *args))
#   end

  def rexpr(symbol, *args)
    "#{symbol}(#{args.join(", ")})"
  end

  def eval_test_R(expr)
    "Evaluate #{expr}"
  end


end

class RdeRException < Exception
  def initialize
  end
end
