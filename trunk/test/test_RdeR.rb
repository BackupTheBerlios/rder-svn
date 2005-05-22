require 'test/unit'
require 'RdeR'

class TC_RdeR < Test::Unit::TestCase
  def setup
    @r = RdeR.new
  end

  def teardown 
p "teardown"
    @r.quitR
  end

  def test_klass
    assert_equal("RdeR", @r.class.to_s)
  end

   def test_method_missing
     assert_equal("Evaluate ls()", @r.ls)
     assert_equal("Evaluate ls(a)", @r.ls("a"))
     assert_equal("Evaluate ls(a, b, c)", @r["ls", "a, b, c"])
     assert_equal("Evaluate plot()", @r.plot)
   end

end
