require "rder/rder.so"

module RdeR

  class R
    
    def print
      self.to_s
    end

    def method_missing(symbol, *args)
      # We need manipurations of "[", "<-" etc.
      fname = symbol.to_s

      args = args.map { |arg| Robj.new(arg) }
p args

      fetch_R(fname)
    end
    
    def rexpr(symbol, *args)
      "#{symbol}(#{args.join(", ")})"
    end

private

    def fetch_R(expr)
      begin
        res = evalR(expr)
#        res = evalR('ls')
      rescue
        raise RException, 'R Evaluation error.'
      end
      
      res
    end
    
  end

end


