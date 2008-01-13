require File.dirname(__FILE__) + '/../../spec_helper'

describe Object, "#dup" do
  class ObjectSpecDup
    def initialize()
      @obj = :original
    end

    attr_accessor :obj
  end

  class ObjectSpecDupInitCopy
    def initialize()
      @obj = :original
    end

    attr_accessor :obj, :original

    def initialize_copy(original)
      @obj = :init_copy
      @original = original
    end

    private :initialize_copy
  end

  it "returns a new object duplicated from the original" do
    o = ObjectSpecDup.new
    o2 = ObjectSpecDup.new

    o.obj = 10

    o3 = o.dup

    o3.obj.should == 10
    o2.obj.should == :original
  end

  it "produces a shallow copy, contained objects are not recursively dupped" do
    o = ObjectSpecDup.new
    array = [1, 2]
    o.obj = array

    o2 = o.dup
    o2.obj.equal?(o.obj).should == true
  end

  it "calls #initialize_copy on the NEW object if available, passing in original object" do
    o = ObjectSpecDupInitCopy.new
    o2 = o.dup

    o.obj.should == :original
    o2.obj.should == :init_copy
    o2.original.equal?(o).should == true
  end
end
