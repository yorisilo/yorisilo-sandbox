# temporary file

require "bundler/setup"
# 一括require
Bundler.require
# dotenvを使う準備
Dotenv.load

puts ENV['UNKO']
