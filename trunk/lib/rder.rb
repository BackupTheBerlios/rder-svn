require "rder.so"

module RdeR

  class R
    
    def method_missing(symbol, *args)
      # We need manipurations of "[", "[[", "<-" etc.
      fname = symbol.to_s

      robj = Robj.new(fname, args)
    end
        
  end

end


