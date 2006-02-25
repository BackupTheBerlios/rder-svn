require "rder/rder.so"

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
#        res = evalR(expr)
        res = evalR('ls')
      rescue
        raise RException, 'R Evaluation error.'
      end
      
      res
    end
    
  end

end


