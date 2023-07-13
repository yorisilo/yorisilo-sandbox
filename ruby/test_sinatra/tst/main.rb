require "sinatra"
require "sinatra/reloader" if development?

get '/hello/:yourname' do
  "hello " + params[:yourname]
end

get '/hello2/:name' do
  "hello2 #{params[:name]}"
end

get '/hello3/:name' do |n|
  "hello3 #{n}"
end

get '/hello4/:fname/:lname' do |f, l|
  "hello #{f} #{l}"
end

get '/hello4/:fname/ ?:lname?' do |f, l|
  "hello #{f} #{l}"
end

# get '/from/*/to/*' do |f, t|
#   "from #{f} to #{t}"
# end

get '/from/*/to/*' do |f, t|
  "from #{f} to #{t}"
end

get '/template' do
  erb :index
end
