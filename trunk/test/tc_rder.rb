$LOAD_PATH.unshift('lib', 'ext/rder')
require 'rder'

require 'test/unit'


class TC_R < Test::Unit::TestCase

  $r = RdeR::R.new # Is this correct approach? --- mimamu

  def setup

  end

  def teardown 
  end

  def test_klass
    assert_equal(RdeR::R, $r.class)
  end

#   def test_method_missing
#     assert_equal("Evaluate ls()", $r.ls)
#     assert_equal("Evaluate ls(a)", $r.ls("a"))
#     assert_equal("Evaluate ls(a, b, c)", $r["ls", "a, b, c"])
#     assert_equal("Evaluate plot()", $r.plot)
#   end
  
  def test_evalR
    assert(true, $r.evalR("c").kind_of?(RdeR::Robj))
  end

end
