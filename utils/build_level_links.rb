#!/usr/bin/env ruby
# - encoding: binary

require 'json'

class Levels
  def initialize
    @links = []
  end

  def export file, output
    parse_links file
    save output
  end

  def parse_links links
    links = JSON.parse(File.read links)
    links.each do |l|
      l2 = l[3, 3] + l[0, 3]
      append_link l
      append_link l2
    end
  end

  def append_link link
    @links << link.pack('L6')
  end

  def save bin_linkspec
    f = File.open bin_linkspec, 'wb'
    f.write([@links.length].pack 'L')
    @links.each {|l| f.write l}
    f.close
  end
end

lvl = Levels.new
lvl.export ARGV[0], ARGV[1]