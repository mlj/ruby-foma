require 'foma'
require 'test/unit'

TEST_DIRECTORY = File.expand_path(File.dirname(__FILE__))
TEST_FSM       = File.join(TEST_DIRECTORY, 'test_foma.bin')

class InitTestCase < Test::Unit::TestCase
  def test_foma_init
    fsm = FOMA::FSM.new(TEST_FSM)
  end

  def test_foma_acceptance
    fsm = FOMA::FSM.new(TEST_FSM)

    assert fsm.apply_up("amandum")
    assert !fsm.apply_up("amanderxgtyvnuij")
    assert fsm.apply_down("amō+VERB+ger+acc")
    assert !fsm.apply_up("amō+VERB+ger+foobar")
  end

  def test_foma_analyses
    fsm = FOMA::FSM.new(TEST_FSM)

    analyses = []

    fsm.apply_up("amandum") do |analysis|
      analyses << analysis
    end

    assert_equal 3, analyses.count
    assert_equal "amō+VERB+gdv+masc+sg+acc", analyses.sort.first
  end
end
