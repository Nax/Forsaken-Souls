#!/usr/bin/env ruby
# - encoding: binary

require 'json'

class Map
  def initialize
    @maps = []
    @links = []
  end

  def export folder, map
    Dir[folder + '/map*.json'].each {|d| parse_map d}
    parse_links folder + '/links.json'
    save map
  end

  def parse_map m
    map_json = JSON.parse(File.read m)
    w = map_json['width']
    h = map_json['height']
    data = map_json['layers'].map{|d| d['data'].each_slice(w).to_a.reverse }.flatten
    header = [w, h].pack 'LL'
    bindata = data.pack 'C*'
    @maps << (header + bindata)
  end

  def parse_links links
    links = JSON.parse(File.read links)
    links.each do |l|
      l2 = l[2, 2] + l[0, 2]
      append_link l
      append_link l2
    end
  end

  def append_link link
    @links << (link.pack 'L4')
  end

  def save map
    f = File.open map, 'wb'
    f.write([@maps.length].pack 'L')
    @maps.each {|m| f.write m}
    f.write([@links.length].pack 'L')
    @links.each {|l| f.write l}
    f.close
  end
end

m = Map.new
m.export ARGV[0], ARGV[1]
