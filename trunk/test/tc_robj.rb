$LOAD_PATH.unshift('lib', 'ext/rder')
require 'rder'

require 'test/unit'


class TC_Robj < Test::Unit::TestCase

  $r = RdeR::R.new # Is this correct approach? --- mimamu

  def setup
  end

  def teardown 
  end

  def test_length
    robj_c = $r.c
    assert(true, robj_c).kind_of?(RdeR::Robj)
    assert_equal(1, robj_c.length)
  end

end
