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

	# Instantiate map header.
    w = map_json['width']
    h = map_json['height']

	# Instantiate the 5 tile layers.
    data = map_json['layers'].map{|d| d['data'].each_slice(w).to_a.reverse if d['data']}.flatten.select{|i| !i.nil?}

	# Instantiate the object layers.
    objects = map_json['layers'][5]['objects']

	# -- Gather and instantiate spawners.
    spawns = []
    objects.each do |o|
      next if o['type'] != 'spawn'
      spawns << {x: o['x'].to_i / 128, y: h - o['y'].to_i / 128, id: o['properties']['enemyID'].to_i}
    end

	# -- Gather and instantiate lights.
    lights = []
    objects.each do |o|
      next if o['type'] != 'light'
      lights << {x: o['x'].to_f / 128.0, y: h.to_f - o['y'].to_f / 128.0}
    end

	# Pack components into binary data.
    header = [w, h].pack 'LL'
    bindata = data.pack 'S*'
    spawndata = [spawns.length].pack 'L'
    spawns.each do |s|
      spawndata += [s[:x], s[:y], s[:id]].pack 'LLL'
    end
    lightdata = [lights.length].pack 'L'
    lights.each do |s|
      lightdata += [s[:x], s[:y]].pack 'FF'
    end
    @maps << (header + bindata + spawndata + lightdata)
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
    @maps.each do |m|
      f.write m
    end
    f.write([@links.length].pack 'L')
    @links.each {|l| f.write l}
    f.close
  end
end

m = Map.new
m.export ARGV[0], ARGV[1]
