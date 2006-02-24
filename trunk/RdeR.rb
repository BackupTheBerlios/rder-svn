
# Subversion keyword: $Id: RdeR.rb 1068 2005-05-16 02:06:54Z shinamon $

require "RdeR.so"

module RdeR

  class R
    
    def method_missing(symbol, *args)
      symbol = symbol.to_s
      
      if (symbol.size > 0)
        fnc = symbol.to_s
      else
        fnc = args.shift
      end
      p rexpr(symbol, *args)


      eval_test_R(rexpr(symbol, *args))
    end
    
    def rexpr(symbol, *args)
      "#{symbol}(#{args.join(", ")})"
    end

private

    def eval_test_R(expr)
      begin
        #      res = evalR(expr)
        res = evalR('seq')
      rescue
        raise RException, "RException"
      end
      
      res
    end
    
  end

  class RException < Exception; end

end


