$LOAD_PATH.unshift('lib', 'ext/rder')
require 'rder'

require 'test/unit'


class TC_Robj < Test::Unit::TestCase

  include RdeR

  $r = R.new # Is this correct approach? --- mimamu

  def setup

  end

  def teardown 
  end

  def test_initialize
    robj = Robj.new('foo')
    assert(robj.kind_of?(Robj))

    # not implemented yet
#    assert_raise(RobjException) { robj = Robj.new(1) }
    
  end

  def test_length
    robj = $r.c
    assert(true, robj).kind_of?(RdeR::Robj)
    assert_equal(1, robj.length)

#    robj = $r.c(1, 2, 3, 4)
#    assert_equal(4, robj.length)
  end

end
