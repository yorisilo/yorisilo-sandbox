begin
  File.open('labmen.txt') do |file|
    file.each_line do |labmen|
      puts "#{file.lineno}: #{labmen}"
    end
  end

rescue SystemCallError => e
  puts "class=[#{e.class}] message=[#{e.message}]"
rescue IOError => e
  puts "class=[#{e.class}] message=[#{e.message}]"
end
