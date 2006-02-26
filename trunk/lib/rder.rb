require "rder.so"

module RdeR

  class R
    
    def method_missing(symbol, *args)
      # We need manipurations of "[", "[[", "<-" etc.
      fname = symbol.to_s

      robj = Robj.function(fname)
      robj.args = args

      return robj
      # robj.mock_eval

    end
    
  end

  class Robj
    def mock_eval
      'evaluating my R expression...'
    end
  end

end


