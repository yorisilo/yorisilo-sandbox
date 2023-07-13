# -*- coding: utf-8 -*-
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

def bfs(start,graph)
  queue = [start]
  visited = Set.new
  loop do
    top = queue.shift
    if ((top == nil) && (visited != graph.vertices))
      p "graph is not connected"
      break
    end
    visited.add(top)
    if graph.edges[top] # topの子ノードが存在する場合
      graph.edges[top].each do |child|
        if !(queue.include?(child) || visited.include?(child))
          queue.push(child)
        end
      end
    end
    if visited == graph.vertices
      p "graph is connected"
      break
    end
  end
end

def combination(n,m) # nCm
  if n>m
    factorial(n) / (factorial(m) * factorial(n-m))
  end
end

def factorial(n) # n!
  if n >= 1
    n * factorial(n-1)
  else
    1
  end
end

g = Graph.new
#g.add_vertex(10)
g.add_edge(0,1)
g.add_edge(0,2)
g.add_edge(0,8)
g.add_edge(0,7)
g.add_edge(2,3)
g.add_edge(2,8)
g.add_edge(8,7)
g.add_edge(8,6)
g.add_edge(8,5)
g.add_edge(5,4)
g.add_edge(5,6)

g.edges[0].each do |child|
  p child # => 1, 2, 8, 7
end


#  judge connected graph.
bfs(0,g)
# >> 1
# >> 2
# >> 8
# >> 7
# >> "graph is connected"
