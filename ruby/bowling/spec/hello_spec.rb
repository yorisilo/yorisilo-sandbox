require 'spec_helper'

describe Hello do
  let(:hello) { Hello.new }

  it 'should message return hello' do
    expect(hello.message).to eq 'hello'
  end
end
