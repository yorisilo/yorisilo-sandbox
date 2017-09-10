require "Set"

class Graph
  attr_reader :vertices,:edges

  def initialize
    @vertices = Set.new
    @edges = Hash.new
  end

  def add_vertex(v)
    @vertices.add(v)
  end

  def add_edge(v1,v2)
    @edges[v1] ||= Set.new
    @edges[v1].add(v2)
    @edges[v2] ||= Set.new
    @edges[v2].add(v1)

    @vertices.add(v1).add(v2)
  end
end

def combination(n,m) # nCm
  if n>m
    factorial(n) / (factorial(m) * factorial(n-m))
  end
end

def factorial(n)
  if n >= 1
    n * factorial(n-1)
  else
    1
  end
end

p combination(4,3)
# >> 4
