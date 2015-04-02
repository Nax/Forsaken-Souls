dir = Dir['map/level*']
p dir
dir.each do |d|
  f = File.basename d
  system 'ruby', 'utils/build_level.rb', d, "assets/levels/#{f}.lvl"
end
system 'ruby', 'utils/build_level_links.rb', 'map/links.json', 'assets/level_links.bin'
