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
    robj = $r.c
    assert(true, robj).kind_of?(RdeR::Robj)
    assert_equal(1, robj.length)

    robj = $r.version # environment() returns 12 length 
    assert_equal(12, robj.length)

    robj = $r.c(1, 2, 3, 4)
    assert_equal(4, robj.length)
  end

  def test_to_rexp
    robj = $r.c
    robj.to_rexp
  end

  

end
