# -*- coding: utf-8 -*-
require "Set"

# array
array = Array.new

array.push "a" # => ["a"]
# arrayの末尾に追加

array << "b"  # => ["a", "b"]
# arrayの末尾に追加 pushのalias

array.unshift("f") # => ["f", "a", "b"]
# arrayの先頭に追加

array.push("g") # => ["f", "a", "b", "g"]
# arrayの末尾に追加

array.pop # => "g"
# arrayの末尾を取り出す

array.shift # => "f"
# arrayの先頭を取り出す

# queue
queue = Array.new
queue.push 1  # => [1]
queue.push "1" # => [1, "1"]
queue.shift  # => 1
queue # => ["1"]
queue.shift # => "1"
queue.shift # => nil

# stack
stack = []

stack.push 45  # => [45]
stack.push 21  # => [45, 21]
stack.pop  # => 21
stack # => [45]

array # => ["a", "b"]
array.push "hoge" # => ["a", "b", "hoge"]

array[-1] # => "hoge"
# 配列の末尾のインデックスは−1で指定できる


class Hello
  attr_accessor :name
  def initialize
    @name = "unko"
  end
  def say
    puts "hello #{@name}"
  end
end

class Hello2
  def initialize()
    @name = "unko"
  end
  def name
    @name
  end
  def name=(value)
    @name = value
  end
  def say
    puts "hello #{@name}"
  end
end

# HelloとHello2クラスは同じ意味

hello = Hello2.new

hello.name = "chinpo"
# これはオブジェクトの属性のようなものに代入を行っているように感じるが，
# 実際は，hello.name=("chinpo")というメソッド呼び出しを行っている

hello.say


def hogehoge x, &proc
  proc.call if block_given?
  return x + 2
end

p hogehoge( 3 )
p hogehoge( 5 ){ p "foo" }   # => 7
# >> hello chinpo
# >> 5
# >> "foo"
# >> 7
