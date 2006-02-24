require 'test/unit'

require 'RdeR'

class TestCaseRdeR < Test::Unit::TestCase

  $r = RdeR.new # Is this correct approach? --- mimamu

  def setup

  end

  def teardown 
  end

  def test_klass
    assert_equal("RdeR", $r.class.to_s)
  end

#   def test_method_missing
#     assert_equal("Evaluate ls()", $r.ls)
#     assert_equal("Evaluate ls(a)", $r.ls("a"))
#     assert_equal("Evaluate ls(a, b, c)", $r["ls", "a, b, c"])
#     assert_equal("Evaluate plot()", $r.plot)
#   end
  
  def test_rexpr
    assert_equal("ls()", $r.rexpr("ls"))
    assert_equal("ls(a, b, c)", $r.rexpr("ls",["a", "b", "c"]))
  end

  def test_evalR
    assert_nil($r.evalR("c")) # R: c() => NULL
  end
end
