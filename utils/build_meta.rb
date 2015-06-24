Dir["meta/*"].each do |d|
    name = File.basename d
    system 'json2lums', d, "assets/bbd/#{name}.bbd"
end
